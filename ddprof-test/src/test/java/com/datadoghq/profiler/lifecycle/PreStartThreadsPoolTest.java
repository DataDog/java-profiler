/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.lifecycle;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.Platform;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

import java.nio.file.Path;
import java.util.Collections;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * The TLS pool is sized at the first start from the number of live threads. Threads that already
 * exist then have no ProfiledThread (the pthread_create hook isn't installed yet), so each takes a
 * pool slot on its first signal. With far more of them than the old fixed 64 slots, none of their
 * samples may be dropped for lack of a slot.
 */
public class PreStartThreadsPoolTest extends AbstractProcessProfilerTest {

    private static final int THREADS = 300;

    @Test
    void poolIsSizedForThreadsThatPredateTheFirstStart(@TempDir Path tmp) throws Exception {
        assumeTrue(Platform.isLinux() && !Platform.isJ9() && !Platform.isZing());

        AtomicReference<String> exhausted = new AtomicReference<>();
        LaunchResult result = launch("pre-start-threads:" + THREADS, Collections.emptyList(),
            "start,cpu=1ms,jfr,file=" + tmp.resolve("pre-start.jfr"),
            l -> {
                if (l.startsWith("[pool-exhausted] ")) {
                    exhausted.set(l.substring("[pool-exhausted] ".length()).trim());
                }
                return LineConsumerResult.CONTINUE;
            },
            null);

        assertTrue(result.inTime);
        assertNotNull(exhausted.get(), "the launcher did not report the pool counter");
        assertEquals("0", exhausted.get(), "samples dropped for lack of a TLS pool slot");
    }
}
