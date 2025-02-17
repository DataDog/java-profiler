package com.datadoghq.profiler;


import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.CStackInjector;
import org.junit.jupiter.api.extension.ExtendWith;

@ExtendWith(CStackInjector.class)
public abstract class CStackAwareAbstractProfilerTest extends AbstractProfilerTest {
    public CStackAwareAbstractProfilerTest(@CStack String cstack) {
        super(mapOf("cstack", cstack));
    }
}
