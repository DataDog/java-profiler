/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler;

import com.datadoghq.profiler.chaos.VirtualThreadRemountAntagonist;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import org.junit.jupiter.api.function.Executable;

import static org.junit.jupiter.api.Assertions.assertAll;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Checks continuation ancestry and bounds failed walks in a remount workload recording. */
public final class ContinuationStackChecks {
    private static final String WORKLOAD_CLASS = VirtualThreadRemountAntagonist.class.getName();
    private static final int MIN_SAMPLES = 10;
    private static final int MIN_SUCCESS_PERCENT = 99;
    private final boolean carrierFrames;
    private final Set<Long> carrierIds;
    private final long[] eligible = new long[2];
    private final long[] partialThaws = new long[2];
    private final long[] otherStops = new long[2];
    private final Map<String, Long> failureReasons = new LinkedHashMap<>();
    private long carrierOnlyFailures;
    private long idleNativeGaps;
    private long continuationErrors;
    private long invalidAncestry;
    private long falseComplete;
    private String firstFailure;

    /** Takes carrier OS IDs discovered from workload samples in either sampling engine. */
    public ContinuationStackChecks(boolean carrierFrames, Set<Long> carrierIds) {
        this.carrierFrames = carrierFrames;
        this.carrierIds = new HashSet<>(carrierIds);
    }

    /** Discovers carriers before checking failures that contain no application frames. */
    public static void collectCarriers(Set<Long> ids, JfrEvent event) {
        for (JfrFrame frame : event.getStackTrace().frames()) {
            if (WORKLOAD_CLASS.equals(frame.className()) && ("registerFrames".equals(frame.methodName())
                    || "stackFrames".equals(frame.methodName()))) {
                long id = carrierId(event);
                assertTrue(id > 0, "Workload sample has no carrier OS ID: " + event);
                ids.add(id);
                return;
            }
        }
    }

    private static long carrierId(JfrEvent event) {
        Object thread = event.get("eventThread");
        Object id = thread instanceof Map ? ((Map<?, ?>) thread).get("osThreadId") : null;
        return id instanceof Number ? ((Number) id).longValue() : -1;
    }

    /** Classifies one sample; keeps counts and only the first failing stack. */
    public void accept(JfrEvent event) {
        JfrStackTrace trace = event.getStackTrace();
        boolean register = false, stack = false, outer = false;
        String walkError = null;
        boolean continuationError = false;
        int carriers = 0, carrierIndex = -1, lastApplicationIndex = -1, roots = 0, index = 0;
        for (JfrFrame frame : trace.frames()) {
            String method = frame.methodName();
            if (WORKLOAD_CLASS.equals(frame.className())) {
                register |= "registerFrames".equals(method);
                stack |= "stackFrames".equals(method);
                outer |= "registerWorkload".equals(method) || "stackWorkload".equals(method);
                lastApplicationIndex = index;
            }
            if ("java.util.concurrent.ForkJoinWorkerThread".equals(frame.className()) && "run".equals(method)) {
                carriers++;
                carrierIndex = index;
            }
            if ("JVM Continuation".equals(method)) roots++;
            if (method != null) {
                continuationError |= method.startsWith("break_cont_");
                if (walkError == null && (method.startsWith("break_") || "unknown_nmethod".equals(method)
                        || "no_Java_frame".equals(method) || "[skipped frames]".equals(method))) walkError = method;
            }
            index++;
        }
        boolean workload = register || stack;
        boolean knownCarrier = carrierIds.contains(carrierId(event));
        if (continuationError) continuationErrors++;
        if (trace.isEmpty() && knownCarrier) walkError = "empty stack";
        boolean failedWalk = walkError != null && (workload || knownCarrier || continuationError);
        // Only a complete idle scheduler chain establishes that no continuation walk was attempted.
        // Ambiguous carrier samples and all other error markers keep consuming the failure budget.
        boolean idleNativeGap = knownCarrier && !workload && "[skipped frames]".equals(walkError) && isIdleCarrier(trace);
        if (idleNativeGap) idleNativeGaps++;
        else if (failedWalk) {
            if (workload) otherStops[stack ? 1 : 0]++;
            else if (knownCarrier) carrierOnlyFailures++;
            recordFailure(event, walkError);
        }
        if (!workload) return;
        int layout = stack ? 1 : 0;
        // A skipped native region can coexist with complete Java ancestry. Require
        // truncation only when this workload's continuation boundary or outer caller is missing.
        if (!trace.isTruncated() && (carriers == 0 && roots == 0 || !outer)) {
            falseComplete++;
            recordFailure(event, "missing Java ancestor reported complete");
        }
        if (carriers == 0 && roots == 0) {
            if (!failedWalk) {
                otherStops[layout]++;
                recordFailure(event, "missing continuation boundary");
            }
            return;
        }
        if (register && stack || (carrierFrames
                ? carriers != 1 || roots != 0 || carrierIndex <= lastApplicationIndex
                : carriers != 0 || roots != 1)) {
            invalidAncestry++;
            recordFailure(event, "invalid carrier ancestry");
        } else if (!failedWalk && !outer && trace.isTruncated()) partialThaws[layout]++;
        if (!failedWalk) eligible[layout]++;
    }

