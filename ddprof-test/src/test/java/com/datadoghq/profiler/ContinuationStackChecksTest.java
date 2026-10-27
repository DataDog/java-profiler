/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler;

import com.datadoghq.profiler.chaos.VirtualThreadRemountAntagonist;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import org.junit.jupiter.api.Test;
import org.opentest4j.MultipleFailuresError;

import static org.junit.jupiter.api.Assertions.assertAll;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Exercises the chaos recording oracle with resolved JFR samples, including failure substitutions. */
public class ContinuationStackChecksTest {
    private static final String WORKLOAD = VirtualThreadRemountAntagonist.class.getName();
    private static final String CARRIER = "java.util.concurrent.ForkJoinWorkerThread#run";

    private static Map<String, Object> fields(Object... pairs) {
        Map<String, Object> values = new HashMap<>();
        for (int i = 0; i < pairs.length; i += 2) values.put((String) pairs[i], pairs[i + 1]);
        return values;
    }

    /** Builds the same resolved field layout consumed from an actual profiler recording. */
    private static JfrEvent sample(long carrier, boolean truncated, String... frames) {
        Object[] stack = Arrays.stream(frames).map(frame -> {
            String[] name = frame.split("#", -1);
            return fields("method", fields("type", fields("name", name[0]), "name", name[1]));
        }).toArray();
        return new JfrEvent("datadog.ExecutionSample", fields(
                "eventThread", fields("osThreadId", carrier, "osName", "carrier-" + carrier),
                "stackTrace", fields("frames", stack, "truncated", truncated)));
    }

    private static ContinuationStackChecks covered(boolean carriers, int samplesPerLayout) {
        ContinuationStackChecks checks = new ContinuationStackChecks(carriers, Collections.singleton(7L));
        for (int i = 0; i < samplesPerLayout; i++) {
            for (String method : new String[]{"registerFrames", "stackFrames"}) {
                checks.accept(sample(7, true, WORKLOAD + "#" + method, carriers ? CARRIER : "#JVM Continuation"));
            }
        }
        return checks;
    }

    /** Both VM modes must accept valid, truncated partial walks in both argument layouts. */
    @Test
    public void acceptsCoveredPartialWalksInBothModes() {
        covered(false, 10).assertValid("wall");
        covered(true, 10).assertValid("cpu");
    }

    /** A complete idle scheduler chain identifies a parked carrier, even with a native gap. */
    private static JfrEvent idleSample(long carrier, boolean truncated, String parkMethod, String... prefix) {
        String[] frames = Arrays.copyOf(prefix, prefix.length + 5);
        frames[prefix.length] = "jdk.internal.misc.Unsafe#park";
        frames[prefix.length + 1] = "java.util.concurrent.locks.LockSupport#" + parkMethod;
        frames[prefix.length + 2] = "java.util.concurrent.ForkJoinPool#awaitWork";
        frames[prefix.length + 3] = "java.util.concurrent.ForkJoinPool#runWorker";
        frames[prefix.length + 4] = CARRIER;
        return sample(carrier, truncated, frames);
    }

    /** Confirmed idle gaps remain visible but do not consume continuation coverage or its budget. */
    @Test
    public void excludesConfirmedIdleNativeGapBurstsFromContinuationBudget() {
        for (boolean carriers : new boolean[]{false, true}) {
            for (boolean truncated : new boolean[]{false, true}) {
                for (String park : new String[]{"park", "parkUntil", "parkNanos"}) {
                    ContinuationStackChecks checks = covered(carriers, 10);
                    for (int i = 0; i < 1000; i++) {
                        checks.accept(idleSample(7, truncated, park, "#__syscall_cancel_arch_start", "#[skipped frames]"));
                    }
                    checks.assertValid("wall");
                    assertTrue(checks.toString().contains("idleNativeGaps=1000"));
                    assertTrue(checks.toString().contains("carrierOnlyFailures=0"));
                    assertTrue(checks.toString().contains("failureReasons={}"));
                }
            }
        }
    }

