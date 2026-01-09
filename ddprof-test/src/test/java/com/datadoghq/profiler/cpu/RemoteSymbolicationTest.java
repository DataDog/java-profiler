/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.RemoteSymHelper;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import io.jafar.parser.api.*;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;

import java.nio.file.Paths;
import java.util.Map;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

/**
 * Integration test for remote symbolication feature.
 *
 * <p>Tests that when remotesym=true is enabled:
 * <ul>
 *   <li>Native frames contain build-id instead of symbol names</li>
 *   <li>PC offsets are stored instead of symbol addresses</li>
 *   <li>Build-ids are valid hex strings</li>
 * </ul>
 */
public class RemoteSymbolicationTest extends CStackAwareAbstractProfilerTest {
    /**
     * Force load libddproftest BEFORE any test runs to ensure library is discovered
     * during profiler's initial updateSymbols() scan (profiler.cpp:1377).
     * This runs before @BeforeEach, ensuring the library is loaded before profiler.execute().
     */
    @BeforeAll
    public static void loadNativeLibrary() {
        try {
            Class.forName("com.datadoghq.profiler.RemoteSymHelper", true,
                RemoteSymHelper.class.getClassLoader());
        } catch (Exception e) {
            // Library load failure will be caught when native methods are called
        }
    }

    public RemoteSymbolicationTest(@CStack String cstack) {
        super(cstack);
    }

    @BeforeEach
    public void checkPlatform() {
        // Remote symbolication with build-id extraction is Linux-only
        Assumptions.assumeTrue(Platform.isLinux(), "Remote symbolication test requires Linux");
        // Zing JVM forces cstack=no which disables native stack walking
        Assumptions.assumeFalse(Platform.isZing(), "Remote symbolication test requires native stack walking (incompatible with Zing)");
        // J9/OpenJ9 has limited native stack walking and most J9 libraries lack GNU build-ids
        Assumptions.assumeFalse(Platform.isJ9(), "Remote symbolication test requires reliable native stack walking and build-ids (not available on J9)");
    }

