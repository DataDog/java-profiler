package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.lang.ref.PhantomReference;
import java.lang.ref.ReferenceQueue;
import java.lang.ref.SoftReference;
import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Aggressive stress test for CTimer CPU profiling during heavy GC activity.
 *
 * <p>This test attempts to reproduce crashes in signal handlers when signals are delivered to GC
 * threads during collection phases, particularly on musl-based systems.
 *
 * <p>The test stresses:
 *
 * <ul>
 *   <li>CTimer per-thread timers with very aggressive sampling (10us)
 *   <li>Heavy G1 GC activity with mixed collections
 *   <li>Humongous allocations to stress G1 humongous handling
 *   <li>Reference processing (weak, soft, phantom) during GC
 *   <li>Concurrent GC phases where GC threads are CPU-active
 * </ul>
 */
public class CTimerGCStressTest extends AbstractProfilerTest {

  private static final int ALLOCATION_THREADS = 8;
  private static final int GC_TRIGGER_THREADS = 2;
  private static final int DURATION_SECONDS = 30;

  // Allocation sizes to stress different GC code paths
  private static final int SMALL_OBJECT_SIZE = 256;
  private static final int MEDIUM_OBJECT_SIZE = 4096;
  private static final int LARGE_OBJECT_SIZE = 64 * 1024;
  // Humongous objects (> G1 region size / 2, typically > 512KB)
  private static final int HUMONGOUS_OBJECT_SIZE = 1024 * 1024;

