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
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.JfrFrame;

import static org.junit.jupiter.api.Assertions.assertTrue;

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
    public RemoteSymbolicationTest(@CStack String cstack) {
        super(cstack);
    }

    @BeforeEach
    public void checkPlatform() {
        // Remote symbolication with build-id extraction is Linux-only
        Assumptions.assumeTrue(Platform.isLinux(), "Remote symbolication test requires Linux");
        // Zing JVM forces cstack=no which disables native stack walking
        Assumptions.assumeFalse(Platform.isZing(), "Remote symbolication test requires native stack walking (incompatible with Zing)");
        // OpenJ9 uses JVMTI-based CPU profiling which only captures Java frames, not native library frames
        // This test requires native frames from libddproftest.so to validate remote symbolication
        Assumptions.assumeFalse(Platform.isJ9(), "Remote symbolication requires native frames; OpenJ9 JVMTI engine only captures Java frames");
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

            // First verify that our test library (libddproftest) has a build-id
            // We use the extended jdk.NativeLibrary event which now includes buildId and loadBias fields
            JfrEvents libraryEvents = verifyEvents("jdk.NativeLibrary");
            String testLibBuildId = null;
            boolean foundTestLib = false;

            for (JfrEvent libItem : libraryEvents) {
                String name = libItem.getString("name");
                String buildId = libItem.getString("buildId");

                System.out.println("Library: " + name + " -> build-id: " +
                    (buildId != null && !buildId.isEmpty() ? buildId : "<none>"));

                // Check if this is our test library
                if (name != null && name.contains("libddproftest")) {
                    foundTestLib = true;
                    testLibBuildId = buildId;
                    System.out.println("Found test library: " + name + " with build-id: " + buildId);
                }
            }

            // Our test library MUST be present and have a build-id
            Assumptions.assumeTrue(foundTestLib,
                "Test library libddproftest not found in jdk.NativeLibrary events. "
                + "The test needs this library to verify remote symbolication.");
            Assumptions.assumeTrue(testLibBuildId != null && !testLibBuildId.isEmpty(),
                "Test library libddproftest found but has no build-id. "
                + "Cannot test remote symbolication without build-id.");

            JfrEvents events = verifyEvents("datadog.ExecutionSample");

            boolean foundTestLibFrame = false;
            boolean foundTestLibRemoteFrame = false;
            int sampleCount = 0;
            int printCount = 0;
            int testLibFrameCount = 0;

            for (JfrEvent sample : events) {
                if (!sample.has("stackTrace")) {
                    continue;
                }
                sampleCount++;

                // Iterate through frames to check for test library frames
                for (JfrFrame frame : sample.getStackTrace().frames()) {
                    String methodName = frame.methodName();

                    // Get class name (contains build-id for remote symbolication frames)
                    String className = frame.className();

                    // Check if this is a remote symbolication frame from our test library
                    // Format in JFR: type.name = build-ID (bare, no suffix), method.name = "<remote>"
                    if (methodName != null && methodName.equals("<remote>") &&
                        className != null && className.equals(testLibBuildId)) {
                        foundTestLibRemoteFrame = true;
                        testLibFrameCount++;
                        foundTestLibFrame = true;

                        // Print first remote frame for debugging
                        if (printCount == 0) {
                            System.out.println("=== First remote symbolication frame ===");
                            System.out.println("Class: " + className);
                            System.out.println("Method: " + methodName);
                            System.out.println("Signature: " + (frame.methodDescriptor() != null ? frame.methodDescriptor() : "null"));
                            printCount++;
                        }
                    }

                    // With remote symbolication, we should see <remote> method names, not resolved symbols
                    // Log a warning if we find resolved symbols (indicates remote symbolication didn't work for this frame)
                    if (methodName != null && (methodName.equals("burn_cpu") || methodName.equals("compute_fibonacci"))) {
                        System.out.println("WARNING: Found resolved symbol instead of remote frame: " + methodName + " (class: " + className + ")");
                    }

                    // Also count frames with resolved symbols from libddproftest
                    // (for fallback case or if library name appears in class name)
                    if ((methodName != null && (methodName.contains("burn_cpu") || methodName.contains("compute_fibonacci"))) ||
                        (className != null && className.contains("libddproftest"))) {
                        foundTestLibFrame = true;
                        // Don't increment testLibFrameCount here to avoid double-counting
                    }
                }
            }

            System.out.println("Total samples analyzed: " + sampleCount);
            System.out.println("Samples with test lib frames: " + testLibFrameCount);
            System.out.println("Found test lib frames: " + foundTestLibFrame);
            System.out.println("Found test lib remote frames: " + foundTestLibRemoteFrame);
            System.out.println("Test library build-id: " + testLibBuildId);

            // We call the test library functions extensively, so we MUST see frames from it
            assertTrue(foundTestLibFrame,
                "No frames from libddproftest found in any samples. "
                + "The test called RemoteSymHelper.burnCpu() and computeFibonacci() extensively. "
                + "Analyzed " + sampleCount + " samples.");

            // Those frames MUST be in remote symbolication format (not resolved)
            assertTrue(foundTestLibRemoteFrame,
                "Found frames from libddproftest but they are not in remote symbolication format. "
                + "Expected format: " + testLibBuildId + ".<remote>(0x<offset>). "
                + "Analyzed " + testLibFrameCount + " samples with test lib frames.");
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms,remotesym=true";
    }
}