    /** No workload frames is insufficient evidence of idleness; all ordered scheduler frames are required. */
    @Test
    public void rejectsIncompleteMisorderedOrDuplicatedIdleSignatures() {
        String unsafe = "jdk.internal.misc.Unsafe#park";
        String await = "java.util.concurrent.ForkJoinPool#awaitWork";
        String worker = "java.util.concurrent.ForkJoinPool#runWorker";
        for (String[] frames : new String[][]{
                {"#[skipped frames]", await, worker, CARRIER},
                {"#[skipped frames]", unsafe, worker, CARRIER},
                {"#[skipped frames]", unsafe, await, CARRIER},
                {"#[skipped frames]", unsafe, await, worker},
                {"#[skipped frames]", unsafe, worker, await, CARRIER},
                {"#[skipped frames]", CARRIER, unsafe, await, worker},
                {"#[skipped frames]", unsafe, await, worker, CARRIER, CARRIER}}) {
            ContinuationStackChecks checks = covered(true, 10);
            checks.accept(sample(7, false, frames));
            assertThrows(AssertionError.class, () -> checks.assertValid("wall"));
            assertTrue(checks.toString().contains("idleNativeGaps=0"));
            assertTrue(checks.toString().contains("carrierOnlyFailures=1"));
        }
    }

    /** Application or continuation evidence prevents an idle-looking suffix from hiding a failed walk. */
    @Test
    public void rejectsIdleLookingStacksWithApplicationOrContinuationFrames() {
        for (String frame : new String[]{WORKLOAD + "#registerFrames", WORKLOAD + "#registerWorkload",
                "example.Task#run", "jdk.internal.vm.Continuation#run", "java.lang.VirtualThread#runContinuation",
                "#JVM Continuation"}) {
            ContinuationStackChecks checks = covered(true, 10);
            checks.accept(idleSample(7, true, "park", "#[skipped frames]", frame));
            assertThrows(AssertionError.class, () -> checks.assertValid("cpu"));
            assertTrue(checks.toString().contains("idleNativeGaps=0"));
        }
    }

    /** A skipped marker must not conceal a second, more specific walk error on an idle-looking stack. */
    @Test
    public void rejectsOtherWalkErrorsAlongsideIdleNativeGaps() {
        for (String error : new String[]{"break_unwind_stub_failed", "break_not_walkable", "unknown_nmethod", "no_Java_frame"}) {
            for (boolean first : new boolean[]{false, true}) {
                ContinuationStackChecks checks = covered(true, 10);
                checks.accept(idleSample(7, false, "park", first ? "#" + error : "#[skipped frames]",
                        first ? "#[skipped frames]" : "#" + error));
                assertThrows(AssertionError.class, () -> checks.assertValid("cpu"));
                assertTrue(checks.toString().contains("idleNativeGaps=0"));
                assertTrue(checks.toString().contains("carrierOnlyFailures=1"));
            }
        }
    }

    /** Continuation errors remain unconditional failures on both known and unidentified idle-looking threads. */
    @Test
    public void rejectsContinuationErrorsAlongsideIdleNativeGaps() {
        for (long carrier : new long[]{7, 99}) {
            ContinuationStackChecks checks = covered(true, 100);
            checks.accept(idleSample(carrier, false, "park", "#[skipped frames]", "#break_cont_entry_fp"));
            MultipleFailuresError failure = assertThrows(MultipleFailuresError.class, () -> checks.assertValid("wall"));
            assertEquals(1, failure.getFailures().size());
            assertTrue(failure.getFailures().get(0).getMessage().startsWith("Continuation recovery errors"));
            assertTrue(checks.toString().contains("idleNativeGaps=0"));
        }
    }

