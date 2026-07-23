/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.Platform;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Reference-chains VMStructs-walk plan, Phase 3: exercises {@code FieldWalker::walkOneHop()}
 * (referenceChainsWalker.h/.cpp) directly, via {@link JavaProfiler#walkOneHopForTest0(Object)},
 * against real object graphs on a live JVM. This is a real-oop-read seam wrapped in a minimal
 * {@code FollowReferences} call so it runs at the same {@code VM_HeapWalkOperation} safepoint
 * {@code heapReferenceCallback()}'s own raw-oop reads already rely on (see javaApi.cpp's
 * comment on {@code walkOneHopForTest0}); a green result here does not by itself establish
 * {@code walkOneHop()}'s safety under Phase 4's real safepoint-gated invocation, only that the
 * walking logic itself matches reflection on real object layouts.
 */
public class FieldWalkerTestSeamsTest extends AbstractProfilerTest {

  static class WithMixedFields {
    Object refA;
    int primitive;
    Object refB;
    long anotherPrimitive;
  }

  static class NoOopFields {
    int a;
    long b;
    double c;
  }

  static class WithNullField {
    Object maybeNull;
  }

  static class SelfReferential {
    SelfReferential self;
  }

  @Override
  protected String getProfilerCommand() {
    return "referencechains=true:hops=32:budget=500:ttl=60000:framecap=1024";
  }

  @Override
  protected boolean isPlatformSupported() {
    return !(Platform.isJavaVersion(8) || Platform.isJ9() || Platform.isZing());
  }

  private static void assumeDebugBuild() {
    assumeTrue("debug".equals(System.getProperty("ddprof_test.config")));
    // FieldWalker::available() gates on VMStructs primitives (notably the InstanceKlass
    // "OopMapBlock" export) that are not guaranteed present on every vendor JDK
    // distribution - observed entirely absent from gHotSpotVMStructs/gHotSpotVMTypes on at
    // least one real Temurin 21 build. Skip rather than assert a specific walk result when
    // that's the case; this is Phase 1/2's VMStructs plumbing gap, not a FieldWalker defect -
    // FieldWalker's own fail-closed contract (walkOneHop() producing zero children when
    // unavailable) is exactly what's exercised in that case.
    assumeTrue(JavaProfiler.fieldWalkerAvailableForTest0(),
        "FieldWalker::available() is false on this JVM (VMStructs oop-map/array-layout "
            + "primitives did not resolve) - nothing to assert here");
  }

  /**
   * Plain instance with a mix of reference and primitive fields: the discovered slot count must
   * match the number of non-null reference fields reflection reports, regardless of how many
   * primitive fields are interleaved between them.
   */
  @Test
  public void shouldDiscoverNonNullReferenceFieldsOnly() {
    assumeDebugBuild();
    WithMixedFields obj = new WithMixedFields();
    obj.refA = new Object();
    obj.refB = new Object();
    obj.primitive = 42;
    obj.anotherPrimitive = 123456789L;

    int[] slots = JavaProfiler.walkOneHopForTest0(obj);

    assertEquals(2, slots.length);
  }

  /**
   * A klass with no oop-typed fields at all must yield zero children - walkOneHop() has nothing
   * to visit, not an error.
   */
  @Test
  public void shouldYieldNoChildrenForKlassWithoutOopFields() {
    assumeDebugBuild();
    NoOopFields obj = new NoOopFields();

    int[] slots = JavaProfiler.walkOneHopForTest0(obj);

    assertEquals(0, slots.length);
  }

  /**
   * A null reference field must be skipped, not dereferenced/crashed on - walkOneHop()'s visitor
   * only records non-null children (see fieldWalkTestVisitor, javaApi.cpp).
   */
  @Test
  public void shouldSkipNullReferenceField() {
    assumeDebugBuild();
    WithNullField obj = new WithNullField();
    obj.maybeNull = null;

    int[] slots = JavaProfiler.walkOneHopForTest0(obj);

    assertEquals(0, slots.length);
  }

  /**
   * Object array: every non-null element must be discovered, indexed by element index (not byte
   * offset) as its field_slot.
   */
  @Test
  public void shouldDiscoverObjectArrayElements() {
    assumeDebugBuild();
    Object[] array = new Object[] {new Object(), new Object(), new Object()};

    int[] slots = JavaProfiler.walkOneHopForTest0(array);

    assertEquals(3, slots.length);
    Set<Integer> uniqueSlots = new HashSet<>();
    for (int slot : slots) {
      uniqueSlots.add(slot);
    }
    assertEquals(3, uniqueSlots.size());
  }

  /**
   * Object array with a null element interleaved: only the two non-null elements are discovered.
   */
  @Test
  public void shouldSkipNullObjectArrayElement() {
    assumeDebugBuild();
    Object[] array = new Object[] {new Object(), null, new Object()};

    int[] slots = JavaProfiler.walkOneHopForTest0(array);

    assertEquals(2, slots.length);
  }

