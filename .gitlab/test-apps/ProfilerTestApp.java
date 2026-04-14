import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Profiler Test Application
 *
 * Generates workloads to validate profiler functionality:
 * - CPU activity (ExecutionSample events)
 * - Memory allocations (ObjectAllocationSample events)
 * - Thread activity (multiple threads for sampling)
 *
 * Compatible with JDK 8-25. Compiles with plain javac.
 *
 * Expected JFR Events:
 * - jdk.ExecutionSample: CPU profiling samples
 * - jdk.ObjectAllocationSample: Allocation events
 * - jdk.ThreadAllocationStatistics: Per-thread allocation stats
 *
 * Usage:
 *   javac ProfilerTestApp.java
 *   java ProfilerTestApp [options]
 *
 * Options:
 *   --duration <seconds>       Duration to run (default: 30)
 *   --threads <count>          Number of worker threads (default: 4)
 *   --cpu-iterations <count>   CPU work iterations (default: 10000)
 *   --alloc-rate <per-sec>     Allocations per second (default: 1000)
 */
public class ProfilerTestApp {

    // Configuration
    private int durationSeconds = 30;
    private int threadCount = 4;
    private int cpuIterations = 10000;
    private int allocationsPerSecond = 1000;

    // Runtime state
    private final AtomicBoolean running = new AtomicBoolean(true);
    private final AtomicLong totalIterations = new AtomicLong(0);
    private final AtomicLong totalAllocations = new AtomicLong(0);
    private final List<Thread> threads = new ArrayList<Thread>();

    /**
     * Metrics task - monitors system resources and detects CPU changes
     */
    private class MetricsTask implements Runnable {
        private int lastCpuCount;

        public MetricsTask() {
            this.lastCpuCount = Runtime.getRuntime().availableProcessors();
        }

        public void run() {
            while (running.get()) {
                try {
                    Thread.sleep(5000);

                    int cpus = Runtime.getRuntime().availableProcessors();
                    long freeMemory = Runtime.getRuntime().freeMemory();
                    long totalMemory = Runtime.getRuntime().totalMemory();

                    // Structured logging for parsing
                    System.out.printf("[METRICS] timestamp=%d cpus=%d free_mb=%d total_mb=%d%n",
                        System.currentTimeMillis() / 1000,
                        cpus,
                        freeMemory / 1024 / 1024,
                        totalMemory / 1024 / 1024);

                    // Detect CPU changes
                    if (cpus != lastCpuCount) {
                        System.err.printf("[WARN] CPU count changed: %d -> %d%n", lastCpuCount, cpus);
                        lastCpuCount = cpus;
                    }
                } catch (InterruptedException e) {
                    break;
                }
            }
        }
    }

    public static void main(String[] args) throws Exception {
        ProfilerTestApp app = new ProfilerTestApp();
        app.parseArgs(args);
        app.run();
    }

    private void parseArgs(String[] args) {
        for (int i = 0; i < args.length; i++) {
            String arg = args[i];

            if (arg.equals("--duration") && i + 1 < args.length) {
                durationSeconds = Integer.parseInt(args[++i]);
            } else if (arg.equals("--threads") && i + 1 < args.length) {
                threadCount = Integer.parseInt(args[++i]);
            } else if (arg.equals("--cpu-iterations") && i + 1 < args.length) {
                cpuIterations = Integer.parseInt(args[++i]);
            } else if (arg.equals("--alloc-rate") && i + 1 < args.length) {
                allocationsPerSecond = Integer.parseInt(args[++i]);
            } else if (arg.equals("--help") || arg.equals("-h")) {
                printUsage();
                System.exit(0);
            } else {
                System.err.println("Unknown argument: " + arg);
                printUsage();
                System.exit(1);
            }
        }
    }

    private void printUsage() {
        System.out.println("Usage: java ProfilerTestApp [options]");
        System.out.println();
        System.out.println("Options:");
        System.out.println("  --duration <seconds>       Duration to run (default: 30)");
        System.out.println("  --threads <count>          Number of worker threads (default: 4)");
        System.out.println("  --cpu-iterations <count>   CPU work iterations (default: 10000)");
        System.out.println("  --alloc-rate <per-sec>     Allocations per second (default: 1000)");
        System.out.println("  --help, -h                 Show this help message");
    }

    private void run() throws Exception {
        System.out.println("=== Profiler Test Application ===");
        System.out.println("Configuration:");
        System.out.println("  Duration: " + durationSeconds + " seconds");
        System.out.println("  Threads: " + threadCount);
        System.out.println("  CPU iterations: " + cpuIterations);
        System.out.println("  Allocation rate: " + allocationsPerSecond + " per second");
        System.out.println();

        // Set up shutdown handler
        Runtime.getRuntime().addShutdownHook(new Thread() {
            public void run() {
                shutdown();
            }
        });

        // Start timer thread
        Thread timerThread = new Thread(new TimerTask(), "timer-thread");
        timerThread.setDaemon(false);
        timerThread.start();

        // Start metrics thread
        Thread metricsThread = new Thread(new MetricsTask(), "metrics-thread");
        metricsThread.setDaemon(true);
        metricsThread.start();

        // Create barrier for synchronized start
        final CyclicBarrier startBarrier = new CyclicBarrier(threadCount);

        // Start worker threads
        for (int i = 0; i < threadCount; i++) {
            Thread workerThread = new Thread(new WorkerTask(i, startBarrier), "worker-" + i);
            workerThread.setDaemon(false);
            threads.add(workerThread);
            workerThread.start();
        }

        System.out.println("Started " + threadCount + " worker threads");
        System.out.println("Test running...");
        System.out.println();

        // Wait for timer to expire
        timerThread.join();

        // Stop workers
        running.set(false);

        // Wait for all workers to finish
        for (Thread thread : threads) {
            thread.join(5000); // 5 second timeout per thread
        }

        // Print summary
        System.out.println();
        System.out.println("=== Test Complete ===");
        System.out.println("Total iterations: " + totalIterations.get());
        System.out.println("Total allocations: " + totalAllocations.get());
        System.out.println();
    }

