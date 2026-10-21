/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assumptions;
import org.openjdk.jmc.common.IMCType;
import org.openjdk.jmc.common.item.IAccessorKey;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.item.IType;
import org.openjdk.jmc.common.item.ItemFilters;
import org.openjdk.jmc.common.unit.IQuantity;
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
 * PROF-15341 design doc, Open Question: does JMC's parser resolve the {@code datadog.ReferenceChain}
 * event's {@code chain} field - declared in jfrMetadata.cpp as {@code field("chain", T_CLASS,
 * ..., F_CPOOL | F_ARRAY)}, an <em>array of scalar constant-pool-index</em> {@code T_CLASS}
 * values - the same way it resolves a plain scalar F_CPOOL field ({@code objectClass}) or a
 * plain F_ARRAY-of-composite-struct field ({@code jdk.StackTrace#frames})? Neither shape proves
 * this combination.
 *
 * <p>Loads the standalone .jfr file produced by the companion gtest
 * ({@code referenceChainJfrRoundtrip_ut.cpp}) directly via {@link JfrLoaderToolkit} - no live
 * profiler attach - and asserts the {@code chain} field resolves to the exact class names the
 * gtest seeded, in the leaf-to-root order {@code buildChainEvent()} produces.
 *
 * <p><b>Why a generic accessor, not {@code Attribute.attr(...)}:</b> JMC's v1 chunk parser
 * registers {@code UnitLookup.UNKNOWN} as the declared content type for <em>every</em> array
 * field, regardless of what its element reader resolves to, and a field registered as UNKNOWN
 * cannot be bound via a compile-time-typed {@code Attribute}. This test looks the field up by
 * identifier via {@code IType#getAccessorKeys()} and calls {@code IType#getAccessor(IAccessorKey)}
 * directly - the same lookup JMC's own UI uses for fields it has no compile-time-known attribute
 * for. It still calls through the code ({@code ArrayReader.read()}/{@code resolve()} delegating
 * per-element to the field's {@code PoolReader}) that resolves each element's constant-pool index
 * to its class - the actual thing this test exists to prove.
 */
public class ReferenceChainJfrParserTest {

  private static final String EVENT_TYPE = "datadog.ReferenceChain";

  /**
   * The path the companion gtest resolves to: {@code DDPROF_REFERENCE_CHAIN_ROUNDTRIP_JFR} when
   * set (ddprof-lib's build sets it to a build-dir path for both the gtest and this test task),
   * otherwise the OS temp dir (TMPDIR, falling back to /tmp) for standalone runs. The file is
   * consume-once: this test deletes it after loading and the gtest unlinks it before regenerating,
   * so a stale fixture from an earlier build can never satisfy the existence assumption below.
   */
  private static Path roundtripJfrPath() {
    String configured = System.getenv("DDPROF_REFERENCE_CHAIN_ROUNDTRIP_JFR");
    if (configured != null && !configured.isEmpty()) {
      return Paths.get(configured);
    }
    String tmp = System.getenv("TMPDIR");
    String dir = (tmp != null && !tmp.isEmpty()) ? tmp : "/tmp";
    return Paths.get(dir, "datadog_reference_chain_roundtrip.jfr");
  }

  @Test
  public void chainFieldResolvesToSeededClassNamesInLeafToRootOrder()
      throws IOException, CouldNotLoadRecordingException {
    Path jfrPath = roundtripJfrPath();
    // Assumption, not assertion: the producing gtest does not run on CI runners without Google
    // Test (e.g. the el7 testRelease job) or with -Pskip-gtest. The build deletes the file before
    // the gtest runs, and when the gtest is skipped, so an existing file is always this build's.
    Assumptions.assumeTrue(Files.exists(jfrPath),
        "Expected " + jfrPath + " to exist - run "
            + ":ddprof-lib:gtestDebug_referenceChainJfrRoundtrip_ut first "
            + "(referenceChainJfrRoundtrip_ut.cpp produces this file).");

    IItemCollection events;
    try (InputStream in = Files.newInputStream(jfrPath)) {
      events = JfrLoaderToolkit.loadEvents(in);
    } finally {
      // Consume-once (see roundtripJfrPath()): loadEvents() fully materializes the recording, so
      // the shared fixture can go now - even on a parse failure - and a later run only ever sees
      // a file freshly written by the gtest.
      Files.deleteIfExists(jfrPath);
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
        // Retention-edge labels: one per chain hop, aligned with it. The gtest seeds kind labels
        // because its JNIEnv is null - the label DECODE is skipped; the Java side validates the
        // ARRAY FIELD parses, not the decode itself (referenceChains_ut covers that natively).
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
          } else if (v instanceof IQuantity) {
            targetTag = ((IQuantity) v).longValue();
          }
        }
        if (depthAccessor != null) {
          Object v = depthAccessor.getMember(item);
          if (v instanceof Number) {
            depth = ((Number) v).intValue();
          } else if (v instanceof IQuantity) {
            depth = (int) ((IQuantity) v).longValue();
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
