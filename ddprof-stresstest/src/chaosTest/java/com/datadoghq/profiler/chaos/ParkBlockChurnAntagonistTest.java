/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.chaos;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.JavaProfiler;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.URL;
import java.net.URLClassLoader;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.time.Duration;
import javax.tools.ToolProvider;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.api.io.TempDir;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

/** Runs the real chaos workload against native recordings without tracer instrumentation. */
@Timeout(15)
class ParkBlockChurnAntagonistTest {
  private JavaProfiler profiler;
  private Path recording;
  private boolean started;

  @BeforeEach
  void setUp() throws Exception {
    Assumptions.assumeFalse(
        System.getProperty("java.vm.name", "").contains("J9"),
        "Unfiltered owned-block prechecks are unsupported by the J9 wall engine");
    profiler = JavaProfiler.getInstance();
    recording = Files.createTempFile("chaos-owned-block-", ".jfr");
  }

  @AfterEach
  void tearDown() throws Exception {
    try {
      if (started) profiler.stop();
    } finally {
      if (recording != null) Files.deleteIfExists(recording);
    }
  }

  /** The native hooks and timer must provide coverage without any Java agent attached. */
  @Test
  void explicitHooksExerciseUnfilteredPrechecks() throws Exception {
    ParkBlockChurnAntagonist workload = runWorkload("wall=1ms,filter=,wallprecheck=true");
    workload.verifyPrecheckCoverage();
  }

  /** A rejected nested park must not close the caller's existing owned interval. */
  @Test
  void nestedParkDoesNotCloseOuterOwnedRun() throws Exception {
    ParkBlockChurnAntagonist workload = runWorkload("wall=1ms,filter=,wallprecheck=true");
    Method enter = JavaProfiler.class.getDeclaredMethod("parkEnter");
    Method exit = JavaProfiler.class.getDeclaredMethod("parkExit", long.class, long.class);
    Method block = ParkBlockChurnAntagonist.class.getDeclaredMethod("block", int.class);
    enter.setAccessible(true);
    exit.setAccessible(true);
    block.setAccessible(true);
    assertTrue((boolean) enter.invoke(profiler), "The test must own the outer park");
    try {
      block.invoke(workload, 1);
      assertFalse((boolean) enter.invoke(profiler), "The outer park must still be owned");
    } finally {
      exit.invoke(profiler, 0L, 0L);
    }
  }

  /** The application loader cannot link profiler classes stored in the agent's private loader. */
  @Test
  void privateAgentLoaderSuppliesHooksAndCounters(@TempDir Path directory) throws Exception {
    try (URLClassLoader loader = isolatedAgentLoader(directory, true)) {
      assertThrows(
          ClassNotFoundException.class,
          () -> loader.loadClass("com.datadoghq.profiler.JavaProfiler"));
      profiler.execute("start,wall=1ms,filter=,wallprecheck=true,jfr,file=" + recording);
      started = true;
      Class<?> type = loader.loadClass(ParkBlockChurnAntagonist.class.getName());
      Object workload = type.getConstructor(int.class, int.class).newInstance(12, 20);
      type.getMethod("start").invoke(workload);
      try {
        Thread.sleep(1000);
      } finally {
        type.getMethod("stopGracefully", Duration.class).invoke(workload, Duration.ofSeconds(5));
      }
      type.getMethod("verifyPrecheckCoverage").invoke(workload);
    }
  }

  /** An uninitialized agent must fail before launching any workers. */
  @Test
  void unavailableAgentLoaderFailsStartup(@TempDir Path directory) throws Exception {
    try (URLClassLoader loader = isolatedAgentLoader(directory, false)) {
      Class<?> type = loader.loadClass(ParkBlockChurnAntagonist.class.getName());
      Object workload = type.getConstructor().newInstance();
      InvocationTargetException failure =
          assertThrows(
              InvocationTargetException.class, () -> type.getMethod("start").invoke(workload));
      assertTrue(failure.getCause() instanceof IllegalStateException, failure.toString());
      assertTrue(
          failure.getCause().getCause() instanceof ClassNotFoundException, failure.toString());
    }
  }

