package com.datadoghq.profiler.filter;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class TestFalseSharing extends AbstractProfilerTest {
    private static ExecutorService threadPool;

    @BeforeAll
    static void setupAll() {
        threadPool = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
    }

    @Test
    void testFalseSharing() {
        for (int i = 0; i < 512; i++) {
            threadPool.submit(() -> {
                for (int x = 0; x < 10000000; x++) {
                    profiler.addThread();
//                    double acc = 0;
//                    for (int j = 0; j < 100; j++) {
//                        // Simulate some work
//                        acc += Math.sin(j);
//                    }
                    profiler.removeThread();
                }
            });
        }

        // Wait for all tasks to complete
        threadPool.shutdown();
        while (!threadPool.isTerminated()) {
            // Wait for termination
        }

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.ExecutionSample");
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms";
    }
}
