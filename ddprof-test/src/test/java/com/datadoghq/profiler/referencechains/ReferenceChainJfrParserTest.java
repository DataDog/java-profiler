/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.IMCType;
import org.openjdk.jmc.common.item.IAccessorKey;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.item.IType;
import org.openjdk.jmc.common.item.ItemFilters;
import org.openjdk.jmc.flightrecorder.CouldNotLoadRecordingException;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

/**
 * PROF-15341 design doc, Open Question: does JMC's parser actually resolve the {@code
 * datadog.ReferenceChain} event's {@code chain} field - declared in jfrMetadata.cpp as {@code
 * field("chain", T_CLASS, ..., F_CPOOL | F_ARRAY)}, i.e. an <em>array of scalar
 * constant-pool-index</em> {@code T_CLASS} values - the same way it resolves a plain scalar
 * F_CPOOL field (e.g. {@code objectClass}, already exercised by {@code AbstractProfilerTest})
 * or a plain F_ARRAY-of-composite-struct field (e.g. {@code jdk.StackTrace#frames})? Neither
 * already-exercised shape proves this exact combination.
 *
 * <p>This test loads the standalone .jfr file produced by the companion gtest ({@code
 * ddprof-lib/src/test/cpp/referenceChainJfrRoundtrip_ut.cpp}) directly via {@link
 * JfrLoaderToolkit} - no live profiler attach, no {@code AbstractProfilerTest} lifecycle - and
 * asserts the {@code chain} field resolves to the exact class names that gtest seeded, in the
 * exact leaf-to-root order {@code ReferenceChainTracker::buildChainEvent()} (referenceChains.h)
 * produces.
 *
 * <p><b>Why a generic accessor, not {@code Attribute.attr(...)}:</b> JMC's v1 chunk parser
 * (internal.parser.v1.ValueReaders.ArrayReader#getContentType()) registers {@code
 * UnitLookup.UNKNOWN} as the declared content type for <em>every</em> array field, regardless of
 * what its element reader resolves to - this is generic to all array fields, not specific to the
 * cpool case. A field registered as UNKNOWN cannot be bound via {@code
 * Attribute.attr(id, name, desc, CLASS).getAccessor(type)} (that requires the field's registered
 * content type to match). This test instead looks the field up by identifier via {@code
 * IType#getAccessorKeys()} and calls {@code IType#getAccessor(IAccessorKey)} directly - the same
 * lower-level lookup JMC's own UI uses for fields it has no compile-time-known attribute for.
 * This is not a workaround for a missing capability; it is the correct API for an unregistered
 * custom field, and it still calls through the very code
 * ({@code ArrayReader.read()}/{@code resolve()} delegating per-element to the field's element
 * reader, which for {@code chain} is a {@code PoolReader}) that resolves each array element's
 * constant-pool index to its class - the actual thing this test exists to prove.
 */
public class ReferenceChainJfrParserTest {

  private static final String EVENT_TYPE = "datadog.ReferenceChain";

  /**
   * Same path {@code chainRoundtripJfrPath()} in the companion gtest resolves to: the OS temp
   * dir (TMPDIR, falling back to /tmp), agreed by both sides rather than by a shared build
   * directory - the gtest (ddprof-lib) and this test (ddprof-test) are different Gradle
   * modules/tasks with no other filesystem contract between them.
   */
  private static Path roundtripJfrPath() {
    String tmp = System.getenv("TMPDIR");
    String dir = (tmp != null && !tmp.isEmpty()) ? tmp : "/tmp";
    return Paths.get(dir, "datadog_reference_chain_roundtrip.jfr");
  }

