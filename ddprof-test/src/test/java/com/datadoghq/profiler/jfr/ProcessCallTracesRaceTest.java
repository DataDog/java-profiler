package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.params.provider.ValueSource;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.CountDownLatch;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Regression test for PROF-14889: SIGSEGV in Profiler::processCallTraces during JFR
 * snapshot dump under high-rate wall-clock profiling.
 *
 * Root cause: CallTraceHashTable::clearTableOnly() used a global refcount wait
 * (waitForAllRefCountsToClear) that timed out under sustained signal-handler load,
 * leaving collect() racing with an in-flight put().  The bug surfaces only when:
 *   - Wall-clock profiling is active at high rate (<=5 ms)
 *   - Many threads are generating call traces simultaneously
 *   - dump() is called explicitly while the profiler is running
 *
 * A SIGSEGV from this crash aborts the JVM, which Gradle/JUnit detects as a
 * non-zero exit code and reports as a test failure.
 */
public class ProcessCallTracesRaceTest extends CStackAwareAbstractProfilerTest {

    /** Duration long enough to trigger the race; keep under the @Timeout budget. */
    private static final int TEST_DURATION_SECS = 20;
    /** Number of worker threads generating call traces (drives signal-handler load). */
    private static final int WORKER_THREADS = 64;
    /** Number of threads calling dump() concurrently. */
    private static final int DUMP_THREADS = 4;

    public ProcessCallTracesRaceTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected boolean isPlatformSupported() {
        // The crash is only observable with a real VM stack walker; J9 uses a
        // different internal profiling path.  Require JDK 11+ to match the customer
        // JDK range where the crash is reported.
        return !Platform.isJ9() && Platform.isJavaVersionAtLeast(11);
    }

    @Override
    protected String getProfilerCommand() {
        // High-rate wall-clock profiling maximises signal-handler frequency,
        // increasing the probability of refcount contention in clearTableOnly().
        return "wall=1ms,cpu=1ms";
    }

    @RetryTest(2)
    @Timeout(value = 90)
    @TestTemplate
    @ValueSource(strings = {"vm"})
    public void dumpUnderHighLoad() throws Exception {
        Assumptions.assumeTrue(!Platform.isZing(), "Zing forces cstack=no, skipping");

        AtomicInteger dumpCount = new AtomicInteger(0);
        AtomicInteger workCount = new AtomicInteger(0);
        CountDownLatch workersReady = new CountDownLatch(WORKER_THREADS);

        long deadline = System.currentTimeMillis() + TEST_DURATION_SECS * 1000L;

        // Worker pool: keeps all threads busy with CPU work to generate many call
        // traces per profiling tick, maximising put() rate into CallTraceStorage.
        ExecutorService workers = Executors.newFixedThreadPool(WORKER_THREADS);
        for (int i = 0; i < WORKER_THREADS; i++) {
            workers.submit(() -> {
                workersReady.countDown();
                long x = 0;
                while (System.currentTimeMillis() < deadline && !Thread.currentThread().isInterrupted()) {
                    // Tight loop: generates identifiable call-stack frames and
                    // keeps the CPU hot so wall-clock signals fire frequently.
                    for (int j = 0; j < 10_000; j++) {
                        x = x * 6364136223846793005L + 1442695040888963407L;
                    }
                    workCount.incrementAndGet();
                }
                return x; // prevent optimisation
            });
        }

        // Wait for all workers to start before measuring dump() safety.
        assertTrue(workersReady.await(10, TimeUnit.SECONDS),
                "Worker threads did not start within 10 s");

        // Dump threads: repeatedly call dump() while profiling is hot.
        // A SIGSEGV in processCallTraces here aborts the JVM and fails the test.
        // Each dump thread pre-allocates a single temp file and reuses it across
        // all iterations to avoid per-dump filesystem churn that can exhaust /tmp
        // or cause awaitTermination to expire on slow CI.
        ExecutorService dumpers = Executors.newFixedThreadPool(DUMP_THREADS);
        for (int i = 0; i < DUMP_THREADS; i++) {
            dumpers.submit(() -> {
                Path tmp;
                try {
                    tmp = Files.createTempFile("prof-race-test-", ".jfr");
                    tmp.toFile().deleteOnExit();
                } catch (Exception e) {
                    System.err.println("Failed to create temp file: " + e);
                    return;
                }
                try {
                    while (System.currentTimeMillis() < deadline) {
                        try {
                            dump(tmp);
                            dumpCount.incrementAndGet();
                            // Brief pause so dump() interleaves with ongoing profiling
                            // signals rather than running back-to-back in the same
                            // profiling quiescent window.
                            Thread.sleep(5);
                        } catch (InterruptedException e) {
                            Thread.currentThread().interrupt();
                            return;
                        } catch (Exception e) {
                            // dump() failures other than SIGSEGV are logged but do not
                            // fail the test on their own; the JVM crash is the signal.
                            System.err.println("dump() threw: " + e);
                        }
                    }
                } finally {
                    try { Files.deleteIfExists(tmp); } catch (Exception ignored) {}
                }
            });
        }

        try {
            workers.shutdown();
            dumpers.shutdown();
            // Widen termination budget beyond the deadline to accommodate slow CI I/O.
            assertTrue(workers.awaitTermination(TEST_DURATION_SECS + 30L, TimeUnit.SECONDS),
                    "Worker threads did not finish");
            assertTrue(dumpers.awaitTermination(TEST_DURATION_SECS + 30L, TimeUnit.SECONDS),
                    "Dump threads did not finish");
        } finally {
            workers.shutdownNow();
            dumpers.shutdownNow();
        }

        assertTrue(dumpCount.get() > 0,
                "No successful dump() calls recorded; test did not exercise the race");
        System.out.printf("ProcessCallTracesRaceTest: %d dumps, %d work units%n",
                dumpCount.get(), workCount.get());
    }
}
