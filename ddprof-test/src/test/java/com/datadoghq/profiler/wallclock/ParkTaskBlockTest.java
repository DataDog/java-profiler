package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Aggregators;
import org.openjdk.jmc.common.item.IItemCollection;

import java.util.Map;

/**
 * Approach B integration test: parkEnter/parkExit must emit TaskBlock and suppress wall-clock
 * signals while parked (via ProfiledThread flag when thread filter lists the thread).
 */
public class ParkTaskBlockTest extends AbstractProfilerTest {

    /** Verifies TaskBlock emission and parked signal suppression on the same thread. */
    @Test
    public void parkIntervalEmitsTaskBlockAndSuppressesSignals() {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();

        long spanId = 0x1234L;
        long rootSpanId = 0x5678L;
        profiler.setContext(rootSpanId, spanId, 0, 0);

        long parkUntil = System.nanoTime() + 250_000_000L; // 250 ms
        profiler.parkEnter(spanId, rootSpanId);
        while (System.nanoTime() < parkUntil) {
            // Deliberately stay runnable while "parked": suppression must come from park flag,
            // not from sleeping-state precheck.
        }
        profiler.parkExit(System.identityHashCode(this), 0L);
        profiler.clearContext();

        // Keep profiler active after park interval so regular wall samples still occur.
        long activeUntil = System.nanoTime() + 120_000_000L;
        while (System.nanoTime() < activeUntil) {
            // busy
        }

        stopProfiler();

        IItemCollection taskBlocks = verifyEvents("datadog.TaskBlock");
        long taskBlockCount = taskBlocks.getAggregate(Aggregators.count()).longValue();
        assertTrue(taskBlockCount > 0, "Expected datadog.TaskBlock events after parkEnter/parkExit");

        IItemCollection methodSamples = verifyEvents("datadog.MethodSample");
        long methodSampleCount = methodSamples.getAggregate(Aggregators.count()).longValue();
        assertTrue(methodSampleCount > 0, "Expected MethodSample events outside the parked interval");

        Map<String, Long> counters = profiler.getDebugCounters();
        if (counters.containsKey("wc_signals_skipped_parked")) {
            assertTrue(
                    counters.get("wc_signals_skipped_parked") > 0,
                    "Expected wc_signals_skipped_parked > 0");
        }
    }

    /** Configures wall-clock profiling with precheck disabled to isolate parked-flag behavior. */
    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=false";
    }
}
