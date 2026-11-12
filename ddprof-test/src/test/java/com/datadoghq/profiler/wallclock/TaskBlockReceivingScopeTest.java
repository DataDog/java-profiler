/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.*;

import com.datadoghq.profiler.AbstractProfilerTest;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.IMCThread;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.common.unit.IRange;
import org.openjdk.jmc.common.unit.UnitLookup;
import org.openjdk.jmc.flightrecorder.JfrAttributes;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;

/**
 * Controlled decoder fixtures for collection-wide clocks and identity, using actual profiler
 * metadata. These stackless fixtures do not certify production receiving or original JVM
 * observations.
 */
public class TaskBlockReceivingScopeTest extends AbstractProfilerTest {
  // Keep the controlled epoch exactly representable by JMC's quantity scales;
  // these cases isolate collection/clock identity, not large-epoch rounding.
  private static final long EPOCH_NS = 1_000_000_000_000L;
  private static final long QUANTUM_NS = 10_000_000L;

  /** An earlier dump's observation is subtracted after its own chunk clock conversion. */
  @Test
  public void subtractionIncludesEarlierDumpWithItsOwnClock() throws Exception {
    byte[] metadata = metadata();
    byte[] earlierDump =
        chunk(
            metadata,
            EPOCH_NS,
            1_000,
            1_000_000,
            new ThreadRow[] {new ThreadRow(7, 81, 42, "original-worker")},
            event(102, 21_000, 7, 0, 0, 0, 1, 0, 0, 0));
    byte[] receivingDump =
        chunk(
            metadata,
            EPOCH_NS + 5_000_000,
            500_000,
            2_000_000,
            new ThreadRow[] {new ThreadRow(7, 81, 42, "original-worker")},
            event(131, 520_000, 256_000, 7, 1, 0, 0, 0, 0, 0));

    IItemCollection collection = load(earlierDump, receivingDump);
    assertEquals(EPOCH_NS + 20_000_000L, onlySampleTime(collection));
    assertEquals(118_000_000L, syntheticWallTime(collection));
    // This is a rejecting control: closing the scope at the receiving dump overcredits one unit.
    assertEquals(128_000_000L, syntheticWallTime(load(receivingDump)));
    assertEquals(128_000_000L, syntheticWallTime(collection) + QUANTUM_NS);
  }

  /** Equal chunk-local pool keys may bind different original threads in one collection. */
  @Test
  public void equalPoolKeysInDifferentRecordingChunksDoNotIdentifyTheSameThread() throws Exception {
    byte[] metadata = metadata();
    byte[] original =
        chunk(
            metadata,
            EPOCH_NS,
            1_000,
            1_000_000,
            new ThreadRow[] {new ThreadRow(7, 81, 42, "original-worker")},
            event(102, 21_000, 7, 0, 0, 0, 1, 0, 0, 0));
    byte[] nextRecording =
        chunk(
            metadata,
            EPOCH_NS + 5_000_000,
            500_000,
            2_000_000,
            new ThreadRow[] {new ThreadRow(7, 82, 43, "different-worker")},
            event(131, 520_000, 256_000, 7, 1, 0, 0, 0, 0, 0));
    IItemCollection collection = load(original, nextRecording);
    assertEquals(128_000_000L, syntheticWallTime(collection));
    assertEquals(2, factualBindings(collection).size());
  }

  /** A locally valid dump cannot hide a conflicting numeric binding in another dump. */
  @Test
  public void conflictingResolvedIdentityInAnotherDumpRemainsInCollectionHistory()
      throws Exception {
    byte[] metadata = metadata();
    byte[] original =
        chunk(
            metadata,
            EPOCH_NS,
            1_000,
            1_000_000,
            new ThreadRow[] {new ThreadRow(7, 81, 42, "original-worker")},
            event(102, 21_000, 7, 0, 0, 0, 1, 0, 0, 0));
    byte[] conflicting =
        chunk(
            metadata,
            EPOCH_NS + 5_000_000,
            500_000,
            2_000_000,
            new ThreadRow[] {new ThreadRow(9, 82, 42, "conflicting-worker")},
            event(131, 520_000, 256_000, 9, 1, 0, 0, 0, 0, 0));
    assertEquals(1, factualBindings(load(original)).size());
    assertEquals(1, factualBindings(load(conflicting)).size());
    // Neither dump has a local collision. Dropping history at a dump boundary misses this one.
    assertThrows(IllegalStateException.class, () -> factualBindings(load(original, conflicting)));
    assertThrows(IllegalStateException.class, () -> factualBindings(load(conflicting, original)));
  }

