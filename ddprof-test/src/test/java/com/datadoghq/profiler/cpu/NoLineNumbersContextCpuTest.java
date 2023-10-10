package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.Map;
import java.util.Set;
import java.util.concurrent.ExecutionException;

import static com.datadoghq.profiler.MoreAssertions.assertInRange;
import static org.junit.jupiter.api.Assertions.*;

public class NoLineNumbersContextCpuTest extends ContextCpuTest {


    @Override
    protected String getProfilerCommand() {
        return "cpu=1us,linenumbers=false";
    }
}
