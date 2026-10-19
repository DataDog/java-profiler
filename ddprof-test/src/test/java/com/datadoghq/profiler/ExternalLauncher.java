/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import java.io.IOException;
import java.lang.management.ManagementFactory;
import java.lang.management.ThreadMXBean;
import java.lang.reflect.Method;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.TreeMap;
import java.util.concurrent.atomic.LongAdder;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * External launcher for the profiler under test.
 * <p>
 * This class is used to launch the profiler in a separate process for testing purposes.
 * </p>
 * The main method takes the following arguments:
 * <ul>
 *     <li>library - loads the profiler library</li>
 *     <li>profiler [comma delimited profiler command list] - starts the profiler</li>
 *     <li>profiler-work:<expectedCpuTime> [comma delimited profiler command list] - starts the profiler and runs a CPU-intensive task</li>
 *     <li>profiler-virtual-thread - calls {@link JavaProfiler#getInstance()} for the first time from a virtual thread</li>
 *     <li>profiler-sequence [';'-delimited steps] - runs a sequence of start/stop calls in this
 *     process; each step is either the literal {@code STOP} (calls {@link JavaProfiler#stop()})
 *     or a comma delimited profiler command list (calls {@link JavaProfiler#execute(String)})</li>
 *     <li>lazy-trace-id &lt;comma delimited profiler command list, required&gt; - starts the profiler, spins
 *     in {@code com.datadoghq.profiler.generated.LazyTraceIdProbe} (defined by its own class loader, so it
 *     has no jmethodIDs until the profiler resolves its frames) and stops the profiler</li>
 *     <li>entry-frames &lt;comma delimited profiler command list, required&gt; - starts the profiler, then burns
 *     CPU concurrently on the main thread, on a plain {@code new Thread(Runnable)} and on a
 *     two-level {@link Thread} subclass, and stops the profiler again. The resulting recording
 *     holds samples rooted at each of the three thread entry points; see {@code EntryFrameTest}</li>
 *     <li>lazy-calibration-preexisting-arrays &lt;comma delimited profiler command list, required&gt; -
 *     creates {@code Void[]} and {@code Void[][]} with a few hundred class definitions in between, so their
 *     JFR trace IDs are far apart, then starts the profiler, prints the {@code klass_trace_id_offset}
 *     counter and stops it; see {@code LazyTraceIdCalibrationTest}</li>
 *     <li>line-numbers &lt;';'-delimited profiler command lists, required&gt; - for each command list in
 *     turn, starts the profiler, runs the same JDK-heavy workload, prints the
 *     {@code method_resolve_lazy_resolved} counter and stops the profiler; see
 *     {@code LazyLineNumberConsistencyTest}</li>
 * </ul>
 */
public class ExternalLauncher {
    /**
     * Starts a virtual thread using reflection so this class compiles with {@code --release 8}.
     * Equivalent to {@code Thread.ofVirtual().start(task)}.
     */
    private static Thread startVirtualThread(Runnable task) throws Exception {
        Method ofVirtual = Thread.class.getMethod("ofVirtual");
        Object builder = ofVirtual.invoke(null);
        Class<?> builderInterface = Class.forName("java.lang.Thread$Builder");
        Method start = builderInterface.getMethod("start", Runnable.class);
        return (Thread) start.invoke(builder, task);
    }

    /** How long each {@code entry-frames} thread burns CPU for. */
    private static final long ENTRY_FRAME_WORKLOAD_MILLIS = 1000;

    private static volatile long entryFrameSink;

    /**
     * A {@link Thread} subclass that does not override {@code run()}, so that
     * {@link EntryFrameThread} below sits two levels below {@link Thread} and its {@code run()}
     * frame can only be recognised as a thread entry point by walking the whole superclass chain.
     */
    private static class BaseEntryFrameThread extends Thread {
        BaseEntryFrameThread(String name) {
            super(name);
        }
    }

    private static final class EntryFrameThread extends BaseEntryFrameThread {
        EntryFrameThread() {
            super("entry-frame-subclass");
        }

        @Override
        public void run() {
            entryFrameWorkLevel1(ENTRY_FRAME_WORKLOAD_MILLIS);
        }
    }

    private static final class EntryFrameRunnable implements Runnable {
        @Override
        public void run() {
            entryFrameWorkLevel1(ENTRY_FRAME_WORKLOAD_MILLIS);
        }
    }

    /**
     * Burns CPU on the main thread and on the two worker threads at the same time, so that all
     * three entry points ({@code ExternalLauncher.main(String[])}, {@code Thread.run()} for the
     * {@link EntryFrameRunnable} thread and {@code EntryFrameThread.run()}) are the bottom frame
     * of some samples.
     */
    private static void runEntryFrameWorkload() throws InterruptedException {
        Thread runnableThread = new Thread(new EntryFrameRunnable(), "entry-frame-runnable");
        Thread subclassThread = new EntryFrameThread();
        runnableThread.start();
        subclassThread.start();
        entryFrameWorkLevel1(ENTRY_FRAME_WORKLOAD_MILLIS);
        runnableThread.join();
        subclassThread.join();
    }

    // entryFrameWorkLevel1/2 pad the call chain below every entry point, so that a recording
    // taken with a small jstackdepth roots its samples inside the chain rather than at the
    // entry frame itself - that is how EntryFrameTest gets its negative control.
    private static void entryFrameWorkLevel1(long millis) {
        entryFrameWorkLevel2(millis);
    }

    private static void entryFrameWorkLevel2(long millis) {
        entryFrameBurn(millis);
    }

    private static void entryFrameBurn(long millis) {
        // nanoTime() is monotonic: a wall-clock adjustment mid-burn cannot cut the workload short
        // (which would starve the recording of samples) or stretch it past the launcher's timeout.
        long deadline = System.nanoTime() + millis * 1_000_000L;
        long acc = 0;
        while (System.nanoTime() - deadline < 0) {
            for (int i = 0; i < 100000; i++) {
                acc += i * 31 + (acc >>> 3);
            }
        }
        entryFrameSink = acc;
    }

    /** How long the {@code line-numbers} workload runs under each command list. */
    private static final long LINE_NUMBER_WORKLOAD_MILLIS = 1500;

    private static volatile long lineNumberSink;

    /**
     * Spends its time in many different JDK methods (regular expressions, formatting, maps,
     * sorting, big-integer arithmetic), so that their frames, and the lines of their bytecode
     * indices, show up in the recording.
     */
    private static void runLineNumberWorkload() {
        Pattern pattern = Pattern.compile("([a-z]+)-(\\d+)");
        Random rnd = new Random(42);
        long acc = 0;
        long deadline = System.currentTimeMillis() + LINE_NUMBER_WORKLOAD_MILLIS;
        while (System.currentTimeMillis() < deadline) {
            Map<String, Integer> counts = new HashMap<>();
            TreeMap<Integer, String> sorted = new TreeMap<>();
            List<String> words = new ArrayList<>();
            for (int i = 0; i < 200; i++) {
                String word = String.format("%s-%d", Long.toString(rnd.nextInt(1 << 20), 36), i);
                Matcher m = pattern.matcher(word);
                if (m.matches()) {
                    counts.merge(m.group(1), m.group(2).length(), Integer::sum);
                }
                sorted.put(word.hashCode(), word);
                words.add(word.toUpperCase());
            }
            Collections.sort(words);
            BigInteger big = BigInteger.valueOf(rnd.nextLong()).pow(8).mod(BigInteger.valueOf(1_000_000_007L));
            acc += counts.size() + sorted.firstKey() + words.get(0).length() + big.intValue();
        }
        lineNumberSink = acc;
    }

    public static void main(String[] args) throws Exception {
        Thread worker = null;
        try {
            if (args.length < 1) {
                throw new RuntimeException();
            }
            if (args[0].equals("library")) {
                JVMAccess.getInstance();
            } else if (args[0].equals("profiler-virtual-thread")) {
                Thread vt = startVirtualThread(() -> {
                    try {
                        JavaProfiler.getInstance();
                        System.out.println("[virtual-thread-no-exception]");
                    } catch (IOException e) {
                        System.out.println("[virtual-thread-ioexception] " + e.getMessage());
                    } catch (Throwable t) {
                        System.out.println("[virtual-thread-unexpected] " + t.getClass().getName() + ": " + t.getMessage());
                    }
                });
                vt.join();
            } else if (args[0].equals("profiler")) {
                JavaProfiler instance = JavaProfiler.getInstance();
                if (args.length == 2) {
                    String commands = args[1];
                    if (!commands.isEmpty()) {
                        instance.execute(commands);
                    }
                }
            } else if (args[0].equals("profiler-sequence")) {
                JavaProfiler instance = JavaProfiler.getInstance();
                if (args.length == 2) {
                    for (String step : args[1].split(";")) {
                        if (step.equals("STOP")) {
                            instance.stop();
                        } else if (!step.isEmpty()) {
                            instance.execute(step);
                        }
                    }
                }
            } else if (args[0].equals("lazy-trace-id")) {
                if (args.length < 2 || args[1].isEmpty()) {
                    throw new IllegalArgumentException("lazy-trace-id requires a profiler command list");
                }
                JavaProfiler instance = JavaProfiler.getInstance();
                instance.execute(args[1]);
                Class<?> probe = SpinClasses.define("com/datadoghq/profiler/generated/LazyTraceIdProbe");
                probe.getMethod("spin", long.class).invoke(null, 2_000_000_000L);
                // Stopping dumps the recording, which resolves the probe's raw frames.
                instance.stop();
            } else if (args[0].equals("lazy-calibration-preexisting-arrays")) {
                if (args.length < 2 || args[1].isEmpty()) {
                    throw new IllegalArgumentException("lazy-calibration-preexisting-arrays requires a profiler command list");
                }
                Object lowDimension = java.lang.reflect.Array.newInstance(Void.class, 0);
                for (int i = 0; i < 200; i++) {
                    SpinClasses.define("com/datadoghq/profiler/generated/CalibrationGap" + i);
                }
                Object secondDimension = java.lang.reflect.Array.newInstance(lowDimension.getClass(), 0);
                JavaProfiler instance = JavaProfiler.getInstance();
                instance.execute(args[1]);
                System.out.println("[calibration] klass_trace_id_offset="
                        + instance.getDebugCounters().get("klass_trace_id_offset")
                        + " arrays=" + secondDimension.getClass().getName());
                instance.stop();
            } else if (args[0].equals("line-numbers")) {
                if (args.length < 2 || args[1].isEmpty()) {
                    throw new IllegalArgumentException("line-numbers requires profiler command lists");
                }
                JavaProfiler instance = JavaProfiler.getInstance();
                for (String commands : args[1].split(";")) {
                    instance.execute(commands);
                    runLineNumberWorkload();
                    // Counters are reset on start, so read them while this session's are current;
                    // the dump on stop() resolves the raw frames, so stop first.
                    instance.stop();
                    System.out.println("[line-numbers] method_resolve_lazy_resolved="
                            + instance.getDebugCounters().get("method_resolve_lazy_resolved"));
                }
            } else if (args[0].equals("entry-frames")) {
                // Unlike the modes above, this one is only meaningful with a running profiler:
                // silently skipping the start would leave the parent process parsing an empty
                // recording and reporting a missing entry frame instead of a missing command.
                if (args.length < 2 || args[1].isEmpty()) {
                    throw new IllegalArgumentException(
                            "entry-frames requires a profiler command list");
                }
                JavaProfiler instance = JavaProfiler.getInstance();
                instance.execute(args[1]);
                runEntryFrameWorkload();
                // Stop explicitly rather than leaving it to JVM shutdown: the parent process
                // starts reading the recording as soon as this process exits.
                instance.stop();
            } else if (args[0].startsWith("profiler-work:")) {
                long expectedCpuTime = Long.parseLong(args[0].substring("profiler-work:".length()));
                ThreadMXBean thrdBean = ManagementFactory.getThreadMXBean();
                JavaProfiler instance = JavaProfiler.getInstance();
                if (args.length == 2) {
                    String commands = args[1];
                    if (!commands.isEmpty()) {
                        instance.execute(commands);
                        worker = new Thread(() -> {
                            Random rnd = new Random();
                            LongAdder adder = new LongAdder();
                            long counter = 0;
                            long cpuTime = thrdBean.getThreadCpuTime(Thread.currentThread().getId());
                            while (!Thread.currentThread().isInterrupted()) {
                                adder.add(rnd.nextLong());
                                // make sure we caused some CPU load and print the progress
                                if (++counter % 1000000 == 0) {
                                    if (thrdBean.getThreadCpuTime(Thread.currentThread().getId()) - cpuTime > expectedCpuTime * 1_000_000L) {
                                        cpuTime = thrdBean.getThreadCpuTime(Thread.currentThread().getId());
                                        System.out.println("[working]");
                                        System.out.flush();
                                    }
                                }
                            }
                            System.out.println("[async] " + adder.sum());
                        });
                        worker.start();
                    }
                }
            }
        } finally {
            System.out.println("[ready]");
            System.out.flush();
            System.err.flush();
        }
        // wait for signal to exit
        System.in.read();
        if (worker != null) {
            worker.interrupt();
            worker.join();
        }
    }
}