  /**
   * Primitive array: no oop children at all, regardless of length - must yield zero, not
   * misinterpret raw primitive bytes as oops.
   */
  @Test
  public void shouldYieldNoChildrenForPrimitiveArray() {
    assumeDebugBuild();
    int[] array = new int[] {1, 2, 3, 4, 5};

    int[] slots = JavaProfiler.walkOneHopForTest0(array);

    assertEquals(0, slots.length);
  }

  /**
   * Self-referential cycle: a single hop off `obj` that discovers `obj` itself must return that
   * child exactly once (matching the single occurrence of the field in the oop map) and must not
   * hang - cycle *deduplication* across hops is the frontier table's job, not this component's,
   * so this only confirms walkOneHop() terminates and reports the edge, not that repeats are
   * collapsed.
   */
  @Test
  public void shouldReportSelfReferentialFieldWithoutHanging() {
    assumeDebugBuild();
    SelfReferential obj = new SelfReferential();
    obj.self = obj;

    int[] slots = JavaProfiler.walkOneHopForTest0(obj);

    assertEquals(1, slots.length);
  }

  /**
   * An object with more oop children than fit in a single internal batch (FieldWalker's
   * walkOneHop() caller loops internally via hasMore() until exhausted, see
   * fieldWalkTestHeapCallback in javaApi.cpp) must still discover every child exactly once - this
   * exercises the resume-same-object path, not just the common single-batch case.
   */
  @Test
  public void shouldDiscoverAllElementsOfLargeObjectArray() {
    assumeDebugBuild();
    Object[] array = new Object[200];
    for (int i = 0; i < array.length; i++) {
      array[i] = new Object();
    }

    int[] slots = JavaProfiler.walkOneHopForTest0(array);

    assertEquals(array.length, slots.length);
    Set<Integer> uniqueSlots = new HashSet<>(Arrays.asList(box(slots)));
    assertEquals(array.length, uniqueSlots.size());
    for (int i = 0; i < array.length; i++) {
      assertTrue(uniqueSlots.contains(i));
    }
  }

  /**
   * Sanity-bounds check on the raw VMStructs-derived numbers {@code FieldWalker} depends on
   * (vtable/itable length, oop-map count), via {@link JavaProfiler#layoutSanityForTest0(Object)}.
   * This is deliberately independent of {@code walkOneHopForTest0()}'s output-based tests above:
   * a wrong-but-consistent field resolution (or a units mistake, e.g. reporting words where bytes
   * are expected) can still produce a plausible-looking walk result while the raw number itself
   * is nonsensical - this is exactly the class of bug the array-header-size words-vs-bytes defect
   * was (an 8x-too-large header size that read three unrelated heap words as array elements
   * without ever crashing). Failing loudly here on a future JDK/vendor layout change is the goal,
   * not just failing on this specific class's field count.
   */
  @Test
  public void shouldHaveSaneInstanceKlassLayoutNumbers() {
    assumeDebugBuild();
    WithMixedFields obj = new WithMixedFields();

    int[] v = JavaProfiler.layoutSanityForTest0(obj);

    int vtableLength = v[0];
    int itableLength = v[1];
    int oopMapCount = v[2];
    assertTrue(vtableLength >= 0 && vtableLength < 4096,
        "vtableLength=" + vtableLength + " outside sane range - VMStructs _vtable_len "
            + "resolution is likely wrong for this JDK");
    assertTrue(itableLength >= 0 && itableLength < 4096,
        "itableLength=" + itableLength + " outside sane range - VMStructs _itable_len "
            + "resolution is likely wrong for this JDK");
    assertTrue(oopMapCount >= 0 && oopMapCount < 64,
        "oopMapCount=" + oopMapCount + " outside sane range - VMStructs "
            + "_nonstatic_oop_map_size resolution is likely wrong for this JDK");
  }

  /**
   * Same sanity-bounds idea as {@link #shouldHaveSaneInstanceKlassLayoutNumbers()}, for the
   * array-specific number: an object array's header size must be a handful of bytes (mark word +
   * klass pointer + length, give or take alignment), never anywhere close to the 128 bytes the
   * words-vs-bytes bug once produced.
   */
  @Test
  public void shouldHaveSaneArrayHeaderSize() {
    assumeDebugBuild();
    Object[] array = new Object[] {new Object()};

    int[] v = JavaProfiler.layoutSanityForTest0(array);

    int headerSizeBytes = v[3];
    int isObjectArray = v[4];
    assertEquals(1, isObjectArray);
    assertTrue(headerSizeBytes >= 8 && headerSizeBytes <= 32,
        "arrayHeaderSizeBytes=" + headerSizeBytes + " outside sane range - VMStructs "
            + "layout_helper header-size decoding is likely wrong for this JDK (e.g. a "
            + "words-vs-bytes units mistake)");
  }

  private static Integer[] box(int[] values) {
    Integer[] boxed = new Integer[values.length];
    for (int i = 0; i < values.length; i++) {
      boxed[i] = values[i];
    }
    return boxed;
  }
}
