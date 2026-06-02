package com.datadoghq.profiler.llm;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.AgentPhase;
import com.datadoghq.profiler.ContextSetter;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;

import java.util.Arrays;
import java.util.concurrent.atomic.AtomicBoolean;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.PLAIN_TEXT;

public class AgentPhaseProfilingTest extends AbstractProfilerTest {

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms,attributes=" + AgentPhase.ATTRIBUTE_NAME;
    }

    private static final IAttribute<String> AGENT_PHASE = attr(
            AgentPhase.ATTRIBUTE_NAME, AgentPhase.ATTRIBUTE_NAME, AgentPhase.ATTRIBUTE_NAME, PLAIN_TEXT);

    @Test
    public void cpuSamplesCarryAgentPhase() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();

        ContextSetter cs = new ContextSetter(profiler,
                Arrays.asList(AgentPhase.ATTRIBUTE_NAME));
        int offset = cs.offsetOf(AgentPhase.ATTRIBUTE_NAME);
        assertTrue(offset >= 0, "llm.agent.phase must have a valid slot index");

        AtomicBoolean done = new AtomicBoolean(false);
        Thread worker = new Thread(() -> {
            cs.setContextValue(offset, AgentPhase.AWAITING_INFERENCE.token());
            long sum = 0;
            while (!done.get()) {
                sum += sum + 1;
            }
            cs.clearContextValue(offset);
        });
        worker.setDaemon(true);
        worker.start();
        Thread.sleep(300);
        done.set(true);
        worker.join();

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.ExecutionSample");
        boolean found = false;
        outer:
        for (IItemIterable iterable : events) {
            IMemberAccessor<String, IItem> phaseAccessor = AGENT_PHASE.getAccessor(iterable.getType());
            if (phaseAccessor == null) continue;
            for (IItem item : iterable) {
                String val = phaseAccessor.getMember(item);
                if (AgentPhase.AWAITING_INFERENCE.token().equals(val)) {
                    found = true;
                    break outer;
                }
            }
        }
        assertTrue(found, "Expected at least one ExecutionSample with "
                + AgentPhase.ATTRIBUTE_NAME + "=" + AgentPhase.AWAITING_INFERENCE.token()
                + " — if the test fails, check that the JMC accessor name '" + AgentPhase.ATTRIBUTE_NAME + "' "
                + "matches the field name emitted by the profiler (inspect the JFR: "
                + "jfr print --events datadog.ExecutionSample <recording.jfr>)");
    }
}