  /** Models shared classdata visibility without putting JavaProfiler on the application path. */
  private URLClassLoader isolatedAgentLoader(Path directory, boolean initialized) throws Exception {
    Path source = directory.resolve("datadog/trace/bootstrap/Agent.java");
    Files.createDirectories(source.getParent());
    Files.write(
        source,
        ("package datadog.trace.bootstrap; public class Agent {"
                + "private static ClassLoader AGENT_CLASSLOADER; }")
            .getBytes(StandardCharsets.UTF_8));
    int result = ToolProvider.getSystemJavaCompiler().run(null, null, null, source.toString());
    org.junit.jupiter.api.Assertions.assertEquals(0, result, "Agent loader fixture compilation");
    URLClassLoader loader =
        new URLClassLoader(new URL[] {directory.toUri().toURL()}, getClass().getClassLoader()) {
          @Override
          protected Class<?> loadClass(String name, boolean resolve) throws ClassNotFoundException {
            if (name.equals("com.datadoghq.profiler.JavaProfiler")) {
              throw new ClassNotFoundException(name);
            }
            if (name.equals(ParkBlockChurnAntagonist.class.getName())
                || name.equals(Antagonist.class.getName())) {
              Class<?> type = findLoadedClass(name);
              if (type == null) {
                String resource = name.replace('.', '/') + ".class";
                try (InputStream input = getParent().getResourceAsStream(resource)) {
                  if (input == null) throw new ClassNotFoundException(name);
                  ByteArrayOutputStream output = new ByteArrayOutputStream();
                  byte[] buffer = new byte[4096];
                  for (int count; (count = input.read(buffer)) != -1; ) {
                    output.write(buffer, 0, count);
                  }
                  byte[] bytes = output.toByteArray();
                  type = defineClass(name, bytes, 0, bytes.length);
                } catch (IOException e) {
                  throw new ClassNotFoundException(name, e);
                }
              }
              if (resolve) resolveClass(type);
              return type;
            }
            return super.loadClass(name, resolve);
          }
        };
    if (initialized) {
      java.lang.reflect.Field field =
          loader.loadClass("datadog.trace.bootstrap.Agent").getDeclaredField("AGENT_CLASSLOADER");
      field.setAccessible(true);
      field.set(null, JavaProfiler.class.getClassLoader());
    }
    return loader;
  }

  /** Calling hooks alone must not make disabled suppression appear to be covered. */
  @ParameterizedTest
  @ValueSource(
      strings = {"wall=1ms,filter=,wallprecheck=false", "wall=1ms,filter=0,wallprecheck=false"})
  void disabledPrechecksCannotPassCoverage(String command) throws Exception {
    ParkBlockChurnAntagonist workload = runWorkload(command);
    IllegalStateException failure =
        assertThrows(IllegalStateException.class, workload::verifyPrecheckCoverage);
    if (command.contains("filter=0")) {
      // Context-filtered recordings arm the hooks even with prechecks off.
      // Require rejection on the missing timer activity, beyond hook invocation.
      assertTrue(
          failure.getMessage().contains("wc_precheck_registry_lookups"), failure.getMessage());
    }
  }

  /** Creates repeated real thread lifecycles while sampling, and joins them before returning. */
  private ParkBlockChurnAntagonist runWorkload(String command) throws Exception {
    profiler.execute("start," + command + ",jfr,file=" + recording.toAbsolutePath());
    started = true;
    ParkBlockChurnAntagonist workload = new ParkBlockChurnAntagonist(12, 20);
    workload.start();
    try {
      Thread.sleep(1000);
    } finally {
      workload.stopGracefully(Duration.ofSeconds(5));
    }
    return workload;
  }
}
