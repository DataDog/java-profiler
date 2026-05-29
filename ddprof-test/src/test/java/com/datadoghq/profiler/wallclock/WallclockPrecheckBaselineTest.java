package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.unit.UnitLookup.EPOCH_NS;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.LockSupport;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.common.unit.IRange;
import org.openjdk.jmc.flightrecorder.JfrAttributes;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

/**
 * Cross-recording gap-fill proof: recording A ({@code wallprecheck=false}) shows PARKED
 * MethodSamples inside TaskBlock intervals; recording B ({@code wallprecheck=true}) shows those
 * same intervals empty of PARKED samples — the once-per-run filter suppressed them and the
 * TaskBlock interval covers the gap one-for-one.
 */
public class WallclockPrecheckBaselineTest extends AbstractProfilerTest {

    private static final String WORKER_A = "wallprecheck-baseline-A";
    private static final String WORKER_B = "wallprecheck-baseline-B";
    private static final int PARK_RUNS = 200;
    private static final long PARK_NANOS = 50_000_000L;
    private static final long SAMPLING_INTERVAL_MS = 10L;

    @Test
    public void taskBlocksAccountForSuppressedSamples() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

        runParkWorkload(WORKER_A);
        stopProfiler();
        List<Interval> taskBlocksA =
                collectIntervals(verifyEvents("datadog.TaskBlock"), WORKER_A, false);
        List<Interval> parkedSamplesA =
                collectIntervals(verifyEvents("datadog.MethodSample", false), WORKER_A, true);

        Path recordingB = Files.createTempFile(Paths.get("/tmp/recordings"),
                "WallclockPrecheckBaselineTest_B_", ".jfr");
        profiler.execute("start,wall=" + SAMPLING_INTERVAL_MS + "ms,wallprecheck=true,filter=0"
                + ",attributes=tag1;tag2;tag3,jfr,file=" + recordingB.toAbsolutePath());
        runParkWorkload(WORKER_B);
        profiler.stop();

        List<Interval> taskBlocksB =
                collectIntervals(verifyEvents(recordingB, "datadog.TaskBlock", true), WORKER_B, false);
        List<Interval> parkedSamplesB =
                collectIntervals(verifyEvents(recordingB, "datadog.MethodSample", false), WORKER_B, true);

        Files.deleteIfExists(recordingB);

        long coveredA = countSamplesInsideAnyInterval(parkedSamplesA, taskBlocksA);
        long emptyTaskBlocksB = countIntervalsWithoutAnySample(taskBlocksB, parkedSamplesB);

        System.out.printf(
                "%nWallclockPrecheckBaselineTest:%n"
                        + "  Recording A (precheck=false): TaskBlocks=%d, PARKED MethodSamples=%d, "
                        + "PARKED inside any TaskBlock=%d%n"
                        + "  Recording B (precheck=true ): TaskBlocks=%d, PARKED MethodSamples=%d, "
                        + "empty TaskBlock intervals=%d%n",
                taskBlocksA.size(), parkedSamplesA.size(), coveredA,
                taskBlocksB.size(), parkedSamplesB.size(), emptyTaskBlocksB);

        long minTb = PARK_RUNS / 2L;
        assertTrue(taskBlocksA.size() >= minTb,
                "recording A: expected ≥" + minTb + " TaskBlocks, got " + taskBlocksA.size());
        assertTrue(taskBlocksB.size() >= minTb,
                "recording B: expected ≥" + minTb + " TaskBlocks, got " + taskBlocksB.size());

        assertTrue(parkedSamplesA.size() >= 10,
                "recording A: expected ≥10 PARKED samples to make coverage check meaningful, got "
                        + parkedSamplesA.size());

        // Recording A: ≥80% of PARKED samples inside a TaskBlock interval.
        double coverageRatioA = (double) coveredA / parkedSamplesA.size();
        assertTrue(coverageRatioA >= 0.8,
                "recording A: expected ≥80% of PARKED samples to lie inside TaskBlock intervals, "
                        + "got " + coveredA + " / " + parkedSamplesA.size()
                        + " = " + String.format("%.1f%%", 100.0 * coverageRatioA));

        // Recording B: ≥95% of TaskBlock intervals empty of PARKED samples.
        double gapRatioB = (double) emptyTaskBlocksB / taskBlocksB.size();
        assertTrue(gapRatioB >= 0.95,
                "recording B: expected ≥95% of TaskBlock intervals to be empty of PARKED samples, "
                        + "got " + emptyTaskBlocksB + " / " + taskBlocksB.size()
                        + " = " + String.format("%.1f%%", 100.0 * gapRatioB));

