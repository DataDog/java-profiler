/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrFrame;
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
import java.net.URL;
import java.net.URLClassLoader;
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
 * and resolve normally. A second thread retransforms the class meanwhile, which goes through the
 * profiler's RetransformClasses hook instead.
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
        Long traceIdOffset = profiler.getDebugCounters().get("klass_trace_id_offset");
        if (traceIdOffset != null) {
            // Absent in builds without counters. Without a trace ID offset the profiler preloads
            // jmethodIDs as in fjmethodid=false, and nothing here would exercise lazy mode.
            Assumptions.assumeTrue(Platform.hasJfr(), "JDK without JFR");
            assertTrue(traceIdOffset > 0, "lazy mode is not active: klass_trace_id_offset=" + traceIdOffset);
        }

        Class<?> probe = SpinClasses.define(CLASS_NAME);
        byte[] bytes = SpinClasses.bytes(CLASS_NAME);
        Method spin = probe.getMethod("spin", long.class);
        AtomicBoolean done = new AtomicBoolean(false);
        AtomicReference<Throwable> failure = new AtomicReference<>();
        AtomicInteger redefinitions = new AtomicInteger();
        AtomicInteger retransformations = new AtomicInteger();

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
        Thread retransformer = new Thread(() -> {
            try {
                while (!done.get()) {
                    inst.retransformClasses(probe);
                    retransformations.incrementAndGet();
                    Thread.sleep(5);
                }
            } catch (Throwable t) {
                failure.compareAndSet(null, t);
            }
        }, "lazy-redefinition-retransformer");
        spinner.start();
        // Let raw frames of the class pile up first, with no dump in between, so
        // that the first dumps after redefinitions start have stale raw frames of
        // a marked class to refuse.
        Thread.sleep(300);
        redefiner.start();
        if (inst.isRetransformClassesSupported()) {
            retransformer.start();
        }

        Path dir = Paths.get(System.getProperty("java.io.tmpdir"), "recordings");
        Files.createDirectories(dir);
        Path dumpFile = Files.createTempFile(dir, "lazy-redefinition-", ".jfr");
        try {
            runScenario(spin, dumpFile, done, failure, redefinitions, retransformations, spinner, redefiner,
                    retransformer);
        } finally {
            try { Files.deleteIfExists(dumpFile); } catch (IOException ignored) {}
        }
    }

    private void runScenario(Method spin, Path dumpFile, AtomicBoolean done, AtomicReference<Throwable> failure,
            AtomicInteger redefinitions, AtomicInteger retransformations, Thread spinner, Thread redefiner,
            Thread retransformer) throws Exception {
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
            retransformer.join();
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
        assertNull(failure.get(), "tail spin failed: " + failure.get());
        stopProfiler();

        Map<String, Long> counters = profiler.getDebugCounters();
        System.out.println("redefinitions=" + redefinitions.get() + " retransformations=" + retransformations.get()
                + " dumps=" + dumps
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

        // A frame resolved through a freed or reused Method* would decode some other method's
        // line number table, so every resolved spin frame must have one of spin's lines.
        String simpleName = CLASS_NAME.substring(CLASS_NAME.lastIndexOf('/') + 1);
        int spinFrames = 0;
        for (JfrEvent sample : verifyEvents("datadog.ExecutionSample")) {
            if (!sample.has("stackTrace")) {
                continue;
            }
            for (JfrFrame frame : sample.getStackTrace().frames()) {
                String frameClass = frame.className();
                if (frameClass != null && frameClass.endsWith(simpleName) && "spin".equals(frame.methodName())) {
                    spinFrames++;
                    assertTrue(SpinClasses.SPIN_LINES.contains(frame.lineNumber()),
                            "spin frame has line " + frame.lineNumber() + ", expected one of " + SpinClasses.SPIN_LINES);
                }
            }
        }
        assertTrue(spinFrames > 0, "frames of the redefined class sampled after the redefinitions did not resolve");
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
        Class<?> vmClass = attachApi();
        if (vmClass == null) {
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

    /**
     * Returns {@code com.sun.tools.attach.VirtualMachine}, or null if this JVM has no attach API.
     * On JDK 9+ it comes from the jdk.attach module. On JDK 8 it lives in the JDK's
     * {@code lib/tools.jar}, which isn't on the test classpath, so it is loaded from there with a
     * child class loader; {@code AttachProvider} finds its Linux/macOS provider through the
     * same loader.
     */
    private static Class<?> attachApi() throws Exception {
        try {
            return Class.forName("com.sun.tools.attach.VirtualMachine");
        } catch (ClassNotFoundException e) {
            // JDK 8: java.home is <jdk>/jre
            Path toolsJar = Paths.get(System.getProperty("java.home"), "..", "lib", "tools.jar").normalize();
            if (!Files.isRegularFile(toolsJar)) {
                return null;
            }
            ClassLoader loader = new URLClassLoader(new URL[] {toolsJar.toUri().toURL()},
                    LazyRedefinitionStressTest.class.getClassLoader());
            return Class.forName("com.sun.tools.attach.VirtualMachine", true, loader);
        }
    }
}
