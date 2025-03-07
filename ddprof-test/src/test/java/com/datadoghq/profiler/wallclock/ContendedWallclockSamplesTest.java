package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.context.ContextExecutor;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.time.Duration;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicLong;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeFalse;
import static org.junit.jupiter.api.Assumptions.assumeTrue;


public class ContendedWallclockSamplesTest extends CStackAwareAbstractProfilerTest {
    public ContendedWallclockSamplesTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms";
    }

    private ContextExecutor executor;

    @Override
    protected void before() {
        executor = new ContextExecutor(10, profiler);
        ExecutorService es = Executors.newCachedThreadPool();
    }

    @Override
    public void after() {
        executor.shutdownNow();
    }

    @RetryTest(10)
    @TestTemplate
    @ValueSource(strings = {"fp", "dwarf", "vm", "vmx"})
    public void test(@CStack String cstack) {
        assumeFalse(Platform.isZing() || Platform.isJ9());
        // on aarch64 and JDK 8 the vmstructs unwinding for wallclock is extremely unreliable
        //   ; perhaps due to something missing in the unwinder but until we figure it out we will just not run the tests in CI
        assumeTrue(!isInCI() || !Platform.isAarch64() || !cstack.startsWith("vm") || Platform.isJavaVersionAtLeast(11));
        // TODO: investigate why this test fails on musl
        // on musl the missing fp unwinding makes the wallclock tests unreliable
//        assumeTrue(!Platform.isMusl() || !cstack.startsWith("vm"));

        long result = 0;
        for (int i = 0; i < 10; i++) {
            result += pingPong();
        }
        assertTrue(result != 0);
        stopProfiler();

        verifyCStackSettings();

        String lambdaName = getClass().getName() + LAMBDA_QUALIFIER;
        String lambdaStateName = getClass().getName() + ".lambda$pingPong$";
        for (IItemIterable wallclockSamples : verifyEvents("datadog.MethodSample")) {
            IMemberAccessor<String, IItem> frameAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(wallclockSamples.getType());
            IMemberAccessor<String, IItem> stateAccessor = THREAD_STATE.getAccessor(wallclockSamples.getType());
            for (IItem sample : wallclockSamples) {
                String state = stateAccessor.getMember(sample);
                if ("CONTENDED".equals(state)) {
                    String stackTrace = frameAccessor.getMember(sample);
                    if (!stackTrace.endsWith(".GC_active()")) {
                        assertTrue(stackTrace.contains(lambdaStateName), () -> stackTrace + " missing " + lambdaStateName);
                        assertTrue(stackTrace.contains(lambdaName), () -> stackTrace + " missing " + lambdaName);
                    }
                }
            }
        }
    }


    private long pingPong() {
        Object monitor = new Object();
        AtomicLong counter = new AtomicLong();
        long startTime = System.currentTimeMillis();
        List<CompletableFuture<Void>> futures = new ArrayList<>();
        for (int i = 0; i < 2; i++) {
            futures.add(CompletableFuture.supplyAsync(() -> {
                        while (System.currentTimeMillis() - startTime < 500) {
                            synchronized (monitor) {
                                counter.addAndGet(busyWork(Duration.ofMillis(100)));
                            }
                            counter.addAndGet(busyWork(Duration.ofMillis(10)));
                        }
                        return null;
                    },
                    executor));
        }

        CompletableFuture.allOf(futures.toArray(new CompletableFuture[0])).join();
        return counter.get();
    }

    private static long busyWork(Duration duration) {
        long startTime = System.nanoTime();
        long counter = ThreadLocalRandom.current().nextLong();
        while (System.nanoTime() - startTime < duration.toNanos()) {
            counter ^= ThreadLocalRandom.current().nextLong();
        }
        return counter;
    }
}
