/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.Instant;
import java.util.Map;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/** Requires JDK 11+ because HotSpot 8 sleep states are inconsistent. */
public class PrecheckTest extends AbstractProfilerTest {
  private static final int OSTHREAD_STATE_SLEEPING = 7;
  private static final int POOL_WORKERS = 4;
  private static final long POOL_SLEEP_MILLIS = 300;
  private static final String TAIL_WEIGHT_THREAD = "precheck-tail-weight";
  private static final int TAIL_WEIGHT_ITERATIONS = 50;
  private static final int TAIL_WEIGHT_SLEEP_MILLIS = 6;
  private static final long TAIL_WEIGHT_RUNNABLE_NANOS = 2_000_000L;
  private static volatile int tailWeightSpinSink;

  @Test
  public void testSleepingThreadIsNotSampled() throws InterruptedException {
    Assumptions.assumeTrue(!Platform.isJ9());
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
    leaveClearedInitializedContext();
    registerOutsideContextWindow();

    long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
    assertTrue(token != 0, "Expected native blockEnter to arm SLEEPING state");
    Instant ownedStart;
    Instant ownedEnd;
    try {
      ownedStart = Instant.now();
      Thread.sleep(300);
      ownedEnd = Instant.now();
    } finally {
      ProfilerOwnedBlockHooks.blockExit(profiler, token);
    }

    stopProfiler();

    long sampleCount =
        samplesForThread(
            Thread.currentThread().getName(),
            ownedStart.getEpochSecond() * 1_000_000_000L + ownedStart.getNano(),
            ownedEnd.getEpochSecond() * 1_000_000_000L + ownedEnd.getNano());
    System.out.println(
        "PRECHECK_OWNED_INTERVAL samples="
            + sampleCount
            + " outside="
            + (samplesForThread(Thread.currentThread().getName()) - sampleCount));
    // Lifecycle ownership suppresses deliberate signals from blockEnter until blockExit.
    // A few boundary-race samples remain possible.
    assertTrue(
        sampleCount < 10,
        "Expected nearly no MethodSample events for a sleeping thread with wallprecheck=true, got: "
            + sampleCount);

    Map<String, Long> counters = profiler.getDebugCounters();
    if (counters.containsKey("wc_signals_suppressed_owned_block")) {
      assertTrue(
          counters.get("wc_signals_suppressed_owned_block") > 0,
          "wc_signals_suppressed_owned_block should be > 0 for a 300 ms Thread.sleep()");
    }
  }

  @Test
  public void delegatedJavaObjectWaitEmitsOneCompleteTaskBlock() throws Exception {
    Assumptions.assumeTrue(!Platform.isJ9());
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
    DelegatedObjectWaitScenario.assertRecording(getProfilerCommand());
  }

  @Test
  public void testBlockEnterRejectedWithActiveTraceContext() {
    Assumptions.assumeTrue(!Platform.isJ9());
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

    profiler.setTraceContext(0x5100L, 0x5101L, 0L, 0x5101L, -1, null, -1, null);
    try {
      long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
      assertEquals(
          0L, token, "Expected blockEnter to reject arming while an active trace context is set");
    } finally {
      profiler.clearTraceContext();
    }
  }

