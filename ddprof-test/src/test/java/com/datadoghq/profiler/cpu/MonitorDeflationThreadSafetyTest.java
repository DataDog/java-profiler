package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junitpioneer.jupiter.RetryingTest;

/**
 * Reproducer for the MonitorDeflationThread crash seen in JDK 25.0.2+.
 *
 * Root cause: profiling signals can interrupt any JVM thread, including
 * JVM-internal threads such as MonitorDeflationThread.  These threads are
 * JavaThread subclasses in the JVM's type hierarchy, but they are NOT Java
 * application threads: fields such as the frame anchor, vframe_top, and
 * continuation entry are not valid on them.  Before the fix, walkVM
 * dereferenced those fields unconditionally for every non-null VMThread,
 * which caused crashes inside MonitorDeflationThread.
 *
 * Fix: VMThread::isJavaThread() gates all JavaThread-only field accesses
 * (anchor(), inDeopt(), compiledMethod(), …).  It uses a two-step check:
 *   1. Fast path — a JVMTI ThreadStart-cached flag on ProfiledThread.
 *   2. Slow path — vtable majority vote (2-of-3 entries match a known
 *      JavaThread) for threads that bypass the JVMTI callback (compiler
 *      threads, MonitorDeflationThread, etc.).
 *
 * This test forces ObjectMonitor inflation and deflation to race with CPU
 * profiler signal delivery.  If the fix regresses, the JVM will crash with
 * a SIGSEGV or SIGBUS inside MonitorDeflationThread before the test ends.
 */
public class MonitorDeflationThreadSafetyTest extends AbstractProfilerTest {

    // Number of ObjectMonitors to inflate per wave — enough to keep
    // MonitorDeflationThread busy between waves.
    private static final int MONITOR_COUNT = 500;

    // Total duration of monitor churn while the profiler is active (ms).
    private static final int CHURN_DURATION_MS = 3000;

    // Gap between waves — lets MonitorDeflationThread observe and deflate the
    // idle monitors (it runs approximately every 250 ms by default).
    private static final int WAVE_SLEEP_MS = 300;

    @RetryingTest(3)
    public void monitorDeflationDoesNotCrashProfiler() throws Exception {
        // The profiler is already started by AbstractProfilerTest.setupProfiler().
        // Run monitor churn on the test thread so the CPU profiler definitely
        // delivers signals during the deflation window.
        inflateAndDeflateMonitors(CHURN_DURATION_MS, WAVE_SLEEP_MS);
        stopProfiler();

        // Reaching this line means the JVM survived — no crash in
        // MonitorDeflationThread.  Verify the profiler produced samples to
        // confirm that signals were actually delivered during the churn.
        verifyEvents("datadog.ExecutionSample");
    }

    /**
     * Repeatedly inflates then releases a batch of ObjectMonitors, sleeping
     * between waves so MonitorDeflationThread can reclaim them.
     *
     * Object.wait(timeout) while holding a lock forces monitor inflation to a
     * full ObjectMonitor.  Releasing the lock makes the monitor eligible for
     * deflation on the next MonitorDeflationThread pass.
     */
    private static void inflateAndDeflateMonitors(long durationMs, long waveSleepMs)
            throws InterruptedException {
        Object[] monitors = new Object[MONITOR_COUNT];
        for (int i = 0; i < monitors.length; i++) {
            monitors[i] = new Object();
        }

        long deadlineNs = System.nanoTime() + durationMs * 1_000_000L;
        while (System.nanoTime() < deadlineNs) {
            for (Object mon : monitors) {
                synchronized (mon) {
                    mon.wait(1);
                }
            }
            Thread.sleep(waveSleepMs);
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms";
    }
}
