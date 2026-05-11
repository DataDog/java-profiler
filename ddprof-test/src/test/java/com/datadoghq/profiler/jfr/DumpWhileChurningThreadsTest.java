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
 * Regression test for PROF-14548: SIGSEGV in Profiler::updateThreadName when a thread
 * terminates between GetAllThreads and the eetop dereference during dump().
 *
 * Exercises the race by churning short-lived threads while calling dump() repeatedly.
 * A SIGSEGV would abort the JVM and fail the test with a non-zero exit code.
 */
public class DumpWhileChurningThreadsTest extends CStackAwareAbstractProfilerTest {

    private static final int TEST_DURATION_SECS = 10;
    private static final int CHURN_THREADS = 50;

    public DumpWhileChurningThreadsTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected boolean isPlatformSupported() {
        return !Platform.isJ9() && Platform.isJavaVersionAtLeast(11);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=5ms";
    }

    @RetryTest(2)
    @Timeout(value = 60)
    @TestTemplate
    @ValueSource(strings = {"vm"})
    public void dumpWhileChurning(@CStack String cstack) throws Exception {
        Assumptions.assumeTrue(!Platform.isZing(), "Zing forces cstack=no, skipping");

        AtomicInteger dumpCount = new AtomicInteger(0);
        AtomicInteger threadStartCount = new AtomicInteger(0);
        CountDownLatch churnStarted = new CountDownLatch(1);

        ExecutorService executor = Executors.newFixedThreadPool(CHURN_THREADS);
        long deadline = System.currentTimeMillis() + TEST_DURATION_SECS * 1000L;

        // Start the churn task; each pool thread spawns short-lived tasks until deadline
        for (int i = 0; i < CHURN_THREADS; i++) {
            executor.submit(() -> {
                churnStarted.countDown();
                while (System.currentTimeMillis() < deadline) {
                    Thread t = new Thread(() -> threadStartCount.incrementAndGet());
                    t.start();
                    try {
                        t.join(5);
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        return;
                    }
                }
            });
        }

        // Wait for at least one churn thread to be running before starting dumps
        assertTrue(churnStarted.await(5, TimeUnit.SECONDS),
            "Churn tasks did not start within 5 seconds");

        // Dump repeatedly while churn runs
        try {
            while (System.currentTimeMillis() < deadline) {
                Path recording = Files.createTempFile("dump-churn-", ".jfr");
                try {
                    dump(recording);
                    dumpCount.incrementAndGet();
                } finally {
                    Files.deleteIfExists(recording);
                }
                Thread.sleep(200);
            }
        } finally {
            executor.shutdown();
            if (!executor.awaitTermination(5, TimeUnit.SECONDS)) {
                executor.shutdownNow();
            }
        }

        assertTrue(dumpCount.get() >= 10,
            "Expected at least 10 dumps during churn, got " + dumpCount.get()
            + " (threadStarts=" + threadStartCount.get() + ")");
    }
}
