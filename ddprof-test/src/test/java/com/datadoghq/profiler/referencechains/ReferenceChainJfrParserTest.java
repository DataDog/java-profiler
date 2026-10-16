/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import org.junit.jupiter.api.Assumptions;
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
 * Verifies JMC resolves {@code datadog.ReferenceChain}'s {@code chain} field - declared in
 * jfrMetadata.cpp as {@code field("chain", T_CLASS, ..., F_CPOOL | F_ARRAY)}, an array of
 * constant-pool {@code T_CLASS} indices. Neither scalar F_CPOOL fields (e.g. {@code objectClass})
 * nor F_ARRAY-of-struct fields (e.g. {@code jdk.StackTrace#frames}) cover this combination.
 *
 * <p>Loads the .jfr produced by the companion gtest ({@code referenceChainJfrRoundtrip_ut.cpp})
 * directly, with no live profiler, and asserts the seeded class names in leaf-to-root order.
 *
 * <p><b>Why a generic accessor, not {@code Attribute.attr(...)}:</b> JMC's v1 chunk parser
 * ({@code ArrayReader#getContentType()}) registers {@code UnitLookup.UNKNOWN} as the content type
 * of every array field, so it cannot be bound via a typed {@code Attribute}. Looking it up by
 * identifier via {@code IType#getAccessorKeys()} still goes through {@code ArrayReader}'s
 * per-element {@code PoolReader} resolution - the thing this test exists to prove.
 */
public class ReferenceChainJfrParserTest {

  private static final String EVENT_TYPE = "datadog.ReferenceChain";

  /**
   * Must match the companion gtest's {@code chainRoundtripJfrPath()} (TMPDIR, else /tmp): the
   * two run in different Gradle modules with no other shared filesystem contract.
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
    // Assumption, not assertion: the producing gtest does not run on CI runners without Google
    // Test (e.g. the el7 testRelease job), where the file can never exist.
    Assumptions.assumeTrue(Files.exists(jfrPath),
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
      IMemberAccessor<?, IItem> edgesAccessor = findAccessor(type, "edges");
      IMemberAccessor<?, IItem> targetTagAccessor = findAccessor(type, "targetTag");
      IMemberAccessor<?, IItem> depthAccessor = findAccessor(type, "depth");
      assertNotNull(chainAccessor, "No accessor for 'chain' field on " + EVENT_TYPE);
      assertNotNull(edgesAccessor, "No accessor for 'edges' field on " + EVENT_TYPE
          + " - the new retention-edge label array (T_STRING|F_ARRAY) did not make it "
          + "into the recorded metadata");

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
        // Retention-edge labels, one per hop. The gtest has no JNIEnv, so it seeds kind labels
        // instead of decoded ones; this checks the array field parses, not the decode
        // (covered natively by referenceChains_ut).
        Object edgesValue = edgesAccessor.getMember(item);
        assertNotNull(edgesValue, "'edges' field resolved to null");
        assertTrue(edgesValue instanceof Object[],
            "'edges' field resolved to " + edgesValue.getClass()
                + ", expected an array");
        Object[] rawEdges = (Object[]) edgesValue;
        assertEquals(3, rawEdges.length, "edges must align with the chain, one label per hop");
        for (Object e : rawEdges) {
          assertTrue(e instanceof String,
              "edges[] element resolved to " + (e == null ? "null" : e.getClass())
                  + ", expected a String");
        }
        assertEquals("field", rawEdges[0]);
        assertEquals("element", rawEdges[1]);
        assertEquals("jni_global", rawEdges[2]);
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
