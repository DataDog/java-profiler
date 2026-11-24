/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

import java.nio.file.Paths;
import jdk.jfr.Event;
import jdk.jfr.Name;
import jdk.jfr.Recording;

/**
 * Test-only helper for evaluate_test.sh: writes a recording with two {@code datadog.ProfilerCounter}
 * events for {@code native_mem_live_bytes} (100, then 200), the event the profiler emits.
 *
 * <p>Usage: {@code java CounterJfr.java <out.jfr>}
 */
public class CounterJfr {

    @Name("datadog.ProfilerCounter")
    static class Counter extends Event {
        String name;
        long count;
    }

    public static void main(String[] args) throws Exception {
        try (Recording recording = new Recording()) {
            recording.enable(Counter.class);
            recording.start();
            for (long count : new long[] {100, 200}) {
                Counter c = new Counter();
                c.name = "native_mem_live_bytes";
                c.count = count;
                c.commit();
            }
            recording.stop();
            recording.dump(Paths.get(args[0]));
        }
    }
}
