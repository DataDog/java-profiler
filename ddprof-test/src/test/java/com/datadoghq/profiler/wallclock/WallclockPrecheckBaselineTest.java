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
 * Cross-recording proof of the gap-fill property.
 *
 * <p>Recording A ({@code wallprecheck=false}): every {@code SIGVTALRM} fires; almost every
 * {@code PARKED MethodSample} on the worker should lie inside some {@code TaskBlock} interval
 * on the worker, because {@code parkEnter}/{@code parkExit} fences exactly the kernel-wait
 * time during which {@code PARKED} state is observable.
 *
 * <p>Recording B ({@code wallprecheck=true}): the same workload produces the same
 * {@code TaskBlock} intervals (parkEnter/parkExit is filter-independent), but those intervals
 * are now empty of {@code PARKED MethodSamples} — the once-per-run filter has suppressed every
 * signal during the runs.
 *
 * <p>Together, the two checks form the gap-fill proof: each {@code TaskBlock} interval contained
 * sample(s) in baseline (recording A) and is empty under the filter (recording B), so the
 * {@code TaskBlock} interval covers the slot left by suppression one-for-one.
 *
 * <p>{@link TaskBlockCoverageTest} is the within-recording counterpart that exercises recording-B
 * containment in isolation.
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
        // wallprecheck reads HotSpot OSThreadState; JDK 8 misreports sleep / park states.
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

        // Recording A: wallprecheck=false (started by @BeforeEach via getProfilerCommand()).
        runParkWorkload(WORKER_A);
        stopProfiler();
        List<Interval> taskBlocksA =
                collectIntervals(verifyEvents("datadog.TaskBlock"), WORKER_A, false);
        List<Interval> parkedSamplesA =
                collectIntervals(verifyEvents("datadog.MethodSample", false), WORKER_A, true);

        // Recording B: wallprecheck=true, same workload, separate JFR file.
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

        // Structural: parkEnter/parkExit must emit in both modes (filter is sample-side only).
        long minTb = PARK_RUNS / 2L;
        assertTrue(taskBlocksA.size() >= minTb,
                "recording A: expected ≥" + minTb + " TaskBlocks, got " + taskBlocksA.size());
        assertTrue(taskBlocksB.size() >= minTb,
                "recording B: expected ≥" + minTb + " TaskBlocks, got " + taskBlocksB.size());

        // The baseline must have enough PARKED samples for the coverage ratio to be meaningful.
        assertTrue(parkedSamplesA.size() >= 10,
                "recording A: expected ≥10 PARKED samples to make coverage check meaningful, got "
                        + parkedSamplesA.size());

        // Baseline containment: ≥80% of PARKED MethodSamples on the worker in recording A lie
        // inside some TaskBlock interval on the worker. This proves the TaskBlock interval
        // temporally contains the moments where signals fire on a parked thread — i.e. the
        // interval physically covers what the filter would later suppress.
        double coverageRatioA = (double) coveredA / parkedSamplesA.size();
        assertTrue(coverageRatioA >= 0.8,
                "recording A: expected ≥80% of PARKED samples to lie inside TaskBlock intervals, "
                        + "got " + coveredA + " / " + parkedSamplesA.size()
                        + " = " + String.format("%.1f%%", 100.0 * coverageRatioA));

        // Gap-fill under filter: ≥95% of TaskBlock intervals on the worker in recording B
        // contain zero PARKED samples on the worker. Combined with the recording A check, this
        // proves the filter created gaps in MethodSample emission that the TaskBlock intervals
        // cover one-for-one.
        double gapRatioB = (double) emptyTaskBlocksB / taskBlocksB.size();
        assertTrue(gapRatioB >= 0.95,
                "recording B: expected ≥95% of TaskBlock intervals to be empty of PARKED samples, "
                        + "got " + emptyTaskBlocksB + " / " + taskBlocksB.size()
                        + " = " + String.format("%.1f%%", 100.0 * gapRatioB));

        // Per-interval strict invariant of the once-per-run filter: a TaskBlock interval is
        // one CONDVAR_WAIT run by construction, so at most one PARKED MethodSample may fall
        // inside any single TaskBlock interval — never two. Complements the gap-ratio check
        // above (which bounds how many intervals carry an entry sample at all).
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
            // TaskBlock emission requires a non-zero spanId — taskBlockRecorder skips otherwise.
            long spanId = 0x1234L;
            long rootSpanId = 0x5678L;
            profiler.setContext(rootSpanId, spanId, 0, 0);
            try {
                for (int i = 0; i < PARK_RUNS; i++) {
                    profiler.parkEnter();
                    LockSupport.parkNanos(PARK_NANOS);
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
        // Recording A: wallprecheck explicitly disabled (every signal fires).
        return "wall=" + SAMPLING_INTERVAL_MS + "ms,wallprecheck=false,filter=0";
    }
}