  @Test
  public void chainFieldResolvesToSeededClassNamesInLeafToRootOrder()
      throws IOException, CouldNotLoadRecordingException {
    Path jfrPath = roundtripJfrPath();
    assertTrue(Files.exists(jfrPath),
        "Expected " + jfrPath + " to exist - run "
            + ":ddprof-lib:gtestDebug_referenceChainJfrRoundtrip_ut first "
            + "(referenceChainJfrRoundtrip_ut.cpp produces this file).");

    IItemCollection events;
    try (InputStream in = Files.newInputStream(jfrPath)) {
      events = JfrLoaderToolkit.loadEvents(in);
    }
    IItemCollection chainEvents = events.apply(ItemFilters.type(EVENT_TYPE));
    assertTrue(chainEvents.hasItems(), "Expected at least one " + EVENT_TYPE + " event");

    List<IMCType> resolvedChain = null;
    long targetTag = -1;
    int depth = -1;
    for (IItemIterable iterable : chainEvents) {
      IType<IItem> type = iterable.getType();
      IMemberAccessor<?, IItem> chainAccessor = findAccessor(type, "chain");
      IMemberAccessor<?, IItem> targetTagAccessor = findAccessor(type, "targetTag");
      IMemberAccessor<?, IItem> depthAccessor = findAccessor(type, "depth");
      assertNotNull(chainAccessor, "No accessor for 'chain' field on " + EVENT_TYPE);

      for (IItem item : iterable) {
        Object chainValue = chainAccessor.getMember(item);
        assertNotNull(chainValue, "'chain' field resolved to null");
        assertTrue(chainValue instanceof Object[],
            "'chain' field resolved to " + chainValue.getClass() + ", expected an array");

        Object[] rawChain = (Object[]) chainValue;
        List<IMCType> chain = new ArrayList<>(rawChain.length);
        for (Object element : rawChain) {
          assertNotNull(element,
              "chain[] element resolved to null - the constant-pool reference for this "
                  + "T_CLASS array entry did not resolve to a class");
          assertTrue(element instanceof IMCType,
              "chain[] element resolved to " + element.getClass()
                  + ", expected " + IMCType.class + " (a resolved class, not a raw cpool index)");
          chain.add((IMCType) element);
        }
        resolvedChain = chain;
        if (targetTagAccessor != null) {
          Object v = targetTagAccessor.getMember(item);
          if (v instanceof Number) {
            targetTag = ((Number) v).longValue();
          } else if (v instanceof org.openjdk.jmc.common.unit.IQuantity) {
            targetTag = ((org.openjdk.jmc.common.unit.IQuantity) v).longValue();
          }
        }
        if (depthAccessor != null) {
          Object v = depthAccessor.getMember(item);
          if (v instanceof Number) {
            depth = ((Number) v).intValue();
          } else if (v instanceof org.openjdk.jmc.common.unit.IQuantity) {
            depth = (int) ((org.openjdk.jmc.common.unit.IQuantity) v).longValue();
          }
        }
        break; // referenceChainJfrRoundtrip_ut.cpp writes exactly one event
      }
      if (resolvedChain != null) {
        break;
      }
    }

    assertNotNull(resolvedChain, "Never iterated a " + EVENT_TYPE + " item");
    assertEquals(3, resolvedChain.size(), "Expected leaf/middle/root - 3 entries");
    // Leaf-to-root order, matching ReferenceChainTracker::buildChainEvent()'s
    // FrontierTable::reconstructChain() contract and the gtest's insert() calls
    // (tag=3 leaf -> tag=2 middle -> tag=1 root).
    assertEquals("com.test.ChainLeaf", resolvedChain.get(0).getFullName());
    assertEquals("com.test.ChainMiddle", resolvedChain.get(1).getFullName());
    assertEquals("com.test.ChainRoot", resolvedChain.get(2).getFullName());
    assertEquals(3L, targetTag, "targetTag should be the leaf's frontier tag (3)");
    assertEquals(2, depth, "depth should be the leaf's own depth (2 hops from the root)");
  }

  private static IMemberAccessor<?, IItem> findAccessor(IType<IItem> type, String identifier) {
    Map<IAccessorKey<?>, ?> keys = type.getAccessorKeys();
    for (IAccessorKey<?> key : keys.keySet()) {
      if (identifier.equals(key.getIdentifier())) {
        return type.getAccessor(key);
      }
    }
    return null;
  }
}
