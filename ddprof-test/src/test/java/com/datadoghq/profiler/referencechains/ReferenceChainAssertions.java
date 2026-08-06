/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import org.openjdk.jmc.common.IMCType;
import org.openjdk.jmc.common.item.IAccessorKey;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.item.IType;
import org.openjdk.jmc.common.unit.IQuantity;

import java.util.ArrayList;
import java.util.List;

/**
 * Shared {@code datadog.ReferenceChain} JFR-parsing helpers, extracted out of
 * {@code ReferenceChainTrackingTest} so both that in-process JUnit test and
 * {@link LeakingCacheScenario} (run inside a genuinely separate child JVM by
 * {@code ExternalProcessReferenceChainTest}) can reuse the exact same JMC-accessor logic
 * rather than maintaining two copies.
 */
public final class ReferenceChainAssertions {
  private ReferenceChainAssertions() {}

  /** Result of {@link #findMatchForClass(IItemCollection, Class)}: one resolved chain event's fields. */
  public static final class ChainMatch {
    public final List<IMCType> chain;
    public final long targetTag;
    public final int depth;

    ChainMatch(List<IMCType> chain, long targetTag, int depth) {
      this.chain = chain;
      this.targetTag = targetTag;
      this.depth = depth;
    }
  }

  /**
   * Scans {@code events} for a {@code datadog.ReferenceChain} item whose {@code chain[0]} is
   * {@code targetClass} specifically, ignoring any events for other klasses this same
   * leak-candidate mechanism may have legitimately flagged (e.g. "[B"/byte[] - see each caller's
   * own comment). Returns {@code null} if {@code events} is empty or none match.
   */
  public static ChainMatch findMatchForClass(IItemCollection events, Class<?> targetClass) {
    if (events == null || !events.hasItems()) {
      return null;
    }
    for (IItemIterable iterable : events) {
      IType<IItem> type = iterable.getType();
      IMemberAccessor<?, IItem> chainAccessor = findAccessor(type, "chain");
      IMemberAccessor<?, IItem> targetTagAccessor = findAccessor(type, "targetTag");
      IMemberAccessor<?, IItem> depthAccessor = findAccessor(type, "depth");
      if (chainAccessor == null) {
        throw new IllegalStateException("No accessor for 'chain' field on datadog.ReferenceChain");
      }

      for (IItem item : iterable) {
        Object chainValue = chainAccessor.getMember(item);
        if (!(chainValue instanceof Object[])) {
          throw new IllegalStateException(
              "'chain' field resolved to " + chainValue + ", expected an array");
        }
        Object[] rawChain = (Object[]) chainValue;
        if (rawChain.length == 0 || !(rawChain[0] instanceof IMCType)
            || !targetClass.getName().equals(((IMCType) rawChain[0]).getFullName())) {
          continue;
        }
        List<IMCType> chain = new ArrayList<>(rawChain.length);
        for (Object element : rawChain) {
          chain.add((IMCType) element);
        }
        long targetTag = targetTagAccessor != null ? numberValue(targetTagAccessor.getMember(item)) : -1;
        int depth = depthAccessor != null ? (int) numberValue(depthAccessor.getMember(item)) : -1;
        return new ChainMatch(chain, targetTag, depth);
      }
    }
    return null;
  }

  /**
   * Looks up a field's accessor by identifier rather than via {@code Attribute.attr(...)}: JMC's
   * v1 chunk parser (internal.parser.v1.ValueReaders.ArrayReader#getContentType()) registers
   * {@code UnitLookup.UNKNOWN} as the declared content type for every array field regardless of
   * what its element reader resolves to, so an {@code F_ARRAY} field like {@code chain}
   * (T_CLASS, F_CPOOL|F_ARRAY, jfrMetadata.cpp) cannot be bound via a compile-time-typed
   * {@code Attribute}. Mirrors {@code ReferenceChainJfrParserTest}'s identical lookup, which
   * already proves this resolves {@code chain}'s array elements to real {@link IMCType}s.
   */
  public static IMemberAccessor<?, IItem> findAccessor(IType<IItem> type, String identifier) {
    for (IAccessorKey<?> key : type.getAccessorKeys().keySet()) {
      if (identifier.equals(key.getIdentifier())) {
        return type.getAccessor(key);
      }
    }
    return null;
  }

  public static long numberValue(Object value) {
    if (value instanceof Number) {
      return ((Number) value).longValue();
    }
    if (value instanceof IQuantity) {
      return ((IQuantity) value).longValue();
    }
    return -1;
  }
}
