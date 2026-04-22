package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import org.junit.jupiter.api.TestTemplate;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import org.junit.jupiter.params.provider.ValueSource;

import java.lang.reflect.Method;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.locks.LockSupport;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Integration tests for the virtual thread continuation unwind paths in walkVM.
 *
 * CPU-bound VT: never suspends, so all frames are thawed. The profiler detects
 * cont_entry_return_pc as the return PC of the bottommost thawed frame and traverses
 * enterSpecial to reach carrier frames.
 *
 * Blocking VT: parks/unparks repeatedly; when remounted with frozen frames still in the
 * StackChunk, cont_returnBarrier is the return PC of the bottommost thawed frame.
 *
 * Skipped entirely on JDK &lt; 21 via {@link #isPlatformSupported()}.
 *
 * <h3>Negative-test mode</h3>
 * Set {@code DDPROF_DISABLE_CONT_UNWIND=1} to skip both native unwind paths at runtime.
 * With this flag the test will fail (carrier frames absent), confirming the fix is necessary.
 */
public class VirtualThreadWallClockTest extends CStackAwareAbstractProfilerTest {

    /** DCE sink for the CPU-bound spin loop. */
    private volatile long sink;

    public VirtualThreadWallClockTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isJavaVersionAtLeast(21);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=";
    }

    /**
     * Starts a virtual thread using reflection so the class compiles with {@code --release 8}.
     * Equivalent to {@code Thread.ofVirtual().start(task)}.
     */
    private static Thread startVirtualThread(Runnable task) throws Exception {
        // Thread.ofVirtual() -> Thread.Builder.OfVirtual
        Method ofVirtual = Thread.class.getMethod("ofVirtual");
        Object builder = ofVirtual.invoke(null);
        // Look up start(Runnable) via the public Thread.Builder interface to avoid
        // IllegalAccessException on the internal ThreadBuilders$VirtualThreadBuilder class
        Class<?> builderInterface = Class.forName("java.lang.Thread$Builder");
        Method start = builderInterface.getMethod("start", Runnable.class);
        return (Thread) start.invoke(builder, task);
    }

    /**
     * Asserts that carrier frames (ForkJoinWorkerThread) are visible in the stack traces,
     * confirming that continuation unwinding is working correctly.
     */
    private void assertCarrierFramesVisible(IItemCollection events) {
        boolean carrierVisible = false;
        for (IItemIterable samples : events) {
            IMemberAccessor<String, IItem> frameAccessor =
                    JdkAttributes.STACK_TRACE_STRING.getAccessor(samples.getType());
            if (frameAccessor == null) continue;
            for (IItem sample : samples) {
                String stackTrace = frameAccessor.getMember(sample);
                if (stackTrace == null || !stackTrace.contains("VirtualThreadWallClockTest")) continue;
                // Standard JDK VTs run on ForkJoinWorkerThread carriers.
                // If the JVM ever changes the default carrier pool this check must be updated.
                if (stackTrace.contains("ForkJoinWorkerThread")) {
                    carrierVisible = true;
                    break;
                }
            }
            if (carrierVisible) break;
        }
        if (!carrierVisible) {
            System.out.println("=== MISSING CARRIER — sample stack traces ===");
            int printed = 0;
            outer:
            for (IItemIterable dump : events) {
                IMemberAccessor<String, IItem> fa =
                        JdkAttributes.STACK_TRACE_STRING.getAccessor(dump.getType());
                if (fa == null) continue;
                for (IItem sample : dump) {
                    String st = fa.getMember(sample);
                    if (st != null && st.contains("VirtualThreadWallClockTest")) {
                        System.out.println("--- vt sample " + (++printed) + " ---");
                        System.out.println(st);
                        if (printed >= 5) break outer;
                    }
                }
            }
            // Carrier-only samples: ForkJoinWorkerThread without VT frames
            int carrierPrinted = 0;
            System.out.println("=== CARRIER-ONLY samples (no VT frames) ===");
            outer2:
            for (IItemIterable dump : events) {
                IMemberAccessor<String, IItem> fa =
                        JdkAttributes.STACK_TRACE_STRING.getAccessor(dump.getType());
                if (fa == null) continue;
                for (IItem sample : dump) {
                    String st = fa.getMember(sample);
                    if (st != null && st.contains("ForkJoinWorkerThread") && !st.contains("VirtualThreadWallClockTest")) {
                        System.out.println("--- carrier " + (++carrierPrinted) + " ---");
                        System.out.println(st);
                        if (carrierPrinted >= 3) break outer2;
                    }
                }
            }
            if (carrierPrinted == 0) {
                // No carrier samples at all — print first 3 arbitrary samples
                System.out.println("=== No carrier samples — first 3 arbitrary samples ===");
                int anyPrinted = 0;
                outer3:
                for (IItemIterable dump : events) {
                    IMemberAccessor<String, IItem> fa =
                            JdkAttributes.STACK_TRACE_STRING.getAccessor(dump.getType());
                    if (fa == null) continue;
                    for (IItem sample : dump) {
                        String st = fa.getMember(sample);
                        if (st != null && !st.isEmpty()) {
                            System.out.println("--- any " + (++anyPrinted) + " ---");
                            System.out.println(st);
                            if (anyPrinted >= 3) break outer3;
                        }
                    }
                }
            }
        }
        assertTrue(carrierVisible,
                "No sample showed carrier-thread frames (ForkJoinWorkerThread) — continuation unwind may be broken");
    }

    /**
     * CPU-bound virtual thread (all frames thawed).
     *
     * The VT runs a pure spin loop for ~2 seconds and never parks, so all frames are always
     * thawed. The profiler detects cont_entry_return_pc and traverses enterSpecial to reach
     * carrier frames.
     */
    @RetryTest(5)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    public void samplesCarrierFramesFromCpuBoundVT(@CStack String cstack) throws Exception {
        // Carrier-frame unwinding is only enabled for vmx (cstack=vm does not set carrier_frames).
        // fp/dwarf use ASGCT and cannot cross the continuation boundary at all.
        assumeTrue(cstack.equals("vmx"),
                "carrier-frame unwind requires cstack=vmx");
        waitForProfilerReady(2_000);
        Thread vt = startVirtualThread(() -> {
            registerCurrentThreadForWallClockProfiling();
            long sum = 0;
            long deadline = System.nanoTime() + 2_000_000_000L;
            while (System.nanoTime() < deadline) {
                sum ^= System.nanoTime();
            }
            sink = sum;
        });
        vt.join();
        stopProfiler();

        Map<String, Long> countersA = profiler.getDebugCounters();
        System.out.println("=== COUNTERS CpuBound cstack=" + cstack + " ===");
        System.out.println("  enter_special_hit : " + countersA.getOrDefault("walkvm_enter_special_hit", 0L));
        System.out.println("  cont_barrier_hit  : " + countersA.getOrDefault("walkvm_cont_barrier_hit", 0L));
        System.out.println("  cont_entry_null   : " + countersA.getOrDefault("walkvm_cont_entry_null", 0L));
        System.out.println("  break_compiled    : " + countersA.getOrDefault("walkvm_break_compiled", 0L));
        System.out.println("  hit_codeheap      : " + countersA.getOrDefault("walkvm_hit_codeheap", 0L));
        System.out.println("  java_frame_ok     : " + countersA.getOrDefault("walkvm_java_frame_ok", 0L));
        System.out.println("  no_vmthread       : " + countersA.getOrDefault("walkvm_no_vmthread", 0L));
        System.out.println("  cached_not_java   : " + countersA.getOrDefault("walkvm_cached_not_java", 0L));
        System.out.println("  break_interpreted : " + countersA.getOrDefault("walkvm_break_interpreted", 0L));
        System.out.println("  depth_zero        : " + countersA.getOrDefault("walkvm_depth_zero", 0L));

        verifyCStackSettings();

        assertCarrierFramesVisible(verifyEvents("datadog.MethodSample"));
    }

    /**
     * Blocking virtual thread (frozen frames in StackChunk).
     *
     * The VT parks itself 100 times. The main thread sleeps 10ms between each unpark so the
     * wall-clock sampler (1ms period) has time to fire while the VT is mounted with frozen
     * frames still in the StackChunk (cont_returnBarrier as the return PC).
     */
    @RetryTest(5)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    public void samplesCarrierFramesFromBlockingVT(@CStack String cstack) throws Exception {
        // Carrier-frame unwinding is only enabled for vmx (cstack=vm does not set carrier_frames).
        // fp/dwarf use ASGCT and cannot cross the continuation boundary at all.
        assumeTrue(cstack.equals("vmx"),
                "carrier-frame unwind requires cstack=vmx");
        // cont_returnBarrier detection is not yet verified on JDK 25+ where the stub
        // may have changed; skip rather than fail until verified.
        assumeTrue(!Platform.isJavaVersionAtLeast(25),
                "cont_returnBarrier unwind not yet verified on JDK 25+");
        waitForProfilerReady(2_000);
        final CountDownLatch started = new CountDownLatch(1);
        Thread vt = startVirtualThread(() -> {
            registerCurrentThreadForWallClockProfiling();
            started.countDown();
            for (int i = 0; i < 100; i++) {
                LockSupport.park();
                // Do some work after unpark to give profiler a chance to sample
                // while mounted with potentially frozen frames
                long sum = 0;
                for (int j = 0; j < 10000; j++) {
                    sum += System.nanoTime();
                }
                sink = sum;
            }
        });
        started.await();
        for (int i = 0; i < 100; i++) {
            Thread.sleep(10); // give wall-clock sampler time to fire during remount
            LockSupport.unpark(vt);
        }
        vt.join(15_000);
        assertFalse(vt.isAlive(), "Virtual thread did not complete within timeout");
        stopProfiler();

        Map<String, Long> countersB = profiler.getDebugCounters();
        System.out.println("=== COUNTERS Blocking cstack=" + cstack + " ===");
        System.out.println("  enter_special_hit : " + countersB.getOrDefault("walkvm_enter_special_hit", 0L));
        System.out.println("  cont_barrier_hit  : " + countersB.getOrDefault("walkvm_cont_barrier_hit", 0L));
        System.out.println("  cont_entry_null   : " + countersB.getOrDefault("walkvm_cont_entry_null", 0L));
        System.out.println("  break_compiled    : " + countersB.getOrDefault("walkvm_break_compiled", 0L));
        System.out.println("  hit_codeheap      : " + countersB.getOrDefault("walkvm_hit_codeheap", 0L));
        System.out.println("  java_frame_ok     : " + countersB.getOrDefault("walkvm_java_frame_ok", 0L));
        System.out.println("  no_vmthread       : " + countersB.getOrDefault("walkvm_no_vmthread", 0L));
        System.out.println("  cached_not_java   : " + countersB.getOrDefault("walkvm_cached_not_java", 0L));
        System.out.println("  break_interpreted : " + countersB.getOrDefault("walkvm_break_interpreted", 0L));
        System.out.println("  depth_zero        : " + countersB.getOrDefault("walkvm_depth_zero", 0L));

        verifyCStackSettings();

        assertCarrierFramesVisible(verifyEvents("datadog.MethodSample"));
    }
}