  /** Pins the actual decoded Java-ID preference and OS fallback used for subtraction. */
  @Test
  public void positiveJavaIdPrecedesOsFallbackAcrossTheWholeCollection() throws Exception {
    byte[] metadata = metadata();
    byte[] earlierDump =
        chunk(
            metadata,
            EPOCH_NS,
            1_000,
            1_000_000,
            new ThreadRow[] {new ThreadRow(7, 81, 0, "native-worker")},
            event(102, 21_000, 7, 0, 0, 0, 1, 0, 0, 0));
    byte[] sameFallback =
        chunk(
            metadata,
            EPOCH_NS + 5_000_000,
            500_000,
            2_000_000,
            new ThreadRow[] {new ThreadRow(9, 81, 0, "native-worker")},
            event(131, 520_000, 256_000, 9, 1, 0, 0, 0, 0, 0));
    assertEquals(118_000_000L, syntheticWallTime(load(earlierDump, sameFallback)));
    assertTrue(factualBindings(load(earlierDump, sameFallback)).containsKey(81L));
    byte[] preferredJava =
        chunk(
            metadata,
            EPOCH_NS + 5_000_000,
            500_000,
            2_000_000,
            new ThreadRow[] {new ThreadRow(9, 81, 42, "native-worker")},
            event(131, 520_000, 256_000, 9, 1, 0, 0, 0, 0, 0));
    assertEquals(128_000_000L, syntheticWallTime(load(earlierDump, preferredJava)));
  }

  /** Neither duplicate row order may be silently treated as last-wins by the oracle. */
  @Test
  public void duplicatePoolRowFirstWinsInBothOrders() throws Exception {
    byte[] metadata = metadata();
    ThreadRow original = new ThreadRow(7, 81, 42, "original-worker");
    ThreadRow conflict = new ThreadRow(7, 82, 99, "conflicting-worker");
    byte[] sample = event(102, 21_000, 7, 0, 0, 0, 1, 0, 0, 0);
    Map<Long, String> first =
        factualBindings(
            load(
                chunk(
                    metadata,
                    EPOCH_NS,
                    1_000,
                    1_000_000,
                    new ThreadRow[] {original, conflict},
                    sample)));
    assertEquals("original-worker@81", first.get(42L));
    assertFalse(first.containsKey(99L));
    Map<Long, String> reversed =
        factualBindings(
            load(
                chunk(
                    metadata,
                    EPOCH_NS,
                    1_000,
                    1_000_000,
                    new ThreadRow[] {conflict, original},
                    sample)));
    assertEquals("conflicting-worker@82", reversed.get(99L));
    assertFalse(reversed.containsKey(42L));
  }

  /** Extracts the actual profiler metadata event, not a copied/reinvented metadata schema. */
  private byte[] metadata() throws Exception {
    Path snapshot = Files.createTempFile("taskblock-receiving-metadata-", ".jfr");
    byte[] source;
    try {
      profiler.dump(snapshot);
      source = Files.readAllBytes(snapshot);
    } finally {
      Files.deleteIfExists(snapshot);
    }
    stopProfiler();
    int offset = Math.toIntExact(ByteBuffer.wrap(source).getLong(24));
    int[] cursor = {offset};
    int length = Math.toIntExact(compressed(source, cursor));
    assertEquals(0L, compressed(source, cursor), "Expected an actual JFR metadata event");
    return Arrays.copyOfRange(source, offset, offset + length);
  }

