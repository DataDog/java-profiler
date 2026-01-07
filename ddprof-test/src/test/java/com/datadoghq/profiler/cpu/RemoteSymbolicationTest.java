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
import org.openjdk.jmc.common.item.Attribute;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;
import static org.openjdk.jmc.common.unit.UnitLookup.PLAIN_TEXT;

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
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    public void testRemoteSymbolicationEnabled(@CStack String cstack) throws Exception {
        try (ProfiledCode profiledCode = new ProfiledCode(profiler)) {
            for (int i = 0, id = 1; i < 100; i++, id += 3) {
                profiledCode.method1(id);
                // Call native functions from our test library to ensure
                // native frames with build-id appear in the samples
                RemoteSymHelper.burnCpu(10000, 5);
                RemoteSymHelper.computeFibonacci(30);
            }
            stopProfiler();

            verifyCStackSettings();

            // First verify that our test library (libddproftest) has a build-id
            // We use the extended jdk.NativeLibrary event which now includes buildId and loadBias fields
            IItemCollection libraryEvents = verifyEvents("jdk.NativeLibrary");
            String testLibBuildId = null;
            boolean foundTestLib = false;

            // Create attributes for the custom fields we added to jdk.NativeLibrary
            IAttribute<String> buildIdAttr = Attribute.attr("buildId", "buildId", "GNU Build ID", PLAIN_TEXT);
            IAttribute<String> nameAttr = Attribute.attr("name", "name", "Name", PLAIN_TEXT);

            for (IItemIterable libItems : libraryEvents) {
                IMemberAccessor<String, IItem> buildIdAccessor = buildIdAttr.getAccessor(libItems.getType());
                IMemberAccessor<String, IItem> nameAccessor = nameAttr.getAccessor(libItems.getType());

                for (IItem libItem : libItems) {
                    String name = nameAccessor.getMember(libItem);
                    String buildId = buildIdAccessor.getMember(libItem);

                    System.out.println("Library: " + name + " -> build-id: " +
                        (buildId != null && !buildId.isEmpty() ? buildId : "<none>"));

                    // Check if this is our test library
                    if (name != null && name.contains("libddproftest")) {
                        foundTestLib = true;
                        testLibBuildId = buildId;
                        System.out.println("Found test library: " + name + " with build-id: " + buildId);
                    }
                }
            }

            // Our test library MUST be present and have a build-id
            Assumptions.assumeTrue(foundTestLib,
                "Test library libddproftest not found in jdk.NativeLibrary events. "
                + "The test needs this library to verify remote symbolication.");
            Assumptions.assumeTrue(testLibBuildId != null && !testLibBuildId.isEmpty(),
                "Test library libddproftest found but has no build-id. "
                + "Cannot test remote symbolication without build-id.");

            IItemCollection events = verifyEvents("datadog.ExecutionSample");

            boolean foundTestLibFrame = false;
            boolean foundTestLibRemoteFrame = false;
            int sampleCount = 0;
            int printCount = 0;
            int testLibFrameCount = 0;

            for (IItemIterable cpuSamples : events) {
                IMemberAccessor<String, IItem> frameAccessor =
                    JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());

                for (IItem sample : cpuSamples) {
                    String stackTrace = frameAccessor.getMember(sample);
                    assertFalse(stackTrace.contains("jvmtiError"));

                    sampleCount++;

                    // Check if this sample contains frames from our test library
                    boolean hasTestLibInStack = stackTrace.contains("burn_cpu") ||
                                               stackTrace.contains("compute_fibonacci") ||
                                               stackTrace.contains("libddproftest");

                    if (hasTestLibInStack) {
                        testLibFrameCount++;
                        foundTestLibFrame = true;

                        // Print samples containing test lib frames for debugging
                        if (printCount < 5) {
                            System.out.println("=== Sample with test lib frame " + (printCount + 1) + " ===");
                            System.out.println(stackTrace);
                            System.out.println("==================");
                            printCount++;
                        }

                        // In remote symbolication mode, frames from libddproftest MUST be formatted as:
                        // <build-id>.<remote>(0x<offset>)
                        // They should NOT show resolved symbol names like burn_cpu or compute_fibonacci

                        // If we see resolved symbol names from our test library, that's a FAILURE
                        if (stackTrace.contains("burn_cpu") || stackTrace.contains("compute_fibonacci")) {
                            fail("Found resolved symbol names (burn_cpu/compute_fibonacci) from libddproftest in stack trace. "
                                + "Remote symbolication should use <build-id>.<remote>(0x<offset>) format instead. "
                                + "Stack trace:\n" + stackTrace);
                        }

                        // Check if this sample has the expected remote symbolication format with our test lib's build-id
                        if (stackTrace.contains(testLibBuildId + ".<remote>")) {
                            foundTestLibRemoteFrame = true;
                        }
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