  private final AtomicBoolean running = new AtomicBoolean(true);
  private final AtomicLong allocationCount = new AtomicLong(0);
  private final AtomicLong gcCount = new AtomicLong(0);
  private final AtomicLong humongousCount = new AtomicLong(0);

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isLinux();
  }

  @Test
  public void testCTimerWithHeavyGCActivity() throws Exception {
    assumeTrue(Platform.isLinux(), "CTimer (timer_create) is Linux-only");

    System.out.println("=== CTimer GC Stress Test ===");
    System.out.println("Threads: " + ALLOCATION_THREADS + " allocators, " + GC_TRIGGER_THREADS + " GC triggers");
    System.out.println("Duration: " + DURATION_SECONDS + " seconds");
    System.out.println("Sampling: 10us (very aggressive)");
    System.out.println("This test exercises signal handler on GC threads.");
    System.out.println();

    List<Thread> threads = new ArrayList<>();
    CountDownLatch startLatch = new CountDownLatch(1);
    CountDownLatch doneLatch = new CountDownLatch(ALLOCATION_THREADS + GC_TRIGGER_THREADS);

    // Start allocation threads
    for (int i = 0; i < ALLOCATION_THREADS; i++) {
      Thread t = new Thread(new AllocationWorker(startLatch, doneLatch, i), "GCStress-Alloc-" + i);
      threads.add(t);
      t.start();
    }

    // Start multiple GC trigger threads for more pressure
    for (int i = 0; i < GC_TRIGGER_THREADS; i++) {
      Thread t = new Thread(new GCTriggerWorker(startLatch, doneLatch, i), "GCStress-Trigger-" + i);
      threads.add(t);
      t.start();
    }

    // Let threads run
    startLatch.countDown();

    // Run for specified duration, printing progress
    long startTime = System.currentTimeMillis();
    while (System.currentTimeMillis() - startTime < TimeUnit.SECONDS.toMillis(DURATION_SECONDS)) {
      Thread.sleep(5000);
      System.out.printf(
          "Progress: allocations=%d, humongous=%d, GCs=%d%n",
          allocationCount.get(), humongousCount.get(), gcCount.get());
    }

    // Stop threads
    running.set(false);

    // Wait for completion
    assertTrue(doneLatch.await(60, TimeUnit.SECONDS), "Threads should complete");

    System.out.println();
    System.out.println("=== Results ===");
    System.out.println("Total allocations: " + allocationCount.get());
    System.out.println("Humongous allocations: " + humongousCount.get());
    System.out.println("Explicit GC triggers: " + gcCount.get());

    // Stop profiler and verify events
    stopProfiler();

    IItemCollection events = verifyEvents("datadog.ExecutionSample");
    assertTrue(events.hasItems(), "Should have execution samples");

    int sampleCount = 0;
    int jvmModeSamples = 0;

    for (IItemIterable cpuSamples : events) {
      IMemberAccessor<String, IItem> frameAccessor =
          JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
      IMemberAccessor<String, IItem> modeAccessor =
          THREAD_EXECUTION_MODE.getAccessor(cpuSamples.getType());

      for (IItem sample : cpuSamples) {
        sampleCount++;
        String stackTrace = frameAccessor.getMember(sample);
        String mode = modeAccessor != null ? modeAccessor.getMember(sample) : null;

        if ("JVM".equals(mode)) {
          jvmModeSamples++;
        }

        assertFalse(
            stackTrace != null && stackTrace.contains("jvmtiError"),
            "Stack trace should not contain jvmtiError");
      }
    }

    System.out.println("Total samples: " + sampleCount);
    System.out.println("JVM mode samples: " + jvmModeSamples);

    assertTrue(sampleCount > 0, "Should have collected CPU samples");
  }

  /** Worker that allocates objects with various patterns to stress GC. */
  private class AllocationWorker implements Runnable {
    private final CountDownLatch startLatch;
    private final CountDownLatch doneLatch;
    private final int workerId;
    private final List<WeakReference<byte[]>> weakRefs = new ArrayList<>();
    private final List<SoftReference<byte[]>> softRefs = new ArrayList<>();
    private final ReferenceQueue<byte[]> refQueue = new ReferenceQueue<>();
    private final List<PhantomReference<byte[]>> phantomRefs = new ArrayList<>();

    AllocationWorker(CountDownLatch startLatch, CountDownLatch doneLatch, int workerId) {
      this.startLatch = startLatch;
      this.doneLatch = doneLatch;
      this.workerId = workerId;
    }

    @Override
    public void run() {
      try {
        startLatch.await();

        List<byte[]> shortLived = new ArrayList<>();
        List<byte[]> longLived = new ArrayList<>();
        int iteration = 0;

        while (running.get()) {
          iteration++;

          // Small allocations - young gen pressure
          for (int i = 0; i < 200 && running.get(); i++) {
            shortLived.add(new byte[SMALL_OBJECT_SIZE]);
            allocationCount.incrementAndGet();
          }
          shortLived.clear();

          // Medium allocations
          for (int i = 0; i < 50 && running.get(); i++) {
            shortLived.add(new byte[MEDIUM_OBJECT_SIZE]);
            allocationCount.incrementAndGet();
          }
          shortLived.clear();

          // Large allocations - may trigger GC
          for (int i = 0; i < 10 && running.get(); i++) {
            byte[] data = new byte[LARGE_OBJECT_SIZE];
            if (longLived.size() < 500) {
              longLived.add(data);
            }
            allocationCount.incrementAndGet();
          }

          // Humongous allocations (every 10 iterations) - stress G1 humongous handling
          if (iteration % 10 == workerId) {
            try {
              byte[] humongous = new byte[HUMONGOUS_OBJECT_SIZE];
              humongousCount.incrementAndGet();
              // Don't keep - let it become garbage immediately
            } catch (OutOfMemoryError e) {
              // Expected under heavy pressure
            }
          }

          // Reference processing stress
          weakRefs.add(new WeakReference<>(new byte[SMALL_OBJECT_SIZE]));
          softRefs.add(new SoftReference<>(new byte[MEDIUM_OBJECT_SIZE]));
          phantomRefs.add(new PhantomReference<>(new byte[SMALL_OBJECT_SIZE], refQueue));

          // Cleanup references periodically
          if (weakRefs.size() > 5000) {
            weakRefs.subList(0, 2500).clear();
          }
          if (softRefs.size() > 2000) {
            softRefs.subList(0, 1000).clear();
          }
          if (phantomRefs.size() > 5000) {
            phantomRefs.subList(0, 2500).clear();
          }

          // Occasionally clear long-lived to trigger mixed GC
          if (iteration % 100 == 0 && longLived.size() > 100) {
            longLived.subList(0, longLived.size() / 2).clear();
          }

          // Drain phantom reference queue
          while (refQueue.poll() != null) {
            // Just drain
          }
        }
      } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
      } finally {
        doneLatch.countDown();
      }
    }
  }

  /** Worker that triggers GC frequently. */
  private class GCTriggerWorker implements Runnable {
    private final CountDownLatch startLatch;
    private final CountDownLatch doneLatch;
    private final int workerId;

    GCTriggerWorker(CountDownLatch startLatch, CountDownLatch doneLatch, int workerId) {
      this.startLatch = startLatch;
      this.doneLatch = doneLatch;
      this.workerId = workerId;
    }

    @Override
    public void run() {
      try {
        startLatch.await();

        while (running.get()) {
          // Stagger GC triggers between workers
          Thread.sleep(100 + workerId * 50);
          System.gc();
          gcCount.incrementAndGet();
        }
      } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
      } finally {
        doneLatch.countDown();
      }
    }
  }

  @Override
  protected String getProfilerCommand() {
    // Very aggressive sampling to maximize chance of hitting GC threads
    return "cpu=10us,event=ctimer";
  }
}