  private static IItemCollection load(byte[]... chunks) throws Exception {
    ByteArrayOutputStream recording = new ByteArrayOutputStream();
    for (byte[] chunk : chunks) recording.write(chunk);
    Path path = Files.createTempFile("taskblock-receiving-scope-", ".jfr");
    try {
      Files.write(path, recording.toByteArray());
      // The consumer deduplicates chunks by their header start timestamp; the
      // controlled clocks give distinct chunks distinct starts, even on overlap.
      IItemCollection decoded = JfrLoaderToolkit.loadEvents(path.toFile());
      if (Boolean.getBoolean("ddprof_test.keep_jfrs")) {
        System.out.println("Receiving collection fixture: " + path);
      }
      return decoded;
    } finally {
      if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) Files.deleteIfExists(path);
    }
  }

  /**
   * Independent collection-wide subtraction oracle for weight-one fixtures (no epoch upscaling).
   */
  private static long syntheticWallTime(IItemCollection collection) {
    long synthetic = 0;
    for (IItemIterable blocks : collection) {
      if (!"datadog.TaskBlock".equals(blocks.getType().getIdentifier())) continue;
      for (IItem block : blocks) {
        IMCThread thread =
            JfrAttributes.EVENT_THREAD.getAccessor(blocks.getType()).getMember(block);
        IRange<IQuantity> lifetime =
            JfrAttributes.LIFETIME.getAccessor(blocks.getType()).getMember(block);
        long start = lifetime.getStart().clampedLongValueIn(UnitLookup.EPOCH_NS);
        long end = lifetime.getEnd().clampedLongValueIn(UnitLookup.EPOCH_NS);
        long represented = 0;
        for (IItemIterable samples : collection) {
          if (!"datadog.MethodSample".equals(samples.getType().getIdentifier())) continue;
          for (IItem sample : samples) {
            IMCThread sampled =
                JfrAttributes.EVENT_THREAD.getAccessor(samples.getType()).getMember(sample);
            long timestamp =
                JfrAttributes.START_TIME
                    .getAccessor(samples.getType())
                    .getMember(sample)
                    .clampedLongValueIn(UnitLookup.EPOCH_NS);
            if (resolvedId(thread) == resolvedId(sampled)
                && start <= timestamp
                && timestamp < end) {
              represented += QUANTUM_NS;
            }
          }
        }
        synthetic += Math.max(0L, end - start - represented);
      }
    }
    return synthetic;
  }

  /** Keeps every observed numeric binding for the complete collection, not only its last chunk. */
  private static Map<Long, String> factualBindings(IItemCollection collection) {
    Map<Long, String> bindings = new HashMap<>();
    for (IItemIterable items : collection) {
      if (!"datadog.MethodSample".equals(items.getType().getIdentifier())
          && !"datadog.TaskBlock".equals(items.getType().getIdentifier())) continue;
      for (IItem item : items) {
        IMCThread thread = JfrAttributes.EVENT_THREAD.getAccessor(items.getType()).getMember(item);
        assertNotNull(thread);
        String facts = thread.getThreadName() + "@" + osId(thread);
        long id = resolvedId(thread);
        String old = bindings.putIfAbsent(id, facts);
        if (old != null && !old.equals(facts)) {
          throw new IllegalStateException("Conflicting decoded identity " + id);
        }
      }
    }
    return bindings;
  }

  /** Matches the pinned consumer's positive Java-ID preference and decoded OS-ID fallback. */
  private static long resolvedId(IMCThread thread) {
    Long javaId = thread.getThreadId();
    return javaId != null && javaId > 0 ? javaId : osId(thread);
  }

  /** Reads the original decoder struct, rather than substituting a guessed OS identity. */
  private static long osId(IMCThread thread) {
    try {
      java.lang.reflect.Field field = thread.getClass().getDeclaredField("osThreadId");
      field.setAccessible(true);
      return ((Number) field.get(thread)).longValue();
    } catch (ReflectiveOperationException e) {
      throw new AssertionError("Decoder does not expose its original OS thread identity", e);
    }
  }

  private static long onlySampleTime(IItemCollection collection) {
    long result = Long.MIN_VALUE;
    for (IItemIterable items : collection) {
      if (!"datadog.MethodSample".equals(items.getType().getIdentifier())) continue;
      for (IItem item : items) {
        assertEquals(Long.MIN_VALUE, result);
        result =
            JfrAttributes.START_TIME
                .getAccessor(items.getType())
                .getMember(item)
                .clampedLongValueIn(UnitLookup.EPOCH_NS);
      }
    }
    assertNotEquals(Long.MIN_VALUE, result);
    return result;
  }

  /**
   * Minimal independent JFR fixture: actual metadata plus controlled, stackless events and pools.
   */
  private static byte[] chunk(
      byte[] metadata,
      long epochOrigin,
      long tickOrigin,
      long frequency,
      ThreadRow[] rows,
      byte[]... events)
      throws Exception {
    ByteArrayOutputStream pool = new ByteArrayOutputStream();
    for (long field : new long[] {1, tickOrigin, 0, 0, 1, 1, 22, rows.length}) put(pool, field);
    for (ThreadRow row : rows) {
      put(pool, row.key);
      string(pool, row.name);
      put(pool, row.osId);
      string(pool, row.name);
      put(pool, row.javaId);
    }
    byte[] checkpoint = framed(pool.toByteArray());
    ByteArrayOutputStream body = new ByteArrayOutputStream();
    body.write(metadata);
    for (byte[] event : events) body.write(event);
    long checkpointOffset = 68L + body.size();
    body.write(checkpoint);
    ByteArrayOutputStream recording = new ByteArrayOutputStream();
    DataOutputStream header = new DataOutputStream(recording);
    header.writeInt(0x464c5200);
    header.writeShort(2);
    header.writeShort(0);
    for (long value :
        new long[] {
          68L + body.size(), checkpointOffset, 68, epochOrigin, 200_000_000L, tickOrigin, frequency
        }) header.writeLong(value);
    header.writeInt(1);
    recording.write(body.toByteArray());
    return recording.toByteArray();
  }

  private static byte[] event(long... fields) throws Exception {
    ByteArrayOutputStream bytes = new ByteArrayOutputStream();
    for (long field : fields) put(bytes, field);
    // AbstractProfilerTest requests tag1/tag2/tag3; preserve the actual metadata's tail.
    for (int i = 0; i < 3; i++) put(bytes, 0);
    return framed(bytes.toByteArray());
  }

  /** JFR permits a fixed five-byte compressed size; the declared size includes that prefix. */
  private static byte[] framed(byte[] payload) throws Exception {
    ByteArrayOutputStream bytes = new ByteArrayOutputStream();
    int size = payload.length + 5;
    for (int i = 0; i < 4; i++, size >>>= 7) bytes.write((size & 127) | 128);
    bytes.write(size);
    bytes.write(payload);
    return bytes.toByteArray();
  }

  private static void string(ByteArrayOutputStream out, String value) throws Exception {
    byte[] utf8 = value.getBytes("UTF-8");
    out.write(3);
    put(out, utf8.length);
    out.write(utf8);
  }

  private static void put(ByteArrayOutputStream out, long value) {
    for (int i = 0; i < 8 && value > 127; i++, value >>>= 7) out.write((int) (value & 127) | 128);
    out.write((int) value);
  }

  private static long compressed(byte[] bytes, int[] cursor) {
    long value = 0;
    for (int i = 0; i < 9; i++) {
      int b = Byte.toUnsignedInt(bytes[cursor[0]++]);
      value |= (long) (i == 8 ? b : b & 127) << (i * 7);
      if (i == 8 || b < 128) return value;
    }
    throw new AssertionError("Invalid compressed integer");
  }

  private static final class ThreadRow {
    final long key;
    final long osId;
    final long javaId;
    final String name;

    ThreadRow(long key, long osId, long javaId, String name) {
      this.key = key;
      this.osId = osId;
      this.javaId = javaId;
      this.name = name;
    }
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=10ms,filter=,wallprecheck=true";
  }
}
