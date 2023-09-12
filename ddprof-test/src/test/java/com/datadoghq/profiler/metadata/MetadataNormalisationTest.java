package com.datadoghq.profiler.metadata;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.assertFalse;

public class MetadataNormalisationTest extends AbstractProfilerTest {

    @Test
    public void test() throws Exception {
        Constructor<?> arrayListConstructor = ArrayList.class.getConstructor();
        Method arrayListAdd = ArrayList.class.getDeclaredMethod("add", Object.class);
        Constructor<?> linkedListConstructor = LinkedList.class.getConstructor();
        Method linkedListAdd = LinkedList.class.getDeclaredMethod("add", Object.class);
        // need to invoke enough times to result in generation of accessors and to record some cpu time
        int count = 0;
        for (int i = 0; i < 100_000; i++) {
            Object list = arrayListConstructor.newInstance();
            arrayListAdd.invoke(list, "element");
            count += ((List<?>) list).size();
        }
        for (int i = 0; i < 100_000; i++) {
            Object list = linkedListConstructor.newInstance();
            linkedListAdd.invoke(list, "element");
            count += ((List<?>) list).size();
        }
        System.out.println(count);
        stopProfiler();
        IItemCollection executionSamples = verifyEvents("datadog.ExecutionSample");
        Matcher[] forbiddenPatternMatchers = Stream.of(
                "MH.*0x[A-Fa-f0-9]{3}", // method handles
                        "GeneratedConstructorAccessor\\d+",
                        "GeneratedMethodAccessor\\d+"
                )
                .map(regex -> Pattern.compile(regex).matcher(""))
                .toArray(Matcher[]::new);
        for (IItemIterable samples : executionSamples) {
            IMemberAccessor<String, IItem> stacktraceAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(samples.getType());
            for (IItem item : samples) {
                String stacktrace = stacktraceAccessor.getMember(item);
                for (Matcher matcher : forbiddenPatternMatchers) {
                    matcher.reset(stacktrace);
                    assertFalse(matcher.find(), () -> matcher.pattern() + "\n" + stacktrace);
                }
            }
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=1us";
    }
}
