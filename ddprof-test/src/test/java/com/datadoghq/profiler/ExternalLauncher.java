package com.datadoghq.profiler;

import com.datadoghq.profiler.referencechains.LeakingCacheScenario;

import java.lang.management.ManagementFactory;
import java.lang.management.ThreadMXBean;
import java.nio.file.Paths;
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
 *     <li>leak-cache "&lt;start command&gt;|||&lt;scratch dump path&gt;" - starts the profiler with
 *     the given start command, then runs {@link LeakingCacheScenario} in this process and exits
 *     directly (no readiness/stdin-signal handshake, unlike the other modes above) once it
 *     prints its one result line. Used by {@code ExternalProcessReferenceChainTest}
 *     (referencechains package) to prove the reference-chains mechanism end-to-end against a
 *     genuinely separate JVM, not the in-process dynamic-attach lifecycle every other test in
 *     this module uses - see that scenario's own class comment for why a *separate* process is
 *     load-bearing here (the one-shot root-seeded BFS walk is a process-wide, once-ever
 *     resource).</li>
 * </ul>
 */
public class ExternalLauncher {
    public static void main(String[] args) throws Exception {
        Thread worker = null;
        try {
            if (args.length < 1) {
                throw new RuntimeException();
            }
            if (args[0].equals("library")) {
                JVMAccess.getInstance();
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
            } else if (args[0].equals("leak-cache")) {
                // "<start command>|||<scratch dump path>" packed into one args[1] string rather
                // than extending AbstractProcessProfilerTest.launch()'s generic 2-arg
                // (target, commands) contract with a 3rd argument every other mode would have to
                // ignore.
                String packed = args.length == 2 ? args[1] : "";
                int sep = packed.indexOf("|||");
                if (sep < 0) {
                    throw new IllegalArgumentException(
                        "leak-cache requires \"<start command>|||<scratch dump path>\", got: " + packed);
                }
                String commands = packed.substring(0, sep);
                String scratchPath = packed.substring(sep + "|||".length());
                JavaProfiler instance = JavaProfiler.getInstance();
                // LeakingCacheScenario.run() itself calls instance.execute(commands), not here -
                // it needs to seed its cache fixture *before* starting the profiler (see that
                // method's own comment for why).
                LeakingCacheScenario.run(instance, commands, Paths.get(scratchPath));
                System.out.flush();
                // Deliberately exits here rather than falling through to the shared
                // "[ready]" + stdin-signal handshake below: this mode runs to completion in one
                // shot (no live back-and-forth with the parent needed) and its own result line
                // has already been printed by LeakingCacheScenario.run().
                System.exit(0);
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