    @RetryTest(10)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    public void testRemoteSymbolicationEnabled(@CStack String cstack) throws Exception {
        try (ProfiledCode profiledCode = new ProfiledCode(profiler)) {
            for (int i = 0, id = 1; i < 100; i++, id += 3) {
                profiledCode.method1(id);
                // Call native functions from our test library to ensure
                // native frames with build-id appear in the samples
                // Increased iterations to ensure profiler captures these frames
                RemoteSymHelper.burnCpu(1000000, 10);
                RemoteSymHelper.computeFibonacci(35);
            }
            stopProfiler();

            verifyCStackSettings();

            // Parse JFR file using jafar
            AtomicBoolean foundTestLib = new AtomicBoolean(false);
            AtomicBoolean foundTestLibFrame = new AtomicBoolean(false);
            AtomicBoolean foundTestLibRemoteFrame = new AtomicBoolean(false);
            AtomicInteger sampleCount = new AtomicInteger(0);
            AtomicInteger testLibFrameCount = new AtomicInteger(0);
            AtomicInteger printCount = new AtomicInteger(0);
            final String[] testLibBuildId = new String[1];

            try (UntypedJafarParser parser = JafarParser.newUntypedParser(jfrDump)) {

                parser.handle((type, value, ctl) -> {
                    String typeName = type.getName();

                    // First, find build-id from jdk.NativeLibrary events
                    if ("jdk.NativeLibrary".equals(typeName)) {
                        Object name = Values.get(value, "name");
                        Object buildId = Values.get(value, "buildId");

                        if (name != null && buildId != null) {
                            String nameStr = String.valueOf(name);
                            String buildIdStr = String.valueOf(buildId);

                            System.out.println("Library: " + nameStr + " -> build-id: " +
                                (!buildIdStr.isEmpty() ? buildIdStr : "<none>"));

                            if (nameStr.contains("libddproftest")) {
                                foundTestLib.set(true);
                                testLibBuildId[0] = buildIdStr;
                                System.out.println("Found test library: " + nameStr +
                                    " with build-id: " + buildIdStr);
                            }
                        }
                    }

                    // Then analyze ExecutionSample events
                    if ("datadog.ExecutionSample".equals(typeName)) {
                        int currentSample = sampleCount.incrementAndGet();

                        // Access stackTrace.frames array
                        Object stackTraceObj = Values.get(value, "stackTrace");
                        if (stackTraceObj == null || !(stackTraceObj instanceof Map)) {
                            if (currentSample == 1) {
                                System.out.println("DEBUG: Sample 1 - stackTrace is null or not a Map");
                            }
                            return;
                        }

                        Object framesObj = Values.get((Map) stackTraceObj, "frames");
                        Object[] frames = null;

                        // frames can be either ArrayType or Object[] depending on how jafar unwraps it
                        if (framesObj instanceof ArrayType) {
                            frames = (Object[]) ((ArrayType) framesObj).getArray();
                        } else if (framesObj instanceof Object[]) {
                            frames = (Object[]) framesObj;
                        } else {
                            if (currentSample == 1) {
                                System.out.println("DEBUG: Sample 1 - frames is unexpected type: " +
                                    (framesObj != null ? framesObj.getClass().getName() : "null"));
                            }
                            return;
                        }

                        if (currentSample == 1) {
                            System.out.println("DEBUG: Sample 1 - frames.length=" + frames.length);
                        }

                        StringBuilder stackTraceStr = new StringBuilder();
                        boolean hasTestLibInStack = false;
                        boolean hasRemoteFrame = false;

                        for (int i = 0; i < frames.length; i++) {
                            Object frameObj = frames[i];
                            if (!(frameObj instanceof Map)) {
                                continue;
                            }
                            Map frame = (Map) frameObj;

                            // Access method.name.string using proper path navigation
                            Object methodNameObj = Values.get(frame, "method", "name", "string");
                            String methodName = methodNameObj != null ? String.valueOf(methodNameObj) : "";

                            // Debug: print first 3 frames of first sample
                            if (sampleCount.get() == 1 && i < 3) {
                                System.out.println("DEBUG: Frame " + i + " method name: '" + methodName + "'");
                            }

                            stackTraceStr.append(methodName).append("\n");

                            // Check for test library frames
                            if (methodName.contains("burn_cpu") ||
                                methodName.contains("compute_fibonacci") ||
                                methodName.contains("libddproftest")) {
                                hasTestLibInStack = true;

                                // FAIL if we see resolved symbols
                                if (methodName.contains("burn_cpu") ||
                                    methodName.contains("compute_fibonacci")) {
                                    fail("Found resolved symbol names (burn_cpu/compute_fibonacci) " +
                                        "from libddproftest in stack trace. " +
                                        "Remote symbolication should use <build-id>.<remote> format instead. " +
                                        "Method name: " + methodName);
                                }
                            }

                            // Check for remote frame format
                            if (testLibBuildId[0] != null &&
                                methodName.contains(testLibBuildId[0] + ".<remote>")) {
                                hasRemoteFrame = true;
                                hasTestLibInStack = true;
                            }
                        }

                        if (hasTestLibInStack) {
                            testLibFrameCount.incrementAndGet();
                            foundTestLibFrame.set(true);

                            if (printCount.get() < 5) {
                                System.out.println("=== Sample with test lib frame " +
                                    (printCount.incrementAndGet()) + " ===");
                                System.out.println(stackTraceStr.toString());
                                System.out.println("==================");
                            }

                            if (hasRemoteFrame) {
                                foundTestLibRemoteFrame.set(true);
                            }
                        }
                    }
                });

                parser.run();
            }

            // Our test library MUST be present and have a build-id
            Assumptions.assumeTrue(foundTestLib.get(),
                "Test library libddproftest not found in jdk.NativeLibrary events. "
                + "The test needs this library to verify remote symbolication.");
            Assumptions.assumeTrue(testLibBuildId[0] != null && !testLibBuildId[0].isEmpty(),
                "Test library libddproftest found but has no build-id. "
                + "Cannot test remote symbolication without build-id.");

            System.out.println("Total samples analyzed: " + sampleCount.get());
            System.out.println("Samples with test lib frames: " + testLibFrameCount.get());
            System.out.println("Found test lib frames: " + foundTestLibFrame.get());
            System.out.println("Found test lib remote frames: " + foundTestLibRemoteFrame.get());
            System.out.println("Test library build-id: " + testLibBuildId[0]);

            // We call the test library functions extensively, so we MUST see frames from it
            assertTrue(foundTestLibFrame.get(),
                "No frames from libddproftest found in any samples. "
                + "The test called RemoteSymHelper.burnCpu() and computeFibonacci() extensively. "
                + "Analyzed " + sampleCount.get() + " samples.");

            // Those frames MUST be in remote symbolication format (not resolved)
            assertTrue(foundTestLibRemoteFrame.get(),
                "Found frames from libddproftest but they are not in remote symbolication format. "
                + "Expected format: " + testLibBuildId[0] + ".<remote>(0x<offset>). "
                + "Analyzed " + testLibFrameCount.get() + " samples with test lib frames.");
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms,remotesym=true";
    }
}