    /** Excluded idle samples cannot improve the success ratio or hide ambiguous carrier failures. */
    @Test
    public void idleGapsCannotDiluteFailureBudget() {
        ContinuationStackChecks checks = covered(true, 10);
        for (int i = 0; i < 1000; i++) checks.accept(idleSample(7, false, "park", "#[skipped frames]"));
        checks.accept(sample(7, true, "#[skipped frames]", CARRIER));
        assertThrows(AssertionError.class, () -> checks.assertValid("wall"));
        assertTrue(checks.toString().contains("eligible=[10, 10]"));
        assertTrue(checks.toString().contains("carrierOnlyFailures=1"));
        assertTrue(checks.toString().contains("idleNativeGaps=1000"));
    }

    /** Complete workload ancestry can coexist with a skipped native region below the sampled leaf. */
    @Test
    public void acceptsNontruncatedNativeGapWithCompleteJavaAncestryWithinFailureBudget() {
        for (boolean carriers : new boolean[]{false, true}) {
            for (String layout : new String[]{"register", "stack"}) {
                ContinuationStackChecks checks = covered(carriers, 100);
                checks.accept(sample(7, false, "#native_leaf", "#[skipped frames]",
                        WORKLOAD + "#" + layout + "Frames", WORKLOAD + "#" + layout + "Workload",
                        carriers ? CARRIER : "#JVM Continuation"));
                checks.assertValid("cpu");
            }
        }
    }

    /** Workload gaps and ambiguous parked samples keep consuming the unchanged failure budget. */
    @Test
    public void rejectsNativeGapBurstsWithoutClaimingMissingJavaAncestry() {
        for (boolean carriers : new boolean[]{false, true}) {
            for (boolean workload : new boolean[]{false, true}) {
                ContinuationStackChecks checks = covered(carriers, 100);
                for (int i = 0; i < 10; i++) {
                    checks.accept(workload
                            ? sample(7, false, "#[skipped frames]", WORKLOAD + "#registerFrames",
                                    WORKLOAD + "#registerWorkload", carriers ? CARRIER : "#JVM Continuation")
                            : sample(7, false, "#[skipped frames]", "jdk.internal.misc.Unsafe#park", CARRIER));
                }
                MultipleFailuresError failure = assertThrows(MultipleFailuresError.class,
                        () -> checks.assertValid("wall"));
                assertEquals(workload ? 2 : 1, failure.getFailures().size());
                assertTrue(failure.getFailures().stream()
                        .allMatch(error -> error.getMessage().startsWith("Fewer than 99%")));
                assertTrue(failure.getMessage().contains("[skipped frames]=10"));
            }
        }
    }

    /** A native gap must not hide a missing caller or boundary that was reported complete. */
    @Test
    public void rejectsMissingJavaAncestorsWithOrWithoutNativeGap() {
        for (boolean carriers : new boolean[]{false, true}) {
            for (String layout : new String[]{"register", "stack"}) {
                for (boolean nativeGap : new boolean[]{false, true}) {
                    for (boolean boundary : new boolean[]{false, true}) {
                        ContinuationStackChecks checks = covered(carriers, 100);
                        checks.accept(sample(7, false, nativeGap ? "#[skipped frames]" : "#native_leaf",
                                WORKLOAD + "#" + layout + "Frames",
                                boundary ? (carriers ? CARRIER : "#JVM Continuation")
                                        : WORKLOAD + "#" + layout + "Workload"));
                        MultipleFailuresError failure = assertThrows(MultipleFailuresError.class,
                                () -> checks.assertValid("cpu"));
                        assertEquals(1, failure.getFailures().size());
                        assertTrue(failure.getFailures().get(0).getMessage()
                                .startsWith("Incomplete walks reported complete"));
                    }
                }
            }
        }
    }