        // At most one PARKED sample per TaskBlock interval (one run → one entry sample).
        int maxSamplesInAnyTaskBlockB = 0;
        int worstTaskBlockIdxB = -1;
        for (int i = 0; i < taskBlocksB.size(); i++) {
            Interval tb = taskBlocksB.get(i);
            int count = 0;
            for (Interval s : parkedSamplesB) {
                if (s.startNs >= tb.startNs && s.startNs <= tb.endNs) {
                    count++;
                }
            }
            if (count > maxSamplesInAnyTaskBlockB) {
                maxSamplesInAnyTaskBlockB = count;
                worstTaskBlockIdxB = i;
            }
        }
        assertTrue(maxSamplesInAnyTaskBlockB <= 1,
                "recording B: expected at most one PARKED MethodSample per TaskBlock interval, "
                        + "TaskBlock #" + worstTaskBlockIdxB + " contained "
                        + maxSamplesInAnyTaskBlockB + " PARKED samples");
    }

    private void runParkWorkload(String workerName) throws Exception {
        Thread worker = new Thread(() -> {
            registerCurrentThreadForWallClockProfiling();
            long spanId = 0x1234L;
            long rootSpanId = 0x5678L;
            profiler.setContext(rootSpanId, spanId, 0, 0);
            try {
                for (int i = 0; i < PARK_RUNS; i++) {
                    profiler.parkEnter();
                    LockSupport.parkNanos(PARK_NANOS); // SIGVTALRM may interrupt early; TaskBlock still emits
                    profiler.parkExit(System.identityHashCode(this), 0L);
                }
            } finally {
                profiler.clearContext();
            }
        }, workerName);
        worker.setDaemon(true);
        worker.start();
        worker.join();
    }

    private static final class Interval {
        final long startNs;
        final long endNs;
        Interval(long startNs, long endNs) {
            this.startNs = startNs;
            this.endNs = endNs;
        }
    }

    private List<Interval> collectIntervals(IItemCollection events, String workerName,
                                            boolean requirePARKEDState) throws Exception {
        List<Interval> out = new ArrayList<>();
        for (IItemIterable batch : events) {
            IMemberAccessor<String, IItem> threadNameAccessor =
                    JdkAttributes.EVENT_THREAD_NAME.getAccessor(batch.getType());
            IMemberAccessor<IRange<IQuantity>, IItem> lifetimeAccessor =
                    JfrAttributes.LIFETIME.getAccessor(batch.getType());
            IMemberAccessor<String, IItem> stateAccessor =
                    requirePARKEDState ? THREAD_STATE.getAccessor(batch.getType()) : null;
            if (threadNameAccessor == null || lifetimeAccessor == null) continue;
            if (requirePARKEDState && stateAccessor == null) continue;
            for (IItem item : batch) {
                if (!workerName.equals(threadNameAccessor.getMember(item))) continue;
                if (requirePARKEDState && !"PARKED".equals(stateAccessor.getMember(item))) continue;
                IRange<IQuantity> lifetime = lifetimeAccessor.getMember(item);
                long startNs = lifetime.getStart().longValueIn(EPOCH_NS);
                long endNs = lifetime.getEnd().longValueIn(EPOCH_NS);
                out.add(new Interval(startNs, endNs));
            }
        }
        return out;
    }

    private static long countSamplesInsideAnyInterval(List<Interval> samples,
                                                      List<Interval> intervals) {
        long count = 0;
        for (Interval s : samples) {
            for (Interval iv : intervals) {
                if (s.startNs >= iv.startNs && s.startNs <= iv.endNs) {
                    count++;
                    break;
                }
            }
        }
        return count;
    }

    private static long countIntervalsWithoutAnySample(List<Interval> intervals,
                                                       List<Interval> samples) {
        long count = 0;
        for (Interval iv : intervals) {
            boolean hasSample = false;
            for (Interval s : samples) {
                if (s.startNs >= iv.startNs && s.startNs <= iv.endNs) {
                    hasSample = true;
                    break;
                }
            }
            if (!hasSample) count++;
        }
        return count;
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=" + SAMPLING_INTERVAL_MS + "ms,wallprecheck=false,filter=0";
    }
}
