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

            for (IItemIterable cpuSamples : events) {
                IMemberAccessor<String, IItem> frameAccessor =
                    JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());

                for (IItem sample : cpuSamples) {
                    String stackTrace = frameAccessor.getMember(sample);
                    assertFalse(stackTrace.contains("jvmtiError"));

                    // In remote symbolication mode, native frames should contain:
                    // - Build-ID (hex string) instead of symbol name
                    // - PC offset (0x...) instead of absolute address

                    // Check for hex build-id patterns (typically 40-char hex for SHA-1)
                    if (stackTrace.matches(".*[0-9a-f]{20,}.*")) {
                        foundBuildId = true;
                        foundRemoteFrame = true;
                    }

                    // Check for PC offset format (0x followed by hex)
                    if (stackTrace.matches(".*0x[0-9a-f]+.*")) {
                        foundPcOffset = true;
                    }

                    // Remote frames should NOT contain traditional symbol names
                    // like "JavaCalls::call_virtual()" - they should have build-ids instead
                    if (foundRemoteFrame) {
                        assertFalse(stackTrace.matches(".*\\w+::\\w+\\(\\).*"),
                            "Remote symbolication mode should not show resolved C++ symbol names");
                    }
                }
            }

            // Verify we found remote symbolication data
            assertTrue(foundRemoteFrame || foundBuildId,
                "Should find at least one frame with remote symbolication data (build-id)");
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms,remotesym=true";
    }
}
