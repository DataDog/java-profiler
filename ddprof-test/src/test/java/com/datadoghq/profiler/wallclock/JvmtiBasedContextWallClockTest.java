package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;

import java.util.concurrent.ExecutionException;

public class JvmtiBasedContextWallClockTest extends AbstractProfilerTest {
    private final BaseContextWallClockTest base = new BaseContextWallClockTest(() -> profiler);

    @Override
    protected void before() {
        base.before();
    }

    @Override
    protected void after() throws InterruptedException {
        base.after();
    }

    @RetryingTest(5)
    public void test() throws ExecutionException, InterruptedException {
        // thread local handshake available only since Java 15
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(15));
        // do not assert context because of sampling skid
        base.test(this, false);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms,loglevel=warn,wallsampler=jvmti";
    }
}