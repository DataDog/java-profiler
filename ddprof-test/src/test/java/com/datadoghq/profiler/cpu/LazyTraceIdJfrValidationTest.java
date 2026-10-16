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
 * <p>A child JVM runs the profiler in lazy mode and a JFR recording of {@code jdk.ClassDefine} while
 * it spins in a probe class. In debug builds the profiler logs the trace ID it reads for the class
 * of every raw frame it resolves. JFR emits {@code jdk.ClassDefine} when the probe class is created,
 * and the event's {@code definedClass} carries JFR's trace ID for it as {@code RecordedClass.getId()}.
 * The two must be equal. {@code jdk.ClassDefine} is used rather than JFR's execution samples
 * because it is emitted exactly once per class on every JFR-enabled release (8u262 on), while JFR's
 * pre-25 sampler recorded almost no {@code jdk.ExecutionSample} events for the spinning probe.
 *
 * <p>This check runs in CI only. The profiler never calls into JFR at runtime: JFR's
 * {@code JVM.getClassId()} touches JFR state that only exists once its recorder has been created,
 * which the profiler cannot verify safely.
 */
public class LazyTraceIdJfrValidationTest extends AbstractProcessProfilerTest {
    private static final String PROBE_CLASS = "com.datadoghq.profiler.generated.LazyTraceIdProbe";
    private static final Pattern LOGGED_ID = Pattern.compile(
            "\\[TEST::INFO\\] Lazy resolution of " + Pattern.quote(PROBE_CLASS.replace('.', '/')) + ", trace id (\\d+)");

    @Test
    @Timeout(120)
    public void calibratedTraceIdMatchesJfrClassId() throws Exception {
        // The profiler's side of the comparison is a debug-build log line.
        Assumptions.assumeTrue("debug".equals(System.getProperty("ddprof_test.config")), "needs a debug build");
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9() || Platform.isGraal(), "HotSpot only");
        Assumptions.assumeTrue(jfrConsumerAvailable(), "JFR not available");

        Path jfrRecording = Files.createTempFile("lazy-trace-id-jfr-", ".jfr");
        Path ddprofRecording = Files.createTempFile("lazy-trace-id-ddprof-", ".jfr");
        Path jfrSettings = Files.createTempFile("lazy-trace-id-", ".jfc");
        Files.write(jfrSettings, Arrays.asList(
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
                "<configuration version=\"2.0\">",
                "  <event name=\"jdk.ClassDefine\">",
                "    <setting name=\"enabled\">true</setting>",
                "    <setting name=\"stackTrace\">false</setting>",
                "  </event>",
                "</configuration>"));
        try {
            AtomicLong loggedId = new AtomicLong(-1);
            AtomicBoolean traceIdTags = new AtomicBoolean(false);
            LaunchResult result = launch("lazy-trace-id",
                    Arrays.asList("-XX:StartFlightRecording=filename=" + jfrRecording + ",settings=" + jfrSettings + ",dumponexit=true"),
                    "start,cpu=1ms,cstack=vm,fjmethodid=lazy,jfr,file=" + ddprofRecording,
                    line -> {
                        if (line.contains("[TEST::INFO] Raw frame tags: klass trace id")) {
                            traceIdTags.set(true);
                        }
                        Matcher m = LOGGED_ID.matcher(line);
                        if (m.find()) {
                            try {
                                loggedId.set(Long.parseLong(m.group(1)));
                            } catch (NumberFormatException ignored) {
                                // Leaves loggedId unset; the assertion below reports it.
                            }
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
            assertTrue(!jfrIds.isEmpty(), "JFR recorded no jdk.ClassDefine for " + PROBE_CLASS);
            assertEquals(new HashSet<>(Arrays.asList(loggedId.get())), jfrIds,
                    "the calibrated Klass::_trace_id offset does not read JFR's class ID");
        } finally {
            try { Files.deleteIfExists(jfrRecording); } catch (IOException ignored) {}
            try { Files.deleteIfExists(ddprofRecording); } catch (IOException ignored) {}
            try { Files.deleteIfExists(jfrSettings); } catch (IOException ignored) {}
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
     * Returns the IDs JFR's {@code jdk.ClassDefine} events give {@code className}. Uses
     * jdk.jfr.consumer through reflection because the test sources compile with
     * {@code --release 8}, which hides jdk.jfr.
     */
    private static Set<Long> jfrClassIds(Path recording, String className) throws Exception {
        Class<?> recordingFile = Class.forName("jdk.jfr.consumer.RecordingFile");
        List<?> events = (List<?>) recordingFile.getMethod("readAllEvents", Path.class).invoke(null, recording);
        Set<Long> ids = new HashSet<>();
        for (Object event : events) {
            Object type = call(event, "getEventType");
            if (!"jdk.ClassDefine".equals(call(type, "getName"))) {
                continue;
            }
            Object clazz = event.getClass().getMethod("getClass", String.class).invoke(event, "definedClass");
            if (clazz != null && className.equals(call(clazz, "getName"))) {
                ids.add((Long) call(clazz, "getId"));
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
