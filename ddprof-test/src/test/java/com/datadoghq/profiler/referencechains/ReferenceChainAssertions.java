/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.NativeBuildConfig;
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
 * Shared {@code datadog.ReferenceChain} JFR-parsing helpers.
 *
 * <p>Two overloads because callers load recordings differently:
 * {@code ReferenceChainTrackingTest} uses {@code AbstractProfilerTest}'s {@code JfrEvents}
 * helpers ({@link #findMatchForClass(JfrEvents, Class)}), while {@link LeakingCacheScenario} loads
 * via JMC's {@code JfrLoaderToolkit} ({@link #findMatchForClass(IItemCollection, Class)}).
 */
public final class ReferenceChainAssertions {
  private ReferenceChainAssertions() {}

  /**
   * Leak-tag pool range, mirrored from referenceChains.h / livenessTracker.h (LEAK_TAG_BASE,
   * LEAK_TAG_POOL_SIZE): a correlated chain's targetTag and its HeapLiveObject's leakTag must fall
   * into [LEAK_TAG_BASE, LEAK_TAG_BASE + LEAK_TAG_POOL_SIZE). Asserted against runtime event
   * values.
   */
  public static final long LEAK_TAG_BASE = 0x40000000L;

  public static final long LEAK_TAG_POOL_SIZE = 256;

  /**
   * True on every native build that compiles javaApi.cpp's {@code #ifdef DEBUG} test seams: debug,
   * coverage, asan and tsan (all add -DDEBUG, ConfigurationPresets.kt). Release builds get no-op seam stubs.
   * Child JVMs see the same answer because the launchers forward {@code -Dddprof_test.config}.
   */
  public static boolean isDebugInstrumentedBuild() {
    return NativeBuildConfig.isDebugInstrumented();
  }

  /**
   * The {@code ddprof_test.config} value ProfilerTestPlugin.kt sets on every test<config> task.
   * Launchers forwarding it to a child JVM must fail loud when it is unset (a test run directly
   * from an IDE, outside the Gradle tasks) instead of concatenating the literal "null", which the
   * child would silently classify as a release build and take the unseeded, flakier path.
   */
  public static String requiredTestConfig() {
    String config = System.getProperty("ddprof_test.config");
    if (config == null) {
      throw new IllegalStateException(
          "ddprof_test.config is not set; run via a test<config> Gradle task so the child "
              + "JVM sees the right build configuration");
    }
    return config;
  }

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
    return findMatch(events, targetClass, false, 0);
  }

  /**
   * Same as {@link #findMatchForClass(IItemCollection, Class)}, but identifies one specific
   * instance: only an item whose {@code targetTag} equals {@code requiredTargetTag} matches (an
   * item without a readable {@code targetTag} never does).
   */
  public static ChainMatch findMatchForClassAndTargetTag(IItemCollection events,
      Class<?> targetClass, long requiredTargetTag) {
    return findMatch(events, targetClass, true, requiredTargetTag);
  }

  private static ChainMatch findMatch(IItemCollection events, Class<?> targetClass,
      boolean requireTag, long requiredTargetTag) {
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
        long targetTag = targetTagAccessor != null ? numberValue(targetTagAccessor.getMember(item)) : -1;
        if (requireTag && targetTag != requiredTargetTag) {
          continue;
        }
        List<IMCType> chain = new ArrayList<>(rawChain.length);
        for (Object element : rawChain) {
          chain.add((IMCType) element);
        }
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
   * {@code targetClass}'s name in the format {@code IMCType.getFullName()} uses for array types:
   * {@code Class.getName()} renders {@code byte[].class} as {@code "[B"} (JVM internal signature
   * notation) but JMC's chunk parser renders the same class as {@code "byte[]"} (Java source
   * notation), so comparing {@link Class#getName()} directly against {@code getFullName()} can
   * never match an array-typed leaf class. Only affects array {@code targetClass} values.
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
   * v1 chunk parser registers {@code UnitLookup.UNKNOWN} as the declared content type for every
   * array field regardless of what its element reader resolves to, so an {@code F_ARRAY} field
   * like {@code chain} cannot be bound via a compile-time-typed {@code Attribute}.
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
