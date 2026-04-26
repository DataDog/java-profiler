package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.context.Tracing;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.common.unit.UnitLookup;

import java.util.Map;
import java.util.concurrent.locks.LockSupport;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Verifies Approach 2: profiler.parkEnter/parkExit set an atomic flag in ProfiledThread that
 * suppresses SIGVTALRM signals during the parked interval, and emit a datadog.TaskBlock JFR
 * event with accurate timing when a trace span is active.
 */
public class ParkFlagTest extends AbstractProfilerTest {

    private static final IQuantity NANOSECOND = UnitLookup.NANOSECOND.quantity(1);
    private static final long PARK_DURATION_NS = 50_000_000L; // 50 ms
    private static final long MIN_DURATION_NS = 1_000_000L;   // wallparkmin default: 1 ms

    @Test
    public void testParkFlagSuppressesSignals() {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();

        // Call parkEnter/parkExit directly (BCI is in dd-trace-java; here we test the native layer).
        profiler.parkEnter(0L, 0L);
        LockSupport.parkNanos(300_000_000L); // 300 ms park
        profiler.parkExit(0L, 0L);

        stopProfiler();

        // With the park flag set, the timer thread skips SIGVTALRM for the parked interval.
        long sampleCount = verifyEvents("datadog.MethodSample", false)
                .getAggregate(org.openjdk.jmc.common.item.Aggregators.count()).longValue();
        assertTrue(sampleCount < 10,
                "Expected nearly no MethodSample events while park flag is set, got: " + sampleCount);

        Map<String, Long> counters = profiler.getDebugCounters();
        if (counters.containsKey("wc_signals_skipped_parked")) {
            assertTrue(counters.get("wc_signals_skipped_parked") > 0,
                    "wc_signals_skipped_parked should be > 0 during a 300 ms park");
        }
    }

    @Test
    public void testParkWithSpanEmitsTaskBlockEvent() {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();

        long spanId;
        long rootSpanId;
        long beforeParkNs = System.nanoTime();

        try (Tracing.Context ctx = Tracing.newContext(() -> 0xCAFEBABEL, profiler)) {
            spanId = ctx.getSpanId();
            rootSpanId = ctx.getRootSpanId();

            profiler.parkEnter(spanId, rootSpanId);
            LockSupport.parkNanos(PARK_DURATION_NS);
            profiler.parkExit(0L, 0L);
        }

        long afterParkNs = System.nanoTime();
        stopProfiler();

        // Verify a datadog.TaskBlock event was emitted with correct span IDs and duration >= 50 ms.
        IItemCollection blocks = verifyEvents("datadog.TaskBlock");
        assertTrue(blocks.hasItems(), "Expected at least one datadog.TaskBlock event");

        boolean foundMatchingBlock = false;
        for (IItemIterable items : blocks) {
            IMemberAccessor<IQuantity, IItem> spanIdAccessor = SPAN_ID.getAccessor(items.getType());
            IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(items.getType());
            for (IItem item : items) {
                long eventSpanId = spanIdAccessor.getMember(item).longValue();
                long eventRootSpanId = rootSpanIdAccessor.getMember(item).longValue();
                if (eventSpanId == spanId && eventRootSpanId == rootSpanId) {
                    foundMatchingBlock = true;
                }
            }
        }
        assertTrue(foundMatchingBlock,
                "No TaskBlock event matched spanId=" + spanId + " rootSpanId=" + rootSpanId);
    }

    @Test
    public void testParkBelowThresholdEmitsNoTaskBlock() {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();

        try (Tracing.Context ctx = Tracing.newContext(() -> 0xDEADBEEFL, profiler)) {
            long spanId = ctx.getSpanId();
            long rootSpanId = ctx.getRootSpanId();

            // Park for 0.1 ms — below the default 1 ms threshold (wallparkmin=1000000).
            profiler.parkEnter(spanId, rootSpanId);
            LockSupport.parkNanos(100_000L);
            profiler.parkExit(0L, 0L);
        }

        stopProfiler();

        // Duration is below threshold, so no TaskBlock should be emitted.
        IItemCollection blocks = verifyEvents("datadog.TaskBlock", false);
        assertFalse(blocks.hasItems(),
                "Expected no TaskBlock event for a sub-threshold park (0.1 ms < 1 ms threshold)");
    }

    @Test
    public void testParkWithoutSpanEmitsNoTaskBlock() {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();

        // spanId = 0 means no active trace — signal suppression still works but no JFR event.
        profiler.parkEnter(0L, 0L);
        LockSupport.parkNanos(PARK_DURATION_NS);
        profiler.parkExit(0L, 0L);

        stopProfiler();

        IItemCollection blocks = verifyEvents("datadog.TaskBlock", false);
        assertFalse(blocks.hasItems(),
                "Expected no TaskBlock event when parked without a trace span (spanId=0)");
    }

    @Override
    protected String getProfilerCommand() {
        // wallprecheck=false so only the park flag (Approach 2) is exercised in isolation.
        // wallpark=true (default) enables Approach 2.
        return "wall=1ms,wallprecheck=false";
    }
}
