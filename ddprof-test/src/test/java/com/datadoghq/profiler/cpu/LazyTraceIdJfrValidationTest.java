/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.io.IOException;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Validates, against JFR itself, the {@code Klass::_trace_id} offset that {@code fjmethodid=lazy}
 * finds by calibration.
 *
 * <p>A child JVM runs both the profiler (lazy mode) and JFR's own CPU sampler while spinning in a
 * probe class. In debug builds the profiler logs the trace ID it reads for each class it allocates
 * jmethodIDs for; JFR records the same class in its {@code jdk.ExecutionSample} stack frames, and
 * {@code RecordedClass.getId()} is JFR's trace ID for it. The two must be equal.
 *
 * <p>This check runs in CI only. The profiler never calls into JFR at runtime: JFR's
 * {@code JVM.getClassId()} touches JFR state that only exists once its recorder has been created,
 * which the profiler cannot verify safely.
 */
public class LazyTraceIdJfrValidationTest extends AbstractProcessProfilerTest {
    private static final String PROBE_CLASS = "com.datadoghq.profiler.generated.LazyTraceIdProbe";
    private static final Pattern LOGGED_ID = Pattern.compile(
            "\\[TEST::INFO\\] Lazy jmethodIDs for L" + Pattern.quote(PROBE_CLASS.replace('.', '/')) + ";, trace id (\\d+)");

    @Test
    @Timeout(120)
    public void calibratedTraceIdMatchesJfrClassId() throws Exception {
        // The profiler's side of the comparison is a debug-build log line.
        Assumptions.assumeTrue("debug".equals(System.getProperty("ddprof_test.config")), "needs a debug build");
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9() || Platform.isGraal(), "HotSpot only");
        Assumptions.assumeTrue(jfrConsumerAvailable(), "JFR not available");

        Path jfrRecording = Files.createTempFile("lazy-trace-id-jfr-", ".jfr");
        Path ddprofRecording = Files.createTempFile("lazy-trace-id-ddprof-", ".jfr");
        try {
            AtomicLong loggedId = new AtomicLong(-1);
            AtomicBoolean traceIdTags = new AtomicBoolean(false);
            LaunchResult result = launch("lazy-trace-id",
                    Arrays.asList("-XX:StartFlightRecording=filename=" + jfrRecording + ",settings=profile,dumponexit=true"),
                    "start,cpu=1ms,cstack=vm,fjmethodid=lazy,jfr,file=" + ddprofRecording,
                    line -> {
                        if (line.contains("[TEST::INFO] Raw frame tags: klass trace id")) {
                            traceIdTags.set(true);
                        }
                        Matcher m = LOGGED_ID.matcher(line);
                        if (m.find()) {
                            loggedId.set(Long.parseLong(m.group(1)));
                        }
                        return LineConsumerResult.CONTINUE;
                    }, null);
            assertTrue(result.inTime, "child JVM did not finish in time");
            assertEquals(0, result.exitCode, "child JVM failed");
            // Builds without JFR (e.g. 8u before 8u262) have no trace ID; lazy mode uses the epoch.
            Assumptions.assumeTrue(traceIdTags.get(), "calibration found no trace ID");
            assertTrue(loggedId.get() > 0, "the profiler did not log the probe class's trace ID");

            Set<Long> jfrIds = jfrClassIds(jfrRecording, PROBE_CLASS);
            System.out.println("profiler trace id=" + loggedId.get() + ", JFR class ids=" + jfrIds);
            assertTrue(!jfrIds.isEmpty(), "JFR recorded no execution sample in " + PROBE_CLASS);
            assertEquals(new HashSet<>(Arrays.asList(loggedId.get())), jfrIds,
                    "the calibrated Klass::_trace_id offset does not read JFR's class ID");
        } finally {
            try { Files.deleteIfExists(jfrRecording); } catch (IOException ignored) {}
            try { Files.deleteIfExists(ddprofRecording); } catch (IOException ignored) {}
        }
    }

    private static boolean jfrConsumerAvailable() {
        try {
            Class.forName("jdk.jfr.consumer.RecordingFile");
            return true;
        } catch (ClassNotFoundException e) {
            return false;
        }
    }

    /**
     * Returns the IDs JFR gave {@code className} in the method types of its
     * {@code jdk.ExecutionSample} stack frames. Uses jdk.jfr.consumer through reflection because
     * the test sources compile with {@code --release 8}, which hides jdk.jfr.
     */
    private static Set<Long> jfrClassIds(Path recording, String className) throws Exception {
        Class<?> recordingFile = Class.forName("jdk.jfr.consumer.RecordingFile");
        List<?> events = (List<?>) recordingFile.getMethod("readAllEvents", Path.class).invoke(null, recording);
        Set<Long> ids = new HashSet<>();
        for (Object event : events) {
            Object type = call(event, "getEventType");
            if (!"jdk.ExecutionSample".equals(call(type, "getName"))) {
                continue;
            }
            Object stackTrace = call(event, "getStackTrace");
            if (stackTrace == null) {
                continue;
            }
            for (Object frame : (List<?>) call(stackTrace, "getFrames")) {
                Object method = call(frame, "getMethod");
                Object clazz = method != null ? call(method, "getType") : null;
                if (clazz != null && className.equals(call(clazz, "getName"))) {
                    ids.add((Long) call(clazz, "getId"));
                }
            }
        }
        return ids;
    }

    private static Object call(Object target, String name) throws Exception {
        Method m = target.getClass().getMethod(name);
        m.setAccessible(true);
        return m.invoke(target);
    }
}
