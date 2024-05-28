package com.datadoghq.profiler.memleak;

import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.Aggregators;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.ItemFilters;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicLong;

import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Assumptions;

public class GCGenerationsTest extends AbstractProfilerTest {
    @Override
    protected String getProfilerCommand() {
        return "generations=true,cstack=fp";
    }

    @RetryingTest(5)
    public void shouldGetLiveObjectSamples() throws InterruptedException {
        Assumptions.assumeFalse(System.getProperty("java.version").contains("1.8") || Platform.isJ9() || Platform.isZing());
        MemLeakTarget target1 = new MemLeakTarget();
        MemLeakTarget target2 = new MemLeakTarget();
        runTests(target1, target2);
        IItemCollection allocations = verifyEvents("datadog.HeapLiveObject");

//        assertAllocations(allocations, int[].class, target1, target2);
//        assertAllocations(allocations, Integer[].class, target1, target2);
    }

    private static void assertAllocations(IItemCollection allocations, Class<?> clazz, MemLeakTarget... targets) {
        long allocated = 0;
        for (MemLeakTarget target : targets) {
            allocated += target.getAllocated(clazz);
        }
        IItemCollection allocationsByType = allocations.apply(allocatedTypeFilter(clazz.getCanonicalName()));
        assertTrue(allocationsByType.hasItems());
        long recorded = allocationsByType.getAggregate(Aggregators.sum(SCALED_SIZE)).longValue();
        long absoluteError = Math.abs(recorded - allocated);
        assertTrue(absoluteError < allocated / 10,
                String.format("allocation samples should be within 10pct tolerance of allocated memory (recorded %d, allocated %d)",
                        recorded, allocated));
    }

    public static class MemLeakTarget extends ClassValue<AtomicLong> implements Runnable {
        private static byte[] leeway = new byte[32 * 1024 * 1024]; // 32MB to release on OOME
        public static volatile List<Object> sink = new ArrayList<>();

        @Override
        public void run() {
            ThreadLocalRandom random = ThreadLocalRandom.current();
            try {
                for (int i = 0; i < 100_000; i++) {
                    allocate(random, random.nextInt(256));
                }
            } catch (OutOfMemoryError e) {
                leeway = null;
                System.gc();
            } finally {
                sink.clear();
            }
        }

        long getAllocated(Class<?> clazz) {
            return get(clazz).get();
        }

        private static void allocate(ThreadLocalRandom random, int depth) {
            if (depth > 0) {
                allocate(random, depth - 1);
                return;
            }

            Object obj;
            if (random.nextBoolean()) {
                obj = new int[random.nextInt(64, 192) * 1000];
            } else {
                obj = new Integer[random.nextInt(64, 192) * 1000];
            }

            if (random.nextInt(100) == 0 && sink.size() < 100_000) {
                sink.add(obj);
            }
            if (random.nextInt(10000) == 0) {
                System.gc();
            }
        }

        @Override
        protected AtomicLong computeValue(Class<?> type) {
            return new AtomicLong();
        }
    }
}
