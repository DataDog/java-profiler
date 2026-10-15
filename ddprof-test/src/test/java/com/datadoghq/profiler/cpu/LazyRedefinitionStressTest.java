/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.SpinClasses;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.io.IOException;
import java.io.OutputStream;
import java.lang.instrument.ClassDefinition;
import java.lang.instrument.Instrumentation;
import java.lang.management.ManagementFactory;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Map;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;
import java.util.jar.Attributes;
import java.util.jar.JarOutputStream;
import java.util.jar.Manifest;

import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Redefines a class over and over in a live JVM while {@code fjmethodid=lazy} samples it and the
 * profiler dumps concurrently.
 *
 * <p>Each {@code Instrumentation.redefineClasses()} call with the class's own bytes is a full
 * HotSpot redefinition: the class gets a new methods array and new {@code Method*}s, and the old
 * ones are freed once they are off every stack, so their memory can be reused by the next
 * redefinition of the same class. Raw frames sampled before a redefinition must be refused
 * ({@code method_resolve_lazy_redefined}) rather than read through freed metadata or resolved to
 * a reused address; frames sampled after it carry the jmethodIDs the redefinition hook preloads
 * and resolve normally.
 */
public class LazyRedefinitionStressTest extends AbstractProfilerTest {
    private static final String CLASS_NAME = "com/datadoghq/profiler/generated/LazyRedefinitionProbe";
    private static final long DURATION_NANOS = 5_000_000_000L;

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms,cstack=vm,fjmethodid=lazy";
    }

    @Test
    @Timeout(120)
    public void concurrentRedefinitionDoesNotCrashOrMisresolve() throws Exception {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9() || Platform.isGraal(), "HotSpot only");
        Instrumentation inst = loadAgent();
        Assumptions.assumeTrue(inst != null && inst.isRedefineClassesSupported(), "class redefinition not available");
        waitForProfilerReady(2000);

        Class<?> probe = SpinClasses.define(CLASS_NAME);
        byte[] bytes = SpinClasses.bytes(CLASS_NAME);
        Method spin = probe.getMethod("spin", long.class);
        AtomicBoolean done = new AtomicBoolean(false);
        AtomicReference<Throwable> failure = new AtomicReference<>();
        AtomicInteger redefinitions = new AtomicInteger();

        Thread spinner = new Thread(() -> {
            try {
                while (!done.get()) {
                    spin.invoke(null, 1_000_000L);
                }
            } catch (Throwable t) {
                failure.compareAndSet(null, t);
            }
        }, "lazy-redefinition-spinner");
        Thread redefiner = new Thread(() -> {
            try {
                while (!done.get()) {
                    inst.redefineClasses(new ClassDefinition(probe, bytes));
                    redefinitions.incrementAndGet();
                    Thread.sleep(2);
                }
            } catch (Throwable t) {
                failure.compareAndSet(null, t);
            }
        }, "lazy-redefinition-redefiner");
        spinner.start();
        // Let raw frames of the class pile up first, with no dump in between, so
        // that the first dumps after redefinitions start have stale raw frames of
        // a marked class to refuse.
        Thread.sleep(300);
        redefiner.start();

        Path dir = Paths.get(System.getProperty("java.io.tmpdir"), "recordings");
        Files.createDirectories(dir);
        Path dumpFile = Files.createTempFile(dir, "lazy-redefinition-", ".jfr");
        int dumps = 0;
        try {
            long deadline = System.nanoTime() + DURATION_NANOS;
            while (System.nanoTime() < deadline) {
                // Each dump resolves the raw frames collected since the previous one,
                // racing with the redefinitions.
                profiler.dump(dumpFile);
                dumps++;
                Thread.sleep(100);
            }
        } finally {
            done.set(true);
            spinner.join();
            redefiner.join();
        }
        assertNull(failure.get(), "workload thread failed: " + failure.get());

        // Samples taken after the last redefinitions carry jmethodIDs and resolve by name.
        Thread.sleep(50);
        Thread tail = new Thread(() -> {
            try {
                spin.invoke(null, 500_000_000L);
            } catch (Throwable t) {
                failure.compareAndSet(null, t);
            }
        });
        tail.start();
        tail.join();
        stopProfiler();

        Map<String, Long> counters = profiler.getDebugCounters();
        System.out.println("redefinitions=" + redefinitions.get() + " dumps=" + dumps
                + " klass_registry_redefinitions_marked=" + counters.get("klass_registry_redefinitions_marked")
                + " method_resolve_lazy_redefined=" + counters.get("method_resolve_lazy_redefined")
                + " method_resolve_lazy_not_current=" + counters.get("method_resolve_lazy_not_current")
                + " method_resolve_fault_recovered=" + counters.get("method_resolve_fault_recovered"));
        assertTrue(redefinitions.get() > 100, "too few redefinitions to stress anything: " + redefinitions.get());
        Long marked = counters.get("klass_registry_redefinitions_marked");
        Long refused = counters.get("method_resolve_lazy_redefined");
        if (marked != null) {
            // Absent in builds without counters; when present, both paths must have run.
            assertTrue(marked > 0, "the redefinition hooks never marked the class");
            assertTrue(refused != null && refused > 0, "no raw frame of the redefined class was refused");
        }

        String simpleName = CLASS_NAME.substring(CLASS_NAME.lastIndexOf('/') + 1);
        boolean resolved = false;
        for (JfrEvent sample : verifyEvents("datadog.ExecutionSample")) {
            String stackTrace = sample.getStackTraceString();
            if (stackTrace != null && stackTrace.contains(simpleName) && stackTrace.contains("spin")) {
                resolved = true;
                break;
            }
        }
        assertTrue(resolved, "frames of the redefined class sampled after the redefinitions did not resolve");
        try { Files.deleteIfExists(dumpFile); } catch (IOException ignored) {}
    }

    /**
     * Loads {@link RetransformAgent} into this JVM through the attach API (by reflection: it lives
     * in jdk.attach, or tools.jar on JDK 8, neither of which the test sources compile against) and
     * returns its {@link Instrumentation}, or null if self-attach is unavailable.
     */
    private static Instrumentation loadAgent() throws Exception {
        if (RetransformAgent.instrumentation != null) {
            return RetransformAgent.instrumentation;
        }
        Class<?> vmClass;
        try {
            vmClass = Class.forName("com.sun.tools.attach.VirtualMachine");
        } catch (ClassNotFoundException e) {
            return null;
        }
        Path jar = Files.createTempFile("lazy-redefinition-agent-", ".jar");
        Manifest manifest = new Manifest();
        Attributes attributes = manifest.getMainAttributes();
        attributes.put(Attributes.Name.MANIFEST_VERSION, "1.0");
        attributes.putValue("Agent-Class", RetransformAgent.class.getName());
        attributes.putValue("Can-Redefine-Classes", "true");
        attributes.putValue("Can-Retransform-Classes", "true");
        try (OutputStream out = Files.newOutputStream(jar); JarOutputStream ignored = new JarOutputStream(out, manifest)) {
            // Manifest only: the agent class is loaded from the test classpath.
        }
        String pid = ManagementFactory.getRuntimeMXBean().getName().split("@")[0];
        Object vm = vmClass.getMethod("attach", String.class).invoke(null, pid);
        try {
            vmClass.getMethod("loadAgent", String.class).invoke(vm, jar.toString());
        } finally {
            vmClass.getMethod("detach").invoke(vm);
            Files.deleteIfExists(jar);
        }
        return RetransformAgent.instrumentation;
    }
}
