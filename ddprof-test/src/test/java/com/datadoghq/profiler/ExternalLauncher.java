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
 *     <li>profiler-agent-compatible - reuses native monitor ownership after agent initialization</li>
 *     <li>profiler-delegation-conflict - requests delegated monitor ownership after agent initialization</li>
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
            } else if (args[0].equals("profiler-delegation-conflict")) {
                String libraryPath = System.getProperty("ddprof.test.agent.path");
                try {
                    JavaProfiler.getInstance(libraryPath, null, true);
                    System.out.println("[delegation-conflict-missed]");
                } catch (IllegalStateException expected) {
                    System.out.println("[delegation-conflict] " + expected.getMessage());
                }
            } else if (args[0].equals("profiler-agent-compatible")) {
                String libraryPath = System.getProperty("ddprof.test.agent.path");
                JavaProfiler profiler = JavaProfiler.getInstance(libraryPath, null, false);
                System.out.println("[agent-compatible] " + profiler.isMonitorEventsDelegated());
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
