/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.settings;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeFalse;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.J9AsgctGate;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.NativeBuildConfig;
import com.datadoghq.profiler.Platform;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/**
 * Checks the {@code j9AsgctDeadlockRisk} recording setting and the J9 sampler warnings against
 * {@link J9AsgctGate}, the Java mirror of the native rules, on whatever JVM runs the tests. Each
 * case forks a JVM because engine selection and its warnings happen once per {@code start()}.
 */
public class J9AsgctDeadlockRiskTest extends AbstractProcessProfilerTest {
  private static final String SETTING = "j9AsgctDeadlockRisk";
  private static final String DEADLOCK_WARNING = "AsyncGetCallTrace can deadlock";
  private static final String GATED_WARNING = "using the JVMTI sampler";
  private static final String JVMTI_SAMPLER = "-Ddd.profiling.ddprof.j9.sampler=jvmti";

  @BeforeEach
  void skipJ9OnMac() {
    // Matches JavaProfilerTest's J9 cases, which are crashy on macOS.
    assumeFalse(Platform.isMac() && Platform.isJ9());
  }

  @Test
  void defaultSamplers() throws Exception {
    boolean asgct = Platform.isJ9() && J9AsgctGate.asgctAllowed();
    String j9Choice = J9AsgctGate.asgctAllowed() ? "asgct" : "jvmti_gated";
    Run run = run(Collections.emptyList(), "cpu=10ms,wall=10ms");
    run.assertOutcome(
        asgct && J9AsgctGate.deadlockProne(), Platform.isJ9() && !J9AsgctGate.asgctAllowed());
    run.assertJ9Lines(j9Choice, j9Choice);
  }

  @Test
  void jvmtiSamplerRequested() throws Exception {
    Run run = run(jvmtiSamplerArgs(), "cpu=10ms,wall=10ms");
    run.assertOutcome(false, false);
    run.assertJ9Lines("jvmti_requested", "jvmti_requested");
  }

  @Test
  void jvmtiWallSamplerRequested() throws Exception {
    boolean cpuAsgct = Platform.isJ9() && J9AsgctGate.asgctAllowed();
    Run run = run(Collections.emptyList(), "cpu=10ms,wall=10ms,wallsampler=jvmti");
    run.assertOutcome(
        cpuAsgct && J9AsgctGate.deadlockProne(), Platform.isJ9() && !J9AsgctGate.asgctAllowed());
    run.assertJ9Lines(J9AsgctGate.asgctAllowed() ? "asgct" : "jvmti_gated", "jvmti_requested");
  }

  @Test
  void explicitCpuEventBypassesTheSamplerChoice() throws Exception {
    Run run = run(jvmtiSamplerArgs(), "event=itimer,interval=10ms");
    run.assertOutcome(Platform.isJ9() && J9AsgctGate.deadlockProne(), false);
    run.assertJ9Lines("asgct", "none");
  }

  private static List<String> jvmtiSamplerArgs() {
    List<String> args = new ArrayList<>();
    args.add(JVMTI_SAMPLER);
    if (Platform.isJ9()) {
      // Makes jmethodID access safe for the JVMTI sampler on J9 JDK 11+.
      args.add("-XX:+KeepJNIIDs");
    }
    return args;
  }

  private Run run(List<String> jvmArgs, String profilingArgs) throws Exception {
    Path rootDir = Paths.get("/tmp/recordings");
    Files.createDirectories(rootDir);
    Path jfr = Files.createTempFile(rootDir, "j9-asgct-risk", ".jfr");
    Run run = new Run();
    try {
      LaunchResult result =
          launch(
              "profiler-sequence",
              jvmArgs,
              "start," + profilingArgs + ",jfr,file=" + jfr.toAbsolutePath() + ";STOP",
              line -> {
                run.addStdout(line);
                return LineConsumerResult.CONTINUE;
              },
              line -> {
                run.addStderr(line);
                return LineConsumerResult.CONTINUE;
              });
      assertTrue(result.inTime, "forked JVM did not exit in time");
      assertEquals(0, result.exitCode, "forked JVM exited with a non-zero code");
      for (JfrEvent setting : JfrEvents.load(jfr, "jdk.ActiveSetting")) {
        if (SETTING.equals(setting.getString("name"))) {
          run.setting = setting.getString("value");
        }
      }
    } finally {
      Files.deleteIfExists(jfr);
    }
    return run;
  }

  private static final class Run {
    private final List<String> stdout = Collections.synchronizedList(new ArrayList<>());
    private final List<String> stderr = Collections.synchronizedList(new ArrayList<>());
    private String setting;

    void addStdout(String line) {
      stdout.add(line);
    }

    void addStderr(String line) {
      stderr.add(line);
    }

    void assertOutcome(boolean deadlockRisk, boolean gatedFallback) {
      assertNotNull(setting, SETTING + " setting not found in the recording");
      assertEquals(Boolean.toString(deadlockRisk), setting, SETTING);
      assertEquals(deadlockRisk, containsLine(stderr, DEADLOCK_WARNING), "deadlock warning");
      assertEquals(gatedFallback, containsLine(stderr, GATED_WARNING), "gated-fallback warning");
    }

    /** TEST_LOG emits the J9[choice] and J9[props] lines in -DDEBUG builds, and only on J9. */
    void assertJ9Lines(String cpu, String wall) {
      if (!NativeBuildConfig.isDebugInstrumented()) {
        return;
      }
      if (!Platform.isJ9()) {
        assertFalse(containsLine(stdout, "J9[choice]"), "J9[choice] logged off J9: " + stdout);
        assertFalse(containsLine(stdout, "J9[props]"), "J9[props] logged off J9: " + stdout);
        return;
      }
      assertTrue(
          containsLine(stdout, "J9[choice] cpu=" + cpu + " wall=" + wall),
          "expected J9[choice] cpu=" + cpu + " wall=" + wall + " in " + stdout);
      // Proves the native reads see the same values the Java oracle classified.
      String props =
          "J9[props] vm="
              + System.getProperty("java.vm.version")
              + " runtime="
              + System.getProperty("java.runtime.version");
      assertTrue(containsLine(stdout, props), "expected " + props + " in " + stdout);
    }

    private static boolean containsLine(List<String> lines, String text) {
      synchronized (lines) {
        for (String line : lines) {
          if (line.contains(text)) {
            return true;
          }
        }
      }
      return false;
    }
  }
}
