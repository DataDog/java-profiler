/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
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
import java.util.Map;

/**
 * Shared {@code datadog.ReferenceChain} JFR-parsing helpers, extracted out of
 * {@code ReferenceChainTrackingTest} so both that in-process JUnit test and
 * {@link LeakingCacheScenario} (run inside a genuinely separate child JVM by
 * {@code ExternalProcessReferenceChainTest}) can reuse the exact same JMC-accessor logic
 * rather than maintaining two copies.
 *
 * <p>{@link #findMatchForClass(JfrEvents, Class)} is a separate, jafar-backed counterpart to
 * {@link #findMatchForClass(IItemCollection, Class)} for {@code ReferenceChainTrackingTest}, which
 * loads recordings via {@code AbstractProfilerTest}'s {@code JfrEvents}-returning helpers
 * (jb/jfr-lightweight-query-api). {@link LeakingCacheScenario} and {@code ReferenceChainJfrParserTest}
 * load recordings directly via JMC's {@code JfrLoaderToolkit} and keep using the
 * {@code IItemCollection} overload unchanged.
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

  /** Result of {@link #findMatchForClass(JfrEvents, Class)}: one resolved chain event's fields. */
  public static final class JfrChainMatch {
    public final List<String> chain;
    public final long targetTag;
    public final int depth;

    JfrChainMatch(List<String> chain, long targetTag, int depth) {
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

      String targetName = jmcStyleName(targetClass);
      for (IItem item : iterable) {
        Object chainValue = chainAccessor.getMember(item);
        if (!(chainValue instanceof Object[])) {
          throw new IllegalStateException(
              "'chain' field resolved to " + chainValue + ", expected an array");
        }
        Object[] rawChain = (Object[]) chainValue;
        if (rawChain.length == 0 || !(rawChain[0] instanceof IMCType)
            || !targetName.equals(((IMCType) rawChain[0]).getFullName())) {
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
   * jafar/{@code JfrEvents}-backed counterpart to {@link #findMatchForClass(IItemCollection, Class)} -
   * see this class's own header comment for why these are two separate overloads rather than one.
   */
  public static JfrChainMatch findMatchForClass(JfrEvents events, Class<?> targetClass) {
    if (events == null || !events.hasItems()) {
      return null;
    }
    String targetName = jmcStyleName(targetClass);
    for (JfrEvent item : events) {
      Object chainValue = item.get("chain");
      if (!(chainValue instanceof Object[])) {
        throw new IllegalStateException(
            "'chain' field resolved to " + chainValue + ", expected an array");
      }
      Object[] rawChain = (Object[]) chainValue;
      if (rawChain.length == 0 || !targetName.equals(classFullName(rawChain[0]))) {
        continue;
      }
      List<String> chain = new ArrayList<>(rawChain.length);
      for (Object element : rawChain) {
        chain.add(classFullName(element));
      }
      long targetTag = item.getLong("targetTag", -1);
      int depth = (int) item.getLong("depth", -1);
      return new JfrChainMatch(chain, targetTag, depth);
    }
    return null;
  }

  /**
   * {@code targetClass}'s name in the same format {@code IMCType.getFullName()} uses for array
   * types - found the hard way: {@code Class.getName()} renders {@code byte[].class} as {@code
   * "[B"} (JVM internal signature notation), but JMC's chunk parser renders the same array class's
   * {@code IMCType.getFullName()} as {@code "byte[]"} (Java source notation), so comparing {@link
   * Class#getName()} directly against {@code getFullName()} - as both {@code findMatchForClass}
   * overloads above used to - can never match an array-typed leaf class, even when the correct
   * event is genuinely present in the recording. Only affects array {@code targetClass} values
   * (e.g. {@code byte[].class}); a non-array class's {@code getName()} already matches {@code
   * getFullName()} as-is.
   */
  private static String jmcStyleName(Class<?> targetClass) {
    int dimensions = 0;
    Class<?> component = targetClass;
    while (component.isArray()) {
      dimensions++;
      component = component.getComponentType();
    }
    if (dimensions == 0) {
      return targetClass.getName();
    }
    StringBuilder name = new StringBuilder(component.getName());
    for (int i = 0; i < dimensions; i++) {
      name.append("[]");
    }
    return name.toString();
  }

  /**
   * The full name (e.g. {@code java.lang.String}) of a resolved {@code chain[]} array element -
   * mirrors {@code JfrEvent.getClassName(String)}'s own class-reference-map unwrapping, applied
   * to an array element rather than a named field.
   */
  @SuppressWarnings("unchecked")
  private static String classFullName(Object element) {
    if (!(element instanceof Map)) {
      throw new IllegalStateException(
          "chain[] element resolved to " + element + ", expected a class reference map");
    }
    Object name = ((Map<String, Object>) element).get("name");
    String s;
    if (name instanceof Map) {
      Object v = ((Map<String, Object>) name).get("string");
      s = v != null ? v.toString() : null;
    } else {
      s = name != null ? name.toString() : null;
    }
    return s != null ? s.replace('/', '.') : null;
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
