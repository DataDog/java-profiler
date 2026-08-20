/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import java.io.IOException;
import java.lang.management.ManagementFactory;
import java.lang.management.ThreadMXBean;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Random;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
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
 *     <li>profiler-agent-compatible - reuses native monitor ownership after agent initialization</li>
 *     <li>profiler-delegation-conflict - requests delegated monitor ownership after agent initialization</li>
 *     <li>profiler-java-default-delegation-reuse - verifies explicit native ownership after default initialization</li>
 *     <li>profiler-java-default-delegation-conflict - verifies delegated ownership conflicts after default initialization</li>
 *     <li>profiler-java-delegation-reuse:&lt;delegated&gt; - verifies compatible Java singleton ownership reuse</li>
 *     <li>profiler-java-delegation-conflict:&lt;initial&gt;:&lt;requested&gt; - verifies conflicting Java singleton ownership requests</li>
 *     <li>profiler-java-delegation-legacy-reuse:&lt;initial&gt; - verifies the legacy no-preference overloads reuse the existing singleton</li>
 *     <li>profiler-preexisting-monitor-wait - exercises Object.wait on a thread created before profiler initialization</li>
 *     <li>profiler-preexisting-monitor-contention - exercises monitor contention on a thread created before profiler initialization</li>
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

    /** Runs one native monitor callback lifecycle on a platform thread created before JNI load. */
    private static void runPreExistingMonitorCallback(boolean contention) throws Exception {
        ExecutorService executor = Executors.newSingleThreadExecutor(task -> {
            Thread thread = new Thread(task, "preexisting-monitor-callback");
            thread.setDaemon(true);
            return thread;
        });
        executor.submit(Thread::currentThread).get(5, TimeUnit.SECONDS);

        Path recording = Files.createTempFile("preexisting-monitor-callback", ".jfr");
        JavaProfiler profiler = null;
        boolean started = false;
        try {
            profiler = JavaProfiler.getInstance();
            profiler.execute("start,wall=1ms,filter=,wallprecheck=true,jfr,file="
                    + recording.toAbsolutePath());
            started = true;
            long before = profiler.getDebugCounters().getOrDefault("task_block_emitted", 0L);
            Object monitor = new Object();

            if (contention) {
                CountDownLatch attempting = new CountDownLatch(1);
                Future<?> blocked;
                synchronized (monitor) {
                    blocked = executor.submit(() -> {
                        attempting.countDown();
                        synchronized (monitor) {
                            // Acquiring the monitor completes the contended interval.
                        }
                    });
                    if (!attempting.await(5, TimeUnit.SECONDS)) {
                        throw new IllegalStateException("Worker did not attempt monitor entry");
                    }
                    Thread.sleep(100L);
                }
                blocked.get(5, TimeUnit.SECONDS);
            } else {
                executor.submit(() -> {
                    synchronized (monitor) {
                        monitor.wait(100L);
                    }
                    return null;
                }).get(5, TimeUnit.SECONDS);
            }

            long emitted = profiler.getDebugCounters().getOrDefault("task_block_emitted", 0L) - before;
            System.out.println("[preexisting-monitor-events] " + emitted);
        } finally {
            if (started) {
                profiler.stop();
            }
            executor.shutdownNow();
            executor.awaitTermination(5, TimeUnit.SECONDS);
            Files.deleteIfExists(recording);
        }
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
                JavaProfiler initial = JavaProfiler.getInstance();
                JavaProfiler reused = JavaProfiler.getInstance();
                System.out.println("[virtual-thread-recovery] "
                        + (initial == reused) + " " + reused.isMonitorWaitEventsDelegated());
            } else if (args[0].equals("profiler-delegation-conflict")) {
                String libraryPath = System.getProperty("ddprof.test.agent.path");
                try {
                    JavaProfiler.getInstance(libraryPath, null, true);
                    System.out.println("[delegation-conflict-missed]");
                } catch (IllegalStateException expected) {
                    JavaProfiler recovered =
                            JavaProfiler.getInstance(libraryPath, null, false);
                    System.out.println("[delegation-conflict] "
                            + recovered.isMonitorWaitEventsDelegated());
                }
            } else if (args[0].equals("profiler-java-default-delegation-reuse")) {
                JavaProfiler initial = JavaProfiler.getInstance();
                JavaProfiler reused = JavaProfiler.getInstance(null, null, false);
                System.out.println("[java-default-delegation-reuse] "
                        + (initial == reused) + " " + reused.isMonitorWaitEventsDelegated());
            } else if (args[0].equals("profiler-java-default-delegation-conflict")) {
                JavaProfiler initial = JavaProfiler.getInstance();
                try {
                    JavaProfiler.getInstance(null, null, true);
                    System.out.println("[java-default-delegation-conflict-missed]");
                } catch (IllegalStateException expected) {
                    JavaProfiler recovered =
                            JavaProfiler.getInstance(null, null, false);
                    System.out.println("[java-default-delegation-conflict] "
                            + (initial == recovered) + " "
                            + recovered.isMonitorWaitEventsDelegated());
                }
            } else if (args[0].startsWith("profiler-java-delegation-reuse:")) {
                boolean delegated = Boolean.parseBoolean(
                        args[0].substring("profiler-java-delegation-reuse:".length()));
                JavaProfiler initial = JavaProfiler.getInstance(null, null, delegated);
                JavaProfiler reused = JavaProfiler.getInstance(null, null, delegated);
                System.out.println("[java-delegation-reuse] "
                        + (initial == reused) + " " + reused.isMonitorWaitEventsDelegated());
            } else if (args[0].startsWith("profiler-java-delegation-legacy-reuse:")) {
                // A legacy overload expresses no preference about monitor-event ownership:
                // it must return the existing singleton whatever its delegation setting is,
                // never throw IllegalStateException. An escaping ISE is the failure signal.
                boolean initialDelegation = Boolean.parseBoolean(args[0].substring(
                        "profiler-java-delegation-legacy-reuse:".length()));
                JavaProfiler initial =
                        JavaProfiler.getInstance(null, null, initialDelegation);
                JavaProfiler reused = JavaProfiler.getInstance();
                JavaProfiler reused2 = JavaProfiler.getInstance(null, null);
                System.out.println("[java-delegation-legacy-reuse] "
                        + (initial == reused) + " "
                        + (initial == reused2) + " "
                        + initial.isMonitorWaitEventsDelegated());
            } else if (args[0].startsWith("profiler-java-delegation-conflict:")) {
                String[] delegationModes = args[0].split(":");
                boolean initialDelegation = Boolean.parseBoolean(delegationModes[1]);
                boolean requestedDelegation = Boolean.parseBoolean(delegationModes[2]);
                JavaProfiler initial =
                        JavaProfiler.getInstance(null, null, initialDelegation);
                try {
                    JavaProfiler.getInstance(null, null, requestedDelegation);
                    System.out.println("[java-delegation-conflict-missed]");
                } catch (IllegalStateException expected) {
                    JavaProfiler recovered =
                            JavaProfiler.getInstance(null, null, initialDelegation);
                    System.out.println("[java-delegation-conflict] "
                            + (initial == recovered) + " "
                            + recovered.isMonitorWaitEventsDelegated());
                }
            } else if (args[0].equals("profiler-agent-compatible")) {
                String libraryPath = System.getProperty("ddprof.test.agent.path");
                JavaProfiler profiler = JavaProfiler.getInstance(libraryPath, null, false);
                System.out.println("[agent-compatible] "
                        + profiler.isMonitorWaitEventsDelegated());
            } else if (args[0].equals("profiler-preexisting-monitor-wait")) {
                runPreExistingMonitorCallback(false);
            } else if (args[0].equals("profiler-preexisting-monitor-contention")) {
                runPreExistingMonitorCallback(true);
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
