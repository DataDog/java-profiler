package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.openjdk.jmc.common.item.IItemCollection;

import java.util.Map;

public class JvmtiBasedMonitorTaskBlockTest extends MonitorTaskBlockTest {
    @Override
    protected void before() throws Exception {
        Map<String, Long> counters = profiler.getDebugCounters();
        Assumptions.assumeTrue(
                counters.getOrDefault("jvmti_stacks_init_ok", 0L) > 0,
                "HotSpot RequestStackTrace JVMTI extension is not available");
    }

    @Override
    protected boolean isPlatformSupported() {
        return !Platform.isJ9() && !Platform.isZing();
    }

    @Override
    protected void withTestAssumptions() {
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true,jvmtistacks=true";
    }

    @Override
    protected void assertTaskBlockStackReference(IItemCollection taskBlockEvents) {
        TaskBlockAssertions.assertContainsCorrelationId(taskBlockEvents);
    }
}
