package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.context.ContextExecutor;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
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
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicLong;

import static org.junit.jupiter.api.Assertions.assertTrue;


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
    }

    @Override
    public void after() {
        executor.shutdownNow();
    }

    @RetryTest(10)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    public void test(@CStack String cstack) {
        // Skip test entirely on unsupported JVMs (don't use assumeFalse which gets retried)
        if (Platform.isZing() || Platform.isJ9() ||
            (isInCI() && isAsan() && Platform.isGraal() && Platform.isAarch64() &&
             ("vm".equals(cstack) || "vmx".equals(cstack)))) {
            return;
        }

        // Running vm stackwalker tests on JVMCI (Graal), JDK 24, aarch64 and with a sanitizer is crashing in a weird place
        // This looks like the sanitizer instrumentation is breaking the longjump based crash recovery :(
        String config = System.getProperty("ddprof_test.config");
        boolean isJvmci = System.getProperty("java.vm.version", "").contains("jvmci");
        boolean isSanitizer = config.endsWith("san");
        if (Platform.isJavaVersionAtLeast(24) && isJvmci && Platform.isAarch64() && cstack.startsWith("vm") && isSanitizer) {
            return;
        }

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
                        // shortcut the assertions for sanitized runs
                        // the samples are not that good, but it still makes sense to run this load under sanitizers
                        assertTrue(isSanitizer || stackTrace.contains(lambdaStateName), () -> stackTrace + " missing " + lambdaStateName);
                        assertTrue(isSanitizer || stackTrace.contains(lambdaName), () -> stackTrace + " missing " + lambdaName);
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
