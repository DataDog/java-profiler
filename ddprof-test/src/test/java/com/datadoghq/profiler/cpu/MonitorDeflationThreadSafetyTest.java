package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.junitpioneer.jupiter.RetryingTest;

/**
 * Regression test for the MonitorDeflationThread crash in JDK 25.0.2+.
 *
 * Root cause: walkVM() unconditionally wrote a jmp_buf address into
 * ThreadShadow::_exception_file for every non-null VMThread, including
 * JVM-internal threads such as MonitorDeflationThread.  In JDK 25,
 * ObjectMonitorDeflationSafepointer reads thread state (including
 * _exception_file) at safepoint boundaries; finding a stale jmp_buf
 * address instead of NULL or a C-string caused a crash in
 * deflate_monitor_list.
 *
 * Fix: gate the _exception_file write on VMThread::isJavaThread(), which
 * uses vtable comparison to distinguish regular Java application threads
 * from JVM-internal threads that are JavaThread subclasses in JDK 25+.
 *
 * This test forces ObjectMonitor inflation/deflation to race with CPU
 * profiler signal delivery.  If the fix regresses, the JVM will crash
 * with a SIGSEGV in deflate_monitor_list before the test completes.
 */
public class MonitorDeflationThreadSafetyTest extends AbstractProfilerTest {

    // Number of objects to synchronize on each wave — enough to ensure
    // MonitorDeflationThread has work to do between waves.
    private static final int MONITOR_COUNT = 500;

    // Total duration of monitor churn while the profiler is running (ms).
    private static final int CHURN_DURATION_MS = 3000;

    // Sleep between waves to give MonitorDeflationThread time to deflate
    // the monitors we released (it runs every ~250 ms by default).
    private static final int WAVE_SLEEP_MS = 300;

    @RetryingTest(3)
    public void monitorDeflationDoesNotCrashProfiler() throws Exception {
        // The profiler is already started by AbstractProfilerTest.setupProfiler().
        // Run the monitor churn on the test thread itself so the CPU profiler
        // definitely samples it, confirming signals are being delivered during
        // the deflation window.
        inflateAndDeflateMonitors(CHURN_DURATION_MS, WAVE_SLEEP_MS);
        stopProfiler();

        // If we reach this line the JVM survived — no SIGSEGV in
        // deflate_monitor_list.  Verify the profiler actually produced samples
        // to confirm signals were delivered while monitors were being deflated.
        verifyEvents("datadog.ExecutionSample");
    }

    /**
     * Repeatedly inflates then releases a batch of ObjectMonitors, sleeping
     * between waves so MonitorDeflationThread can reclaim them.
     *
     * Each synchronized block on a freshly-allocated Object causes the JVM to
     * inflate that object's mark word into a full ObjectMonitor.  Releasing
     * the lock makes the monitor eligible for deflation.
     */
    private static void inflateAndDeflateMonitors(long durationMs, long waveSleepMs)
            throws InterruptedException {
        Object[] monitors = new Object[MONITOR_COUNT];
        for (int i = 0; i < monitors.length; i++) {
            monitors[i] = new Object();
        }

        long deadline = System.currentTimeMillis() + durationMs;
        while (System.currentTimeMillis() < deadline) {
            for (Object mon : monitors) {
                synchronized (mon) {
                    // wait() forces inflation to an ObjectMonitor and makes it eligible for deflation
                    mon.wait(1);
                }
            }

            // Sleep so MonitorDeflationThread can observe and deflate the
            // now-idle monitors while the CPU profiler is still sending signals.
            Thread.sleep(waveSleepMs);
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms";
    }
}
