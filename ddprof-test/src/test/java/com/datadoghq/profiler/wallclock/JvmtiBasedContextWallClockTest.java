package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
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
        base.test(this);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms,filter=0,loglevel=warn;wallsampler=jvmti";
    }
}