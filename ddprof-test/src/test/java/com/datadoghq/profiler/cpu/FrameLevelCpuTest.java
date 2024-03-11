package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.*;
import org.openjdk.jmc.common.unit.ContentType;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.*;
import java.util.concurrent.ExecutionException;

import static com.datadoghq.profiler.MoreAssertions.assertInRange;
import static org.junit.jupiter.api.Assertions.*;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.NUMBER;

public class FrameLevelCpuTest extends AbstractProfilerTest {

    private static final IAttribute<IQuantity> METHOD_ID = attr("methodId", "", "", NUMBER);
    private static final IAttribute<IQuantity> COMPILATION_TIER = attr("compilationTier", "", "", NUMBER);
    private static final IAttribute<IQuantity> PC_RELATIVE = attr("pcRelative", "", "", NUMBER);

    private ProfiledCode profiledCode;

    @Override
    protected void before() {
        profiledCode = new ProfiledCode(profiler);
    }

    @RetryingTest(10)
    public void test() throws ExecutionException, InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        for (int i = 0, id = 1; i < 100; i++, id += 3) {
            profiledCode.method1(id);
        }
        stopProfiler();
        IItemCollection frameSamples = verifyEvents("datadog.FrameSample");
        IItemCollection codeSamples = verifyEvents("datadog.CodeSample");

        Map<Long, List<IItem>> codeSamplesByMethodId = new HashMap<>();
        for (IItemIterable it : codeSamples) {
            IMemberAccessor<IQuantity, IItem> methodIdAccessor = METHOD_ID.getAccessor(it.getType());
            for (IItem codeSample : it) {
                long methodId = methodIdAccessor.getMember(codeSample).longValue();
                codeSamplesByMethodId.computeIfAbsent(methodId, mi -> new ArrayList<>())
                        .add(codeSample);
            }
        }
        for (IItemIterable it : frameSamples) {
            IMemberAccessor<IQuantity, IItem> methodIdAccessor = METHOD_ID.getAccessor(it.getType());
            IMemberAccessor<IQuantity, IItem> tierAccessor = COMPILATION_TIER.getAccessor(it.getType());
            IMemberAccessor<IQuantity, IItem> pcRelativeAccessor = PC_RELATIVE.getAccessor(it.getType());
            for (IItem frameSample : it) {
                long methodId = methodIdAccessor.getMember(frameSample).longValue();
                // check we don't have frames without corresponding code samples
                assertTrue(codeSamplesByMethodId.containsKey(methodId));
                int tier = (int) tierAccessor.getMember(frameSample).longValue();
                assertTrue(tier > 0);
                long pcRelative = pcRelativeAccessor.getMember(frameSample).longValue();
                assertTrue(pcRelative >= 0);
                // TODO assert it belongs to the code blob too
            }
        }

    }



    @Override
    protected void after() throws Exception {
        profiledCode.close();
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms,frames=y";
    }
}