    /** Truncation permits missing Java ancestors while a native gap still consumes the budget. */
    @Test
    public void acceptsTruncatedMissingJavaAncestorsWithNativeGapWithinFailureBudget() {
        for (boolean carriers : new boolean[]{false, true}) {
            for (String layout : new String[]{"register", "stack"}) {
                for (boolean boundary : new boolean[]{false, true}) {
                    ContinuationStackChecks checks = covered(carriers, 100);
                    checks.accept(sample(7, true, "#[skipped frames]", WORKLOAD + "#" + layout + "Frames",
                            boundary ? (carriers ? CARRIER : "#JVM Continuation") : "#native_frame"));
                    checks.assertValid("wall");
                }
            }
        }
    }

    /** Error markers must not bypass carrier uniqueness and ordering checks. */
    @Test
    public void rejectsInvalidCarrierAncestryDespiteNativeGap() {
        for (JfrEvent event : Arrays.asList(
                sample(7, true, "#[skipped frames]", WORKLOAD + "#registerFrames", CARRIER, CARRIER),
                sample(7, true, "#[skipped frames]", CARRIER, WORKLOAD + "#registerFrames"))) {
            ContinuationStackChecks checks = covered(true, 100);
            checks.accept(event);
            MultipleFailuresError failure = assertThrows(MultipleFailuresError.class,
                    () -> checks.assertValid("cpu"));
            assertEquals(1, failure.getFailures().size());
            assertTrue(failure.getFailures().get(0).getMessage()
                    .startsWith("Missing, duplicated or misplaced carrier frames"));
        }
    }

    /** Ten successful samples cannot conceal widespread generic failures without workload frames. */
    @Test
    public void rejectsGenericFailuresOnKnownCarriers() {
        ContinuationStackChecks checks = covered(true, 10);
        for (int i = 0; i < 1000; i++) checks.accept(sample(7, true, "#break_not_walkable"));
        AssertionError failure = assertThrows(AssertionError.class, () -> checks.assertValid("cpu"));
        assertTrue(failure.getMessage().contains("including carrier-only failures"));
        assertTrue(failure.getMessage().contains("carrier-7"));
        assertTrue(failure.getMessage().contains("break_not_walkable"));
    }

    /** Failures retain their layout even when a carrier frame happens to be present. */
    @Test
    public void rejectsFailedWalksThatStillReachCarrierAncestry() {
        ContinuationStackChecks checks = covered(true, 10);
        for (int i = 0; i < 100; i++) {
            checks.accept(sample(7, true, WORKLOAD + "#stackFrames", "#break_not_walkable", CARRIER));
        }
        AssertionError failure = assertThrows(AssertionError.class, () -> checks.assertValid("cpu"));
        assertTrue(failure.getMessage().contains("successful boundary walks for layout 1"));
    }

    /** One healthy layout must not hide a degraded layout in the combined success rate. */
    @Test
    public void boundsEachLayoutIndependently() {
        ContinuationStackChecks checks = covered(true, 10);
        for (int i = 0; i < 1000; i++) {
            checks.accept(sample(7, true, WORKLOAD + "#registerFrames", CARRIER));
        }
        checks.accept(sample(7, true, WORKLOAD + "#stackFrames", "#break_not_walkable"));
        MultipleFailuresError failure = assertThrows(MultipleFailuresError.class, () -> checks.assertValid("cpu"));
        assertEquals(1, failure.getFailures().size());
        assertTrue(failure.getMessage().contains("successful boundary walks for layout 1"));
    }

    /** Fully thawed samples cannot satisfy the required coverage of omitted outer callers. */
    @Test
    public void requiresPartialThawCoverageForEachLayout() {
        ContinuationStackChecks checks = new ContinuationStackChecks(true, Collections.singleton(7L));
        for (int i = 0; i < 10; i++) {
            checks.accept(sample(7, true, WORKLOAD + "#registerFrames", CARRIER));
            checks.accept(sample(7, false, WORKLOAD + "#stackFrames", WORKLOAD + "#stackWorkload", CARRIER));
        }
        MultipleFailuresError failure = assertThrows(MultipleFailuresError.class, () -> checks.assertValid("cpu"));
        assertEquals(1, failure.getFailures().size());
        assertTrue(failure.getMessage().contains("Insufficient partial-thaw samples for layout 1"));
    }