  /**
   * Verifies that {@code samplePoolSize} in {@code datadog.WallClockSamplingEpoch} still counts
   * threads whose owned blocked run is already suppressed. Both filtered and unfiltered timers
   * select their reservoir before precheck; a suppressed selection consumes capacity and counts as
   * successful for epoch upscaling, while samplePoolSize counts every collected candidate.
   *
   * @throws InterruptedException if a worker is interrupted
   */
  @Test
  public void samplePoolSizeCountsSuppressedThreads() throws InterruptedException {
    Assumptions.assumeTrue(!Platform.isJ9());
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

    // Fewer workers than the default reservoir (16 threads per tick), so every
    // unsuppressed worker is signaled and armed on its first tick.
    Thread[] workers = new Thread[POOL_WORKERS];
    for (int i = 0; i < POOL_WORKERS; i++) {
      workers[i] =
          new Thread(
              () -> {
                long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
                try {
                  Thread.sleep(POOL_SLEEP_MILLIS);
                } catch (InterruptedException ignored) {
                } finally {
                  ProfilerOwnedBlockHooks.blockExit(profiler, token);
                }
              },
              "precheck-pool-" + i);
      workers[i].start();
    }
    for (Thread worker : workers) {
      worker.join();
    }

    stopProfiler();

    // Suppressed workers remain candidates in the epoch's sample pool.
    boolean sawFullPoolWhileSuppressing = false;
    for (JfrEvent epoch : verifyEvents("datadog.WallClockSamplingEpoch")) {
      if (epoch.getLong("numSuppressedOwnedBlock", 0) >= POOL_WORKERS
          && epoch.getLong("samplePoolSize", 0) >= POOL_WORKERS) {
        sawFullPoolWhileSuppressing = true;
        break;
      }
    }
    assertTrue(
        sawFullPoolWhileSuppressing,
        "Expected an epoch that suppressed all "
            + POOL_WORKERS
            + " workers while still counting them in samplePoolSize");
  }

  @Test
  public void unownedSleepingThreadIsNotExactOncePerRunSuppressed() throws Exception {
    Assumptions.assumeTrue(!Platform.isJ9());
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
    leaveClearedInitializedContext();

    registerOutsideContextWindow();

    Thread.sleep(300);

    stopProfiler();

    assertUnownedSamples(Thread.currentThread().getName());
  }

  @Test
  public void unownedSleepingTailWeightIsPreserved() throws Exception {
    Assumptions.assumeTrue(!Platform.isJ9());
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

    Thread sleeper =
        new Thread(
            () -> {
              registerOutsideContextWindow();
              try {
                for (int i = 0; i < TAIL_WEIGHT_ITERATIONS; i++) {
                  Thread.sleep(TAIL_WEIGHT_SLEEP_MILLIS);
                  long runnableUntil = System.nanoTime() + TAIL_WEIGHT_RUNNABLE_NANOS;
                  while (System.nanoTime() < runnableUntil) {
                    tailWeightSpinSink++;
                    // Brief runnable gap forces the unowned blocked state to flush.
                  }
                }
              } catch (InterruptedException ignored) {
              }
            },
            TAIL_WEIGHT_THREAD);

    sleeper.start();
    sleeper.join();

    stopProfiler();

    assertUnownedSamples(TAIL_WEIGHT_THREAD);
  }

