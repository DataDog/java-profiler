/*
 * Copyright 2026 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.datadoghq.profiler.metadata;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Regression test for PROF-15075 (SIGSEGV in {@code Recording::writeElement}).
 *
 * <p>Before the fix, {@code JfrMetadata::reset()} cleared the metadata tree's
 * child vector without deleting the heap-allocated {@code Element} and
 * {@code NoField} objects that {@code JfrMetadata::initialize()} had
 * allocated. On the next profiler restart, {@code initialize()} rebuilt the
 * tree with freshly allocated {@code Element}s; once the allocator reused a
 * freed address, {@code Recording::writeElement()} could dereference stale
 * memory during the following dump and crash with a SIGSEGV.
 *
 * <p>This test drives several full stop/start restart cycles with CPU
 * sampling, allocation sampling, and dynamic context attributes enabled, so
 * that both {@code Element::operator||()} (dynamic attribute fields) and the
 * JDK-version-conditional {@code NoField} path in {@code JfrMetadata::field()}
 * are exercised on every {@code reset()}/{@code initialize()} pair. Each
 * cycle's dump must produce a valid, parseable JFR recording; a pre-fix
 * build crashes before completing all cycles.
 */
public class MetadataRestartCycleTest extends AbstractProfilerTest {

    private static final int RESTART_CYCLES = 5;
    private static volatile Object sink;

    @Test
    public void repeatedRestartCyclesProduceValidRecordings() throws Exception {
        waitForProfilerReady(2000);
        runWorkload();
        stopProfiler();

        Files.createDirectories(Paths.get("/tmp/recordings"));
        for (int cycle = 0; cycle < RESTART_CYCLES; cycle++) {
            Path recording = Files.createTempFile(Paths.get("/tmp/recordings"),
                    "MetadataRestartCycleTest_" + cycle + "_", ".jfr");
            try {
                // Triggers JfrMetadata::reset() (of the previous cycle's tree) followed
                // by JfrMetadata::initialize() for the new session.
                profiler.execute("start," + getProfilerCommand() + ",jfr,file=" + recording.toAbsolutePath());
                waitForProfilerReady(2000);

                runWorkload();

                // Triggers Profiler::dump() -> Recording::switchChunk() ->
                // Recording::writeMetadata() -> Recording::writeElement().
                profiler.stop();

                IItemCollection samples = verifyEvents(recording, "datadog.ExecutionSample", true);
                assertTrue(samples.hasItems(), "cycle " + cycle + " produced no ExecutionSample events");

                IItemCollection allocations = verifyEvents(recording, "datadog.ObjectSample", true);
                assertTrue(allocations.hasItems(), "cycle " + cycle + " produced no ObjectSample events");
            } finally {
                Files.deleteIfExists(recording);
            }
        }
    }

    private static void runWorkload() {
        for (int i = 0; i < 500_000; i++) {
            sink = new Object[4];
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms,alloc=512k,attributes=tag1;tag2;tag3";
    }
}
