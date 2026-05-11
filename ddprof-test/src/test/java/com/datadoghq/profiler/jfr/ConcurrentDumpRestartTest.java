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
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Regression test for PROF-14583: SIGSEGV in std::_Rb_tree_increment during
 * Recording::writeCpool when Profiler::start(reset=true) races with dump().
 *
 * The race: _class_map.clear() in Profiler::start runs concurrently with
 * Dictionary::collect() inside Recording::writeClasses, corrupting rbtree node
 * pointers and causing a SIGSEGV in std::_Rb_tree_increment.
 *
 * A crash aborts the JVM and causes a non-zero exit code, which JUnit reports
 * as a test failure. Passing means the fix holds.
 */
public class ConcurrentDumpRestartTest extends CStackAwareAbstractProfilerTest {

    private static final int TEST_DURATION_SECS = 10;
    private static final int ALLOC_THREADS = 4;

    public ConcurrentDumpRestartTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected boolean isPlatformSupported() {
        return !Platform.isJ9() && Platform.isJavaVersionAtLeast(11);
    }

    @Override
    protected String getProfilerCommand() {
        return "alloc=1ms,wall=5ms";
    }

    @RetryTest(2)
    @Timeout(value = 60)
    @TestTemplate
    @ValueSource(strings = {"vm"})
    public void dumpWhileRestarting(@CStack String cstack) throws Exception {
        Assumptions.assumeTrue(!Platform.isZing(), "Zing forces cstack=no, skipping");

        AtomicInteger dumpCount = new AtomicInteger(0);
        AtomicInteger restartCount = new AtomicInteger(0);
        CountDownLatch workersStarted = new CountDownLatch(1);

        long deadline = System.currentTimeMillis() + TEST_DURATION_SECS * 1000L;

        // Allocating threads populate _class_map via ObjectSampler -> lookupClass
        ExecutorService allocators = Executors.newFixedThreadPool(ALLOC_THREADS);
        for (int i = 0; i < ALLOC_THREADS; i++) {
            allocators.submit(() -> {
                workersStarted.countDown();
                while (!Thread.currentThread().isInterrupted() && System.currentTimeMillis() < deadline) {
                    @SuppressWarnings("unused")
                    byte[] ignored = new byte[1024];
                }
            });
        }

        assertTrue(workersStarted.await(5, TimeUnit.SECONDS),
            "Allocating workers did not start within 5 seconds");

        // Restart thread: stop + start triggers _class_map.clear() in Profiler::start,
        // racing with Dictionary::collect() inside Recording::writeClasses during dump()
        Thread restarter = new Thread(() -> {
            while (!Thread.currentThread().isInterrupted() && System.currentTimeMillis() < deadline) {
                try {
                    profiler.stop();
                    Path restartJfr = Files.createTempFile("restart-", ".jfr");
                    try {
                        profiler.execute("start,alloc=1ms,wall=5ms,cstack=vm,jfr,file=" + restartJfr.toAbsolutePath());
                        restartCount.incrementAndGet();
                        Thread.sleep(50);
                    } finally {
                        Files.deleteIfExists(restartJfr);
                    }
                } catch (Exception e) {
                    Thread.currentThread().interrupt();
                }
            }
        });
        restarter.setDaemon(true);
        restarter.start();

        // Dump repeatedly while the restarter churns through stop/start cycles
        try {
            while (System.currentTimeMillis() < deadline) {
                Path recording = Files.createTempFile("dump-restart-", ".jfr");
                try {
                    profiler.dump(recording);
                    dumpCount.incrementAndGet();
                } finally {
                    Files.deleteIfExists(recording);
                }
                Thread.sleep(100);
            }
        } finally {
            restarter.interrupt();
            restarter.join(5000);
            allocators.shutdown();
            if (!allocators.awaitTermination(5, TimeUnit.SECONDS)) {
                allocators.shutdownNow();
            }
        }

        assertTrue(dumpCount.get() >= 5,
            "Expected at least 5 dumps, got " + dumpCount.get() +
            " (restarts=" + restartCount.get() + ")");
        assertTrue(restartCount.get() >= 3,
            "Expected at least 3 restarts, got " + restartCount.get());
    }
}
