package com.datadoghq.profiler.wallclock;

import java.util.concurrent.ExecutionException;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;

public class ContextWallClockTest extends CStackAwareAbstractProfilerTest {
    private final BaseContextWallClockTest base = new BaseContextWallClockTest(() -> profiler);

    public ContextWallClockTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected void before() {
        base.before();
    }

    @Override
    protected void after() throws InterruptedException {
        base.after();
    }

    @RetryTest(5)
    @TestTemplate
    @ValueSource(strings = {"fp", "dwarf", "vm", "vmx"})
    public void test(@CStack String cstack) throws ExecutionException, InterruptedException {
        base.test(this);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms,filter=0,loglevel=warn";
    }
}
