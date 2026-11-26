/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.jfr;

import static org.junit.jupiter.api.Assertions.*;

import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.IMCThread;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.flightrecorder.JfrAttributes;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;

/** Actual native failed-copy/retry output, decoded across the complete retained chunk prefix. */
public class RecordingDeliveryJfrTest {
  /** Both decoders must recover the original earlier chunk and the subsequent observation. */
  @Test
  @SuppressWarnings("unchecked")
  public void laterSuccessfulDeliveryIncludesPreviouslyUndeliveredChunks() throws Exception {
    Assumptions.assumeFalse(
        "false".equals(System.getenv("DDPROF_NATIVE_FIXTURES_ENABLED")),
        "Native fixture production explicitly disabled with skip-gtest");
    String configured = System.getenv("DDPROF_REFERENCE_CHAIN_ROUNDTRIP_JFR");
    assertNotNull(configured, "Requires the configuration-scoped native producer");
    Path recording = Paths.get(configured).resolveSibling("datadog_delivery_retry_roundtrip.jfr");
    assertTrue(Files.isRegularFile(recording), "Native fixture did not execute");
    try {
      Set<Long> ids = new HashSet<>();
      int samples = 0;
      for (JfrEvent event : JfrEvents.load(recording, "datadog.MethodSample")) {
        Map<String, Object> thread = (Map<String, Object>) event.get("eventThread");
        assertNotNull(thread, "Retained eventThread must resolve in its original chunk");
        assertTrue(ids.add(((Number) thread.get("osThreadId")).longValue()));
        assertEquals(1L, event.getLong("weight", -1L));
        samples++;
      }
      assertEquals(2, samples);
      assertEquals(new HashSet<>(Arrays.asList(111L, 222L)), ids);

      IItemCollection collection = JfrLoaderToolkit.loadEvents(recording.toFile());
      Set<String> names = new HashSet<>();
      int decoded = 0;
      for (IItemIterable items : collection) {
        if (!"datadog.MethodSample".equals(items.getType().getIdentifier())) continue;
        for (IItem item : items) {
          IMCThread thread =
              JfrAttributes.EVENT_THREAD.getAccessor(items.getType()).getMember(item);
          assertNotNull(thread);
          assertTrue(names.add(thread.getThreadName()));
          assertTrue(
              thread.getThreadId() == null || thread.getThreadId() == 0L,
              "Controlled native stackless fixture has no Java identity");
          decoded++;
        }
      }
      assertEquals(2, decoded, "The pinned decoder must not discard either native chunk");
      assertEquals(new HashSet<>(Arrays.asList("[tid=111]", "[tid=222]")), names);
      // Decoding a delivered file is not a runtime receiving acknowledgement.
    } finally {
      if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) Files.deleteIfExists(recording);
      else System.out.println("Retained delivery fixture: " + recording);
    }
  }
}
