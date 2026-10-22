/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.chaos;

import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

/** Binds calls to the agent's profiler without loading another copy on the application classpath. */
final class ProfilerAccess {
    private ProfilerAccess() {}

    /** Uses the agent's isolated loader when attached, or the test classpath in standalone runs. */
    static Object getInstance() throws ReflectiveOperationException {
        ClassLoader loader = ProfilerAccess.class.getClassLoader();
        Class<?> agent;
        try {
            agent = Class.forName("datadog.trace.bootstrap.Agent", false, loader);
        } catch (ClassNotFoundException standalone) {
            return Class.forName("com.datadoghq.profiler.JavaProfiler", true, loader)
                    .getMethod("getInstance").invoke(null);
        }

        // Agent stores shared/*.classdata behind this loader; adding ddprof.jar to the
        // application classpath would create a separate JavaProfiler singleton instead.
        Field field = agent.getDeclaredField("AGENT_CLASSLOADER");
        field.setAccessible(true);
        ClassLoader agentLoader = (ClassLoader) field.get(null);
        if (agentLoader == null) {
            throw new IllegalStateException("Datadog agent class loader is not initialized");
        }
        return Class.forName("com.datadoghq.profiler.JavaProfiler", true, agentLoader)
                .getMethod("getInstance").invoke(null);
    }

    /** Resolves a hook once, retaining its exact signature and avoiding reflective call allocations. */
    static MethodHandle bind(Object profiler, String name, Class<?>... parameterTypes)
            throws ReflectiveOperationException {
        Method method = profiler.getClass().getDeclaredMethod(name, parameterTypes);
        method.setAccessible(true);
        return MethodHandles.lookup().unreflect(method).bindTo(profiler);
    }
}
