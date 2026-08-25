/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import java.io.IOException;
import java.lang.management.ManagementFactory;
import java.lang.management.ThreadMXBean;
import java.lang.reflect.Method;
import java.util.Random;
import java.util.concurrent.atomic.LongAdder;

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
 *     <li>entry-frames &lt;comma delimited profiler command list, required&gt; - starts the profiler, then burns
 *     CPU concurrently on the main thread, on a plain {@code new Thread(Runnable)} and on a
 *     two-level {@link Thread} subclass, and stops the profiler again. The resulting recording
 *     holds samples rooted at each of the three thread entry points; see {@code EntryFrameTest}</li>
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