    private void shutdown() {
        running.set(false);
    }

    /**
     * Timer task - runs for specified duration
     */
    private class TimerTask implements Runnable {
        public void run() {
            try {
                Thread.sleep(durationSeconds * 1000L);
            } catch (InterruptedException e) {
                // Expected
            }
        }
    }

    /**
     * Worker task - generates CPU and allocation workload
     */
    private class WorkerTask implements Runnable {
        private final int workerId;
        private final CyclicBarrier startBarrier;
        private final Random random = new Random();

        WorkerTask(int workerId, CyclicBarrier startBarrier) {
            this.workerId = workerId;
            this.startBarrier = startBarrier;
        }

        public void run() {
            try {
                // Wait for all threads to be ready
                startBarrier.await();

                long iterations = 0;
                long allocations = 0;
                long lastReportTime = System.currentTimeMillis();

                while (running.get()) {
                    // CPU-intensive work
                    performCPUWork();
                    iterations++;

                    // Memory allocations
                    performAllocations();
                    // Note: Division by 100 assumes ~100 iterations/second (10ms sleep + work time)
                    // This is an approximation based on typical execution timing
                    allocations += allocationsPerSecond / 100; // Per iteration

                    // Small sleep to avoid spinning
                    Thread.sleep(10);

                    // Periodic reporting
                    long now = System.currentTimeMillis();
                    if (now - lastReportTime >= 5000) {
                        System.out.println("Worker " + workerId + ": " + iterations + " iterations, " + allocations + " allocations");
                        lastReportTime = now;
                    }
                }

                totalIterations.addAndGet(iterations);
                totalAllocations.addAndGet(allocations);

            } catch (Exception e) {
                System.err.println("Worker " + workerId + " failed: " + e.getMessage());
                e.printStackTrace();
            }
        }

        /**
         * Perform CPU-intensive work to generate ExecutionSample events
         */
        private void performCPUWork() {
            // Mix of different CPU operations

            // 1. Math operations
            double result = 0;
            for (int i = 0; i < cpuIterations; i++) {
                result += Math.sqrt(i);
                result *= Math.sin(i * 0.001);
            }

            // 2. Prime number calculation
            int primeCount = 0;
            for (int num = 2; num < cpuIterations && num < 1000; num++) {
                if (isPrime(num)) {
                    primeCount++;
                }
            }

            // 3. String operations
            String text = "profiler-test-" + result + "-" + primeCount;
            int hash = text.hashCode();

            // Prevent optimization
            if (hash == Integer.MAX_VALUE) {
                System.out.println("Unlikely: " + hash);
            }
        }

        /**
         * Check if number is prime (CPU-intensive)
         */
        private boolean isPrime(int n) {
            if (n <= 1) return false;
            if (n <= 3) return true;
            if (n % 2 == 0 || n % 3 == 0) return false;

            for (int i = 5; i * i <= n; i += 6) {
                if (n % i == 0 || n % (i + 2) == 0) {
                    return false;
                }
            }
            return true;
        }

        /**
         * Perform memory allocations to generate ObjectAllocationSample events
         */
        private void performAllocations() {
            int allocsPerCall = allocationsPerSecond / 100; // Called ~100 times per second

            // 1. String allocations
            List<String> strings = new ArrayList<String>(allocsPerCall);
            for (int i = 0; i < allocsPerCall / 3; i++) {
                strings.add("allocation-worker-" + workerId + "-iteration-" + i + "-" + random.nextInt());
            }

            // 2. Array allocations
            List<byte[]> arrays = new ArrayList<byte[]>(allocsPerCall / 3);
            for (int i = 0; i < allocsPerCall / 3; i++) {
                arrays.add(new byte[1024]); // 1KB allocations
            }

            // 3. Object allocations
            List<WorkerData> objects = new ArrayList<WorkerData>(allocsPerCall / 3);
            for (int i = 0; i < allocsPerCall / 3; i++) {
                objects.add(new WorkerData(workerId, i, System.nanoTime()));
            }

            // Prevent optimization - occasionally use the data
            if (random.nextInt(1000) == 0) {
                System.out.println("Allocated: " + strings.size() + " strings, " + arrays.size() + " arrays, " + objects.size() + " objects");
            }
        }
    }

    /**
     * Data class for allocation testing
     */
    private static class WorkerData {
        private final int workerId;
        private final int iteration;
        private final long timestamp;
        private final String description;

        WorkerData(int workerId, int iteration, long timestamp) {
            this.workerId = workerId;
            this.iteration = iteration;
            this.timestamp = timestamp;
            this.description = "Worker " + workerId + " iteration " + iteration;
        }

        public String getDescription() {
            return description + " at " + timestamp;
        }
    }
}