    /** Empty stacks on known carriers must not escape the generic failure budget. */
    @Test
    public void rejectsEmptyStacksOnKnownCarriers() {
        ContinuationStackChecks checks = covered(true, 10);
        checks.accept(sample(7, true));
        AssertionError failure = assertThrows(AssertionError.class, () -> checks.assertValid("cpu"));
        assertTrue(failure.getMessage().contains("reason=empty stack"));
    }

    /** Rare generic stops are bounded by the declared 99% gate, rather than an absolute count. */
    @Test
    public void boundsFailuresRelativeToSuccessfulSamples() {
        ContinuationStackChecks checks = covered(true, 100);
        checks.accept(sample(7, true, WORKLOAD + "#registerFrames", "#break_not_walkable"));
        checks.accept(sample(7, true, WORKLOAD + "#stackFrames", "#break_not_walkable"));
        checks.assertValid("cpu");
        checks.accept(sample(7, true, "#break_not_walkable"));
        assertThrows(AssertionError.class, () -> checks.assertValid("cpu"));
    }

    /** Unrelated native threads do not count against workload-carrier success. */
    @Test
    public void scopesGenericFailuresToIdentifiedCarriers() {
        ContinuationStackChecks checks = covered(true, 10);
        checks.accept(sample(99, true, "#break_not_walkable"));
        checks.assertValid("cpu");
        Set<Long> carriers = new HashSet<>();
        ContinuationStackChecks.collectCarriers(carriers, sample(7, true, WORKLOAD + "#registerFrames", CARRIER));
        assertEquals(Collections.singleton(7L), carriers);
    }

    /** Error-only continuation samples fail even when no workload frames or known carrier survive. */
    @Test
    public void rejectsContinuationErrorsWithoutApplicationFrames() {
        ContinuationStackChecks checks = covered(true, 10);
        checks.accept(sample(99, true, "#break_cont_entry_fp"));
        AssertionError failure = assertThrows(AssertionError.class, () -> checks.assertValid("wall"));
        assertTrue(failure.getMessage().contains("Continuation recovery errors"));
        assertTrue(failure.getMessage().contains("thread=carrier-99 osId=99 truncated=true"));
        assertTrue(failure.getMessage().contains(".break_cont_entry_fp"));
    }

    /** Wrong ancestry and omitted callers reported complete must remain failures. */
    @Test
    public void rejectsDuplicatedMisplacedOrFalselyCompleteAncestry() {
        for (JfrEvent event : Arrays.asList(
                sample(7, true, WORKLOAD + "#registerFrames", CARRIER, CARRIER),
                sample(7, true, CARRIER, WORKLOAD + "#registerFrames"),
                sample(7, false, WORKLOAD + "#registerFrames", CARRIER))) {
            ContinuationStackChecks checks = covered(true, 10);
            checks.accept(event);
            assertThrows(AssertionError.class, () -> checks.assertValid("cpu"));
        }
    }

    /** A CPU failure must not prevent reporting the independent wall-clock failure. */
    @Test
    public void reportsBothSamplingEnginesWhenBothFail() {
        ContinuationStackChecks cpu = covered(true, 10), wall = covered(true, 10);
        cpu.accept(sample(7, true, "#break_cont_entry_fp"));
        wall.accept(sample(7, true, "#break_cont_carrier_sp"));
        MultipleFailuresError failure = assertThrows(MultipleFailuresError.class,
                () -> assertAll(() -> cpu.assertValid("cpu"), () -> wall.assertValid("wall")));
        assertEquals(2, failure.getFailures().size());
        assertTrue(failure.getMessage().contains("break_cont_entry_fp"));
        assertTrue(failure.getMessage().contains("break_cont_carrier_sp"));
    }
}
