/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import java.lang.instrument.Instrumentation;

/**
 * Agent loaded into the test JVM by self-attach (see {@link LazyRedefinitionStressTest}); it only
 * hands out the {@link Instrumentation} instance.
 */
public final class RetransformAgent {
    /** Set by {@link #agentmain} once the agent has been loaded. */
    public static volatile Instrumentation instrumentation;

    private RetransformAgent() {}

    /**
     * Agent entry point for dynamic loading.
     *
     * @param args ignored
     * @param inst the instrumentation instance of this JVM
     */
    public static void agentmain(String args, Instrumentation inst) {
        instrumentation = inst;
    }
}
