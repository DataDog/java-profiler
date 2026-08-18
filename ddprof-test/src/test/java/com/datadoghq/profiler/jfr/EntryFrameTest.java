/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.JfrStackTrace;

import org.junitpioneer.jupiter.RetryingTest;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Verifies which bottom-of-stack methods {@code Lookup::fillJavaMethodInfo} (flightRecorder.cpp)
 * recognises as thread entry points: {@code void main(String[])}, {@code java.lang.Thread.run()}
 * and the {@code void run()} override of any {@link Thread} subclass.
 *
 * <p>Entry-point recognition is not exposed to Java directly. It surfaces in the recording as the
 * {@code truncated} flag of {@code jdk.types.StackTrace}: {@code Recording::writeStackTraces}
 * writes {@code truncated = !isEntry(bottomFrame)} whenever that bottom frame is a Java frame
 * (the native-frame case falls back to the unwinder's own truncation flag instead). So a stack
 * that bottoms out in a recognised entry point is reported as complete, and any other Java bottom
 * frame is reported as truncated — the profiler cannot tell a stack that genuinely started there
 * from one whose remaining frames were lost.
 *
 * <p>The workload runs in a forked JVM ({@link #launch}) because {@code main(String[])} can only
 * be the bottom frame of the process' primordial thread; inside the test JVM that frame belongs to
 * the build tool's launcher, several dozen frames below the test method.
 *
 * <p>The {@code cstack} mode is deliberately left at its default. Native frames are collected from
 * the signal context down to the topmost Java frame only, so in every non-mixed mode the bottom
 * frame of a Java thread's sample is still its Java entry point. Forcing a mode would only narrow
 * the test: {@code cstack=vmx} appends the native frames <em>below</em> the Java stack and would
 * route the bottom frame through the native branch instead, {@code cstack=vm} fails startup outside
 * Linux/HotSpot, and {@code cstack=no} leaves {@code StackContext::sp} unset, which makes
 * {@code HotspotSupport::getJavaTraceAsync} reject in-Java threads outright
 * (AGCT_NATIVE_NO_JAVA_CONTEXT) and yields nothing but {@code no_Java_frame} samples.
 */
public class EntryFrameTest extends AbstractProcessProfilerTest {

    private static final String LAUNCHER = "com.datadoghq.profiler.ExternalLauncher";

    /** {@code public static void main(String[] args)} of the forked JVM's main class. */
    private static final String MAIN_ROOT = LAUNCHER + ".main([Ljava/lang/String;)V";
    /** {@code new Thread(runnable)} bottoms out in {@code Thread}'s own {@code run()}. */
    private static final String THREAD_RUN_ROOT = "java.lang.Thread.run()V";
    /** A {@code run()} override two levels below {@link Thread}. */
    private static final String SUBCLASS_RUN_ROOT = LAUNCHER + "$EntryFrameThread.run()V";

    /** Both engines are enabled, and both their event types read back, for sampling headroom. */
    private static final String PROFILER_COMMAND = "start,cpu=10ms,wall=10ms,jfr,file=";

    private static final String[] SAMPLE_EVENT_TYPES = {
            "datadog.ExecutionSample", "datadog.MethodSample"
    };

    /**
     * Every method the workload's padding call chain consists of. With a depth-limited recording
     * these become bottom frames, and none of them is an entry point.
     */
    private static final String[] NON_ENTRY_ROOTS = {
            LAUNCHER + ".entryFrameWorkLevel1(J)V",
            LAUNCHER + ".entryFrameWorkLevel2(J)V",
            LAUNCHER + ".entryFrameBurn(J)V",
    };

    @RetryingTest(3)
    void entryFramesAreNotMarkedTruncated() throws Exception {
        Path recording = newRecordingPath();
        try {
            runWorkload(recording, PROFILER_COMMAND + recording.toAbsolutePath());

            Map<String, long[]> roots = truncationCountsByRootFrame(recording);
            for (String root : new String[] {MAIN_ROOT, THREAD_RUN_ROOT, SUBCLASS_RUN_ROOT}) {
                long[] counts = roots.get(root);
                assertNotNull(counts, root + " was never sampled as a bottom frame; bottom frames"
                        + " seen: " + roots.keySet());
                assertEquals(0L, counts[1], root + " is a thread entry point, but "
                        + counts[1] + " of its " + (counts[0] + counts[1])
                        + " samples were marked truncated");
            }
        } finally {
            Files.deleteIfExists(recording);
        }
    }

    /**
     * The counterpart of the assertions above: with {@code jstackdepth=2} the same workload's
     * samples bottom out inside its padding call chain instead of at a thread entry point, and
     * must then be marked truncated. Without this, a build in which nothing is ever recognised as
     * an entry point — the {@code truncated} flag stuck at {@code false} — would still pass.
     */
    @RetryingTest(3)
    void nonEntryFramesAreMarkedTruncated() throws Exception {
        Path recording = newRecordingPath();
        try {
            runWorkload(recording,
                    PROFILER_COMMAND + recording.toAbsolutePath() + ",jstackdepth=2");

            Map<String, long[]> roots = truncationCountsByRootFrame(recording);
            long notTruncated = 0;
            long truncated = 0;
            for (String root : NON_ENTRY_ROOTS) {
                long[] counts = roots.get(root);
                if (counts != null) {
                    notTruncated += counts[0];
                    truncated += counts[1];
                }
            }
            assertTrue(truncated > 0, "no sample bottomed out inside the workload's call chain;"
                    + " bottom frames seen: " + roots.keySet());
            assertEquals(0L, notTruncated, notTruncated + " samples bottoming out inside the"
                    + " workload's call chain were reported as complete stacks");
        } finally {
            Files.deleteIfExists(recording);
        }
    }

    /**
     * Allocates the recording in the JVM's own temp directory ({@code java.io.tmpdir}) rather than
     * a hard-coded {@code /tmp/recordings}, so the test carries no assumption about a POSIX
     * filesystem layout or about {@code /tmp} being writable. The {@code finally} blocks above
     * delete it either way.
     */
    private Path newRecordingPath() throws Exception {
        return Files.createTempFile("entry-frame-test", ".jfr");
    }

    private void runWorkload(Path recording, String commands) throws Exception {
        LaunchResult result = launch("entry-frames", Collections.emptyList(), commands,
                line -> LineConsumerResult.CONTINUE, line -> LineConsumerResult.CONTINUE);
        assertTrue(result.inTime, "forked JVM did not exit in time");
        assertEquals(0, result.exitCode, "forked JVM exited with a non-zero code");
        assertTrue(Files.size(recording) > 0, "forked JVM wrote an empty recording");
    }

    /**
     * Buckets every sample in {@code recording} by its bottom frame, counting how many of them
     * were reported as complete (index 0) and how many as truncated (index 1).
     *
     * <p>{@code Recording::writeStackTraces} emits the frames of a trace in the order the unwinder
     * produced them - topmost frame first - so the entry point the {@code truncated} flag was
     * derived from is the last frame of the list.
     */
    private static Map<String, long[]> truncationCountsByRootFrame(Path recording) throws Exception {
        Map<String, long[]> counts = new LinkedHashMap<>();
        for (String eventType : SAMPLE_EVENT_TYPES) {
            for (JfrEvent sample : JfrEvents.load(recording, eventType)) {
                JfrStackTrace stackTrace = sample.getStackTrace();
                if (stackTrace.isEmpty()) {
                    continue;
                }
                JfrFrame root = stackTrace.frames().get(stackTrace.frames().size() - 1);
                String key = root.className() + "." + root.methodName() + root.methodDescriptor();
                long[] bucket = counts.get(key);
                if (bucket == null) {
                    bucket = new long[2];
                    counts.put(key, bucket);
                }
                bucket[stackTrace.isTruncated() ? 1 : 0]++;
            }
        }
        return counts;
    }
}