  @Test
  public void tracedSleepingThreadIsSampled() throws InterruptedException {
    Assumptions.assumeTrue(!Platform.isJ9());
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

    Map<String, Long> countersBefore = profiler.getDebugCounters();
    profiler.setTraceContext(0x5100L, 0x5101L, 0L, 0x5101L, -1, null, -1, null);
    try {
      Thread.sleep(300);
    } finally {
      profiler.clearTraceContext();
    }

    stopProfiler();

    long sampleCount = samplesForThread(Thread.currentThread().getName());
    assertTrue(
        sampleCount >= 10,
        "Expected normal MethodSample volume for traced sleep, got: " + sampleCount);

    if (countersBefore.containsKey("wc_signals_suppressed_owned_block")) {
      long suppressedBefore = countersBefore.get("wc_signals_suppressed_owned_block");
      long suppressedAfter =
          profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L);
      assertEquals(
          suppressedBefore,
          suppressedAfter,
          "wc_signals_suppressed_owned_block must not increment for traced sleep");
    }
  }

  @Test
  public void suppressionCounterIsZeroWhenPrecheckDisabled() throws Exception {
    Assumptions.assumeTrue(!Platform.isJ9());
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

    // Stop the wallprecheck=true recording started by @BeforeEach before starting a new one.
    stopProfiler();

    Map<String, Long> before = profiler.getDebugCounters();
    if (!before.containsKey("wc_signals_suppressed_owned_block")) {
      return; // counter not available in this build
    }
    long suppressedBefore = before.get("wc_signals_suppressed_owned_block");

    Path recordingB =
        Files.createTempFile(Paths.get("/tmp/recordings"), "PrecheckTest_disabled_", ".jfr");
    profiler.execute(
        "start,"
            + getPrecheckDisabledProfilerCommand()
            + ",attributes=tag1;tag2;tag3,jfr,file="
            + recordingB.toAbsolutePath());
    Thread.sleep(300);
    profiler.stop();

    long suppressedAfter =
        profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L);
    Files.deleteIfExists(recordingB);

    assertEquals(
        suppressedBefore,
        suppressedAfter,
        "wc_signals_suppressed_owned_block must not increment when wallprecheck=false");
  }

  /** Leaves an initialized but cleared and invalid native OTEP record. */
  private void leaveClearedInitializedContext() {
    profiler.setTraceContext(0x7700L, 0x7701L, 0L, 0x7701L, -1, null, -1, null);
    profiler.clearTraceContext();
  }

  /** Registers the calling thread lazily, then leaves its sleep outside the context window. */
  private void registerOutsideContextWindow() {
    profiler.addThread();
    profiler.removeThread();
  }

  /** Rejected native states must preserve the next valid generic-hook owner. */
  @Test
  public void invalidBlockStatesLeaveSleepingHookUsable() throws Exception {
    Assumptions.assumeTrue(!Platform.isJ9());
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
    leaveClearedInitializedContext();
    for (int state : new int[] {Integer.MIN_VALUE, -1, 0, 6, 8, Integer.MAX_VALUE}) {
      assertEquals(
          0L,
          ProfilerOwnedBlockHooks.blockEnter(profiler, state),
          "Unsupported state must be rejected before ownership: " + state);
    }
    long baseline =
        profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L);
    long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
    assertTrue(token != 0, "Invalid states must not strand ownership");
    try {
      ProfilerOwnedBlockHooks.blockExit(profiler, 0L);
      Thread.sleep(100L);
      assertTrue(
          profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L)
              > baseline,
          "Zero-token exit must not disarm the valid owner's suppression");
    } finally {
      ProfilerOwnedBlockHooks.blockExit(profiler, token);
    }
    long next = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
    assertTrue(next != 0, "Valid exit must release ownership for the next interval");
    ProfilerOwnedBlockHooks.blockExit(profiler, next);
  }

  /** Virtual hooks cannot enter or clear platform-thread ownership. */
  @Test
  public void virtualBlockHooksCannotConsumePlatformOwner() throws Exception {
    Assumptions.assumeTrue(!Platform.isJ9());
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(21));
    leaveClearedInitializedContext();
    Method startVirtualThread = Thread.class.getMethod("startVirtualThread", Runnable.class);
    long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
    assertTrue(token != 0);
    AtomicReference<Throwable> failure = new AtomicReference<>();
    try {
      Thread virtual =
          (Thread)
              startVirtualThread.invoke(
                  null,
                  (Runnable)
                      () -> {
                        try {
                          assertEquals(
                              0L,
                              ProfilerOwnedBlockHooks.blockEnter(
                                  profiler, OSTHREAD_STATE_SLEEPING));
                          ProfilerOwnedBlockHooks.blockExit(profiler, token);
                          Thread.sleep(20L);
                          assertEquals(
                              0L,
                              ProfilerOwnedBlockHooks.blockEnter(
                                  profiler, OSTHREAD_STATE_SLEEPING));
                        } catch (Throwable error) {
                          failure.set(error);
                        }
                      });
      virtual.join(5_000L);
      assertFalse(virtual.isAlive());
      if (failure.get() != null) throw new AssertionError(failure.get());
      long baseline =
          profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L);
      Thread.sleep(100L);
      assertTrue(
          profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L)
              > baseline,
          "Virtual exit must not clear the real platform owner's suppression");
    } finally {
      ProfilerOwnedBlockHooks.blockExit(profiler, token);
    }
    long next = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
    assertTrue(next != 0, "Virtual rejection must preserve the subsequent platform control");
    ProfilerOwnedBlockHooks.blockExit(profiler, next);
  }

  @Override
  protected String getProfilerCommand() {
    // Owned-block suppression requires unfiltered sampling outside context
    // windows; addThread() registrations must leave their window before blocking.
    return "wall=1ms,filter=,wallprecheck=true";
  }

  protected String getPrecheckDisabledProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=false";
  }

  /** Returns whether the engine can replay unowned blocked samples with a cached stack. */
  protected boolean usesWeightedUnownedFallback() {
    return !usesDelegatedWallEngine();
  }

  /** Reads the recorded engine because argument selection can fall back. */
  private boolean usesDelegatedWallEngine() {
    String engine = null;
    for (JfrEvent setting : verifyEvents("jdk.ActiveSetting", true)) {
      if ("wallEngine".equals(setting.getString("name"))) engine = setting.getString("value");
    }
    assertNotNull(engine, "Missing actual wall engine setting");
    assertTrue(
        "WallClock (JVMTI)".equals(engine) || "WallClock (ASGCT)".equals(engine),
        "Unexpected wall engine: " + engine);
    System.out.println("PRECHECK_ENGINE selected=" + engine);
    return "WallClock (JVMTI)".equals(engine);
  }

  private long samplesForThread(String threadName) {
    return samplesForThread(threadName, Long.MIN_VALUE, Long.MAX_VALUE);
  }

  /** Counts only events timestamped inside the measured owned interval. */
  private long samplesForThread(String threadName, long startNanos, long endNanos) {
    long count = 0;
    JfrEvents events = verifyEvents("datadog.MethodSample", false);
    for (JfrEvent item : events) {
      if (threadName.equals(item.getThreadName("eventThread"))) {
        Long timestamp = item.getLong("startTime");
        assertNotNull(timestamp, "Missing MethodSample timestamp");
        if (timestamp >= startNanos && timestamp <= endNanos) count++;
      }
    }
    return count;
  }

  /** Verifies weighted ASGCT fallback or ordinary delegated sampling for the named thread. */
  private void assertUnownedSamples(String threadName) {
    long count = 0;
    long weight = 0;
    JfrEvents events = verifyEvents("datadog.MethodSample", false);
    for (JfrEvent item : events) {
      if (threadName.equals(item.getThreadName("eventThread"))) {
        count++;
        weight += item.getLong(WEIGHT, 0);
        if (!usesWeightedUnownedFallback()) {
          assertEquals(
              1L, item.getLong(WEIGHT, 0), "Delegated unowned samples must retain unit weight");
        }
      }
    }
    assertTrue(count > 0, "Expected MethodSample events for " + threadName);
    Map<String, Long> counters = profiler.getDebugCounters();
    long suppressed = counters.getOrDefault("wc_unowned_blocked_suppressed", 0L);
    long recorded = counters.getOrDefault("wc_unowned_blocked_recorded", 0L);
    if (usesWeightedUnownedFallback()) {
      assertTrue(
          weight > count,
          "Expected suppressed observations to be represented by weight for "
              + threadName
              + ", count="
              + count
              + ", weight="
              + weight);
      assertTrue(recorded > 0, "Expected weighted unowned-block fallback samples");
      assertTrue(suppressed > 0, "Expected weighted unowned-block fallback suppression");
    } else {
      assertEquals(0L, suppressed, "Delegated unowned observations must remain sampled");
      assertEquals(0L, recorded, "Delegated samples must bypass the weighted fallback");
    }
  }
}
