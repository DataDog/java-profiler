/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import static org.junit.jupiter.api.Assertions.assertFalse;
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
    }

    @RetryTest(10)
    @TestTemplate
    @ValueSource(strings = {"vmx", "fp", "dwarf"})
    public void testRemoteSymbolicationEnabled(@CStack String cstack) throws Exception {
        try (ProfiledCode profiledCode = new ProfiledCode(profiler)) {
            for (int i = 0, id = 1; i < 100; i++, id += 3) {
                profiledCode.method1(id);
            }
            stopProfiler();

            verifyCStackSettings();

            IItemCollection events = verifyEvents("datadog.ExecutionSample");

            boolean foundRemoteFrame = false;
            boolean foundBuildId = false;
            boolean foundPcOffset = false;
            int sampleCount = 0;
            int printCount = 0;

            for (IItemIterable cpuSamples : events) {
                IMemberAccessor<String, IItem> frameAccessor =
                    JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());

                for (IItem sample : cpuSamples) {
                    String stackTrace = frameAccessor.getMember(sample);
                    assertFalse(stackTrace.contains("jvmtiError"));

                    sampleCount++;
                    // Print first 3 stack traces for debugging
                    if (printCount < 3) {
                        System.out.println("=== Stack trace " + (printCount + 1) + " ===");
                        System.out.println(stackTrace);
                        System.out.println("==================");
                        printCount++;
                    }

                    // In remote symbolication mode, native frames are formatted as:
                    // <build-id>.<remote>(0x<offset>)
                    // where build-id is the hex string stored in the class field
                    // and 0x<offset> is the PC offset stored in the signature field

                    // Check for the <remote> method marker
                    if (stackTrace.contains("<remote>")) {
                        foundRemoteFrame = true;

                        // If we found a remote frame, verify it has the expected format
                        // Should contain 0x prefix for PC offset in the signature/parameter position
                        if (stackTrace.contains("(0x")) {
                            foundPcOffset = true;
                        }

                        // The build-id should be in the class name position (before the dot)
                        // Look for hex pattern before .<remote>
                        if (stackTrace.matches(".*[0-9a-f]{8,}\\.<remote>.*")) {
                            foundBuildId = true;
                        }
                    }

                    // Remote frames should NOT contain traditional resolved symbol names
                    // If we found remote frames, verify no C++ symbols are present
                    if (foundRemoteFrame) {
                        assertFalse(stackTrace.matches(".*\\w+::\\w+\\(\\).*"),
                            "Remote symbolication mode should not show resolved C++ symbol names");
                    }
                }
            }

            System.out.println("Total samples analyzed: " + sampleCount);
            System.out.println("Found remote frames: " + foundRemoteFrame);
            System.out.println("Found build-ids: " + foundBuildId);
            System.out.println("Found PC offsets: " + foundPcOffset);

            // Verify we found remote symbolication data
            assertTrue(foundRemoteFrame,
                "Should find at least one frame with <remote> marker indicating remote symbolication. Analyzed " + sampleCount + " samples.");
            assertTrue(foundBuildId,
                "Should find at least one frame with build-id in class position");
            assertTrue(foundPcOffset,
                "Should find at least one frame with PC offset in signature position");
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms,remotesym=true";
    }
}
