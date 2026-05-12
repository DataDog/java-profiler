/*
 * Copyright 2025 Datadog, Inc
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
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.*;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.PLAIN_TEXT;

/**
 * Verifies that the DoubleBufferedDictionary rotate+clearStandby cycle correctly:
 * - Exposes only pre-dump entries in the dump snapshot.
 * - Resets the live counter to zero after clearStandby().
 * - Accumulates post-dump entries in the new active buffer.
 */
public class DictionaryRotationTest extends AbstractProfilerTest {

    private static final IAttribute<String> ENDPOINT_ATTR =
            attr("endpoint", "endpoint", "endpoint", PLAIN_TEXT);

    @Test
    public void dumpCycleSeparatesPreAndPostDumpEntries() throws Exception {
        String[] preDump  = { "ep_pre_0", "ep_pre_1", "ep_pre_2" };
        String[] postDump = { "ep_post_0", "ep_post_1" };
        int sizeLimit = 100;

        for (int i = 0; i < preDump.length; i++) {
            profiler.recordTraceRoot(i, preDump[i], null, sizeLimit);
        }

        // dump() triggers: rotate() → lockAll() → jfr.dump(snapshot) → unlockAll()
        //                            → clearStandby() (resets counter to 0, frees pre-dump buffer)
        Path snapshot = Files.createTempFile(Paths.get("/tmp/recordings"), "DictionaryRotation_snapshot_", ".jfr");
        try {
            dump(snapshot);

            // Counter is reset to 0 by clearStandby() — no endpoint writes since dump
            Map<String, Long> afterDump = profiler.getDebugCounters();
            assertEquals(0L, afterDump.getOrDefault("dictionary_endpoints_keys", -1L),
                    "dictionary_endpoints_keys must be 0 after clearStandby");

            for (int i = 0; i < postDump.length; i++) {
                profiler.recordTraceRoot(preDump.length + i, postDump[i], null, sizeLimit);
            }

            stopProfiler();

            // Live counter reflects only post-dump insertions
            Map<String, Long> live = profiler.getDebugCounters();
            assertEquals((long) postDump.length, live.get("dictionary_endpoints_keys"),
                    "Live counter must equal number of post-dump endpoints");

            // Snapshot contains pre-dump endpoints only
            Set<String> inSnapshot = endpointNames(verifyEvents(snapshot, "datadog.Endpoint", true));
            for (String ep : preDump) {
                assertTrue(inSnapshot.contains(ep), "Snapshot must contain pre-dump endpoint: " + ep);
            }
            for (String ep : postDump) {
                assertFalse(inSnapshot.contains(ep), "Snapshot must NOT contain post-dump endpoint: " + ep);
            }

            // Main recording contains post-dump endpoints only
            Set<String> inRecording = endpointNames(verifyEvents("datadog.Endpoint"));
            for (String ep : postDump) {
                assertTrue(inRecording.contains(ep), "Recording must contain post-dump endpoint: " + ep);
            }
            for (String ep : preDump) {
                assertFalse(inRecording.contains(ep), "Recording must NOT contain pre-dump endpoint: " + ep);
            }
        } finally {
            Files.deleteIfExists(snapshot);
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms";
    }

    private static Set<String> endpointNames(IItemCollection events) {
        Set<String> names = new HashSet<>();
        for (IItemIterable it : events) {
            IMemberAccessor<String, IItem> accessor = ENDPOINT_ATTR.getAccessor(it.getType());
            if (accessor == null) continue;
            for (IItem item : it) {
                String v = accessor.getMember(item);
                if (v != null) names.add(v);
            }
        }
        return names;
    }
}