    /** Requires an ordered park/idle-worker chain with no application frames or continuation evidence. */
    private static boolean isIdleCarrier(JfrStackTrace trace) {
        int phase = 0;
        for (JfrFrame frame : trace.frames()) {
            String owner = frame.className(), method = frame.methodName();
            if (owner == null || method == null) return false;
            if (owner.isEmpty()) {
                // Check every marker: [skipped frames] can precede a more specific failure.
                if (method.startsWith("break_") || "unknown_nmethod".equals(method)
                        || "no_Java_frame".equals(method) || "JVM Continuation".equals(method)) return false;
                continue;
            }
            if (phase == 0 && "jdk.internal.misc.Unsafe".equals(owner) && "park".equals(method)) phase = 1;
            else if (phase == 1 && "java.util.concurrent.locks.LockSupport".equals(owner)
                    && ("park".equals(method) || "parkUntil".equals(method) || "parkNanos".equals(method))) continue;
            else if (phase == 1 && "java.util.concurrent.ForkJoinPool".equals(owner) && "awaitWork".equals(method)) phase = 2;
            else if (phase == 2 && "java.util.concurrent.ForkJoinPool".equals(owner) && "runWorker".equals(method)) phase = 3;
            else if (phase == 3 && "java.util.concurrent.ForkJoinWorkerThread".equals(owner) && "run".equals(method)) phase = 4;
            else return false;
        }
        return phase == 4;
    }

    private void recordFailure(JfrEvent event, String reason) {
        failureReasons.merge(reason, 1L, Long::sum);
        if (firstFailure != null) return;
        StringBuilder text = new StringBuilder(event.typeName()).append(" thread=")
                .append(event.getThreadName("eventThread")).append(" osId=").append(carrierId(event))
                .append(" truncated=").append(event.getStackTrace().isTruncated()).append(" reason=").append(reason);
        List<JfrFrame> frames = event.getStackTrace().frames();
        for (int i = 0; i < Math.min(16, frames.size()); i++) {
            JfrFrame frame = frames.get(i);
            text.append("\n  ").append(frame.className()).append('.').append(frame.methodName());
        }
        firstFailure = text.toString();
    }

    /** Requires coverage in both layouts and at least 99% successful boundary walks. */
    public void assertValid(String eventType) {
        List<Executable> checks = new ArrayList<>();
        checks.add(() -> assertFalse(carrierIds.isEmpty(), "No workload carriers identified"));
        checks.add(() -> assertEquals(0, continuationErrors, "Continuation recovery errors"));
        checks.add(() -> assertEquals(0, invalidAncestry, "Missing, duplicated or misplaced carrier frames"));
        checks.add(() -> assertEquals(0, falseComplete, "Incomplete walks reported complete"));
        for (int layout = 0; layout < 2; layout++) {
            final int i = layout;
            checks.add(() -> assertTrue(eligible[i] >= MIN_SAMPLES, "Insufficient boundary samples for layout " + i));
            checks.add(() -> assertTrue(partialThaws[i] >= MIN_SAMPLES, "Insufficient partial-thaw samples for layout " + i));
            checks.add(() -> assertTrue(eligible[i] * 100 >= (eligible[i] + otherStops[i]) * MIN_SUCCESS_PERCENT,
                    "Fewer than 99% successful boundary walks for layout " + i));
        }
        long successful = eligible[0] + eligible[1];
        long attempts = successful + otherStops[0] + otherStops[1] + carrierOnlyFailures;
        checks.add(() -> assertTrue(successful * 100 >= attempts * MIN_SUCCESS_PERCENT,
                "Fewer than 99% successful boundary walks including carrier-only failures"));
        assertAll(eventType + " carrier=" + carrierFrames + " " + this, checks);
    }

    /** Reports coverage, failure reasons and the first offending thread and stack. */
    @Override
    public String toString() {
        return "eligible=" + Arrays.toString(eligible) + " partialThaws=" + Arrays.toString(partialThaws)
                + " otherStops=" + Arrays.toString(otherStops) + " carrierOnlyFailures=" + carrierOnlyFailures
                + " idleNativeGaps=" + idleNativeGaps + " continuationErrors=" + continuationErrors + " invalidAncestry=" + invalidAncestry
                + " falseComplete=" + falseComplete + " failureReasons=" + failureReasons
                + (firstFailure == null ? "" : "\nFirst failure: " + firstFailure);
    }
}
