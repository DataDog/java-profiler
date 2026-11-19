/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.alloc;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import java.io.File;
import java.io.IOException;
import java.util.Random;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jol.info.GraphLayout;

public class AllocationProfilerTest extends AbstractProfilerTest {

  @Override
  protected boolean isPlatformSupported() {
    return !(Platform.isJ9() || Platform.isZing()) && Platform.isJavaVersionAtLeast(11);
  }

  /** Cached result of the passwordless-sudo probe ({@code null} until first probed). */
  private static volatile Boolean passwordlessSudo;

  private static final int SUDO_PROBE_TIMEOUT_SECONDS = 10;

  /** Probe without prompting and bound the child wait when passwordless sudo is unavailable. */
  private static boolean canAttachThroughSudo() {
    Boolean cached = passwordlessSudo;
    if (cached != null) {
      return cached;
    }
    boolean ok;
    Process probe = null;
    try {
      probe =
          new ProcessBuilder("sudo", "-n", "true")
              .redirectOutput(ProcessBuilder.Redirect.to(new File("/dev/null")))
              .redirectError(ProcessBuilder.Redirect.to(new File("/dev/null")))
              .start();
      ok = probe.waitFor(SUDO_PROBE_TIMEOUT_SECONDS, TimeUnit.SECONDS) && probe.exitValue() == 0;
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
      ok = false;
    } catch (IOException e) {
      ok = false;
    } finally {
      if (probe != null) {
        probe.destroyForcibly();
      }
    }
    // Only successes are cached: a transient sudo failure (fork pressure, a slow PAM
    // lookup that hit the wait bound) must not pin the skip for the whole worker JVM.
    if (ok) {
      passwordlessSudo = true;
    }
    return ok;
  }

  @RetryingTest(5)
  public void shouldGetObjectAllocationSamples() throws InterruptedException {

    // We seem to hit issues on j9:
    // OSR (On stack replacement) creates crashes with the profiler.
    //     ----------- Stack Backtrace -----------
    // prepareForOSR+0xbf (0x00007F51062A4DDF [libj9jit29.so+0x4a4ddf])
    if (Platform.isJ9() && !Platform.isJavaVersionAtLeast(8)) {
      return;
    }
    Assumptions.assumeFalse(isAsan() || isTsan());
    Assumptions.assumeTrue(canAttachThroughSudo(), "JOL attach requires passwordless sudo");

    AllocatingTarget target1 = new AllocatingTarget();
    AllocatingTarget target2 = new AllocatingTarget();
    runTests(target1, target2);

    // A million-iteration allocation loop produces millions of datadog.ObjectSample events;
    // materializing all of them (each deep-resolved down to its full stack trace) OOMs the test
    // heap, so this reduces per-event in a single streaming pass instead.
    String intArrayName = int[].class.getName();
    String integerArrayName = Integer[].class.getName();
    RecordedSizes recorded =
        reduceEvents(
            "datadog.ObjectSample",
            RecordedSizes::new,
            (acc, item) -> {
              acc.total++;
              String className = item.getClassName("objectClass");
              if (intArrayName.equals(className)) {
                acc.intArray += (long) scaledSize(item);
              } else if (integerArrayName.equals(className)) {
                acc.integerArray += (long) scaledSize(item);
              }
            });
    assertTrue(recorded.total > 0, "datadog.ObjectSample was empty");

    // FIXME when more tests are ported to this structure
    if (!Platform.isMusl()) {
      // JOL on musl seems to be locking up randomly
      assertAllocations(recorded.intArray, int[].class, target1, target2);
      assertAllocations(recorded.integerArray, Integer[].class, target1, target2);
    }
  }

  private static final class RecordedSizes {
    long total;
    long intArray;
    long integerArray;
  }

  private static void assertAllocations(
      long recorded, Class<?> clazz, AllocatingTarget... targets) {
    long allocated = 0;
    for (AllocatingTarget target : targets) {
      allocated += target.getAllocated(clazz);
    }
    assertTrue(recorded > 0, "no allocation samples recorded for " + clazz.getCanonicalName());
    double error = Math.abs(recorded - allocated) / (double) allocated;
    assertTrue(
        error <= 0.50,
        String.format(
            "allocation samples should be within 10pct tolerance of allocated memory (recorded %d, allocated %d :: %4.2f)",
            recorded, allocated, error * 100));
  }

  @Override
  protected String getProfilerCommand() {
    return "memory=" + (256 * 1024) + ":a";
  }

  public static class AllocatingTarget extends ClassValue<AtomicLong> implements Runnable {
    public static volatile Object sink;

    @Override
    public void run() {
      Random random = new Random(0);
      for (int i = 0; i < 1_000_000; i++) {
        allocate(random);
      }
    }

    public long getAllocated(Class<?> clazz) {
      return get(clazz).get();
    }

    private void allocate(Random random) {
      Object object;
      if (random.nextBoolean()) {
        object = new int[128 * 1000];
      } else {
        object = new Integer[128 * 1000];
      }
      if (!Platform.isMusl()) {
        // JOL does not work that well with musl
        get(object.getClass()).addAndGet(GraphLayout.parseInstance(object).totalSize());
      }
      sink = object;
    }

    @Override
    protected AtomicLong computeValue(Class<?> type) {
      return new AtomicLong();
    }
  }
}
