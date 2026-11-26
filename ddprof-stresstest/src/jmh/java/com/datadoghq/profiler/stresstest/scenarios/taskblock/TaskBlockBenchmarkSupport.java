/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.stresstest.scenarios.taskblock;

import com.datadoghq.profiler.JavaProfiler;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Collections;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;
import org.openjdk.jmh.infra.BenchmarkParams;

/**
 * Shared setup, verification and reporting for the TaskBlock benchmarks.
 *
 * <p>Every benchmark takes a {@code config} parameter, mapped by {@link #command(String)}.
 * TaskBlock recording is on only for a wall engine with {@code wallprecheck=true} and an empty
 * {@code filter=}; that one switch enables the park, paired-API, JVMTI monitor and native I/O
 * producers, which have no separate knob.
 *
 * <p>{@code -Dddprof.bench.lib=/path/libjavaProfiler.so} loads that library instead of the bundled
 * debug ({@code -O0}) build, so overhead can be measured on a release build. {@code
 * -Dddprof.bench.wall=<interval>} changes the wall-clock interval (default {@code 10ms}).
 */
final class TaskBlockBenchmarkSupport {
  static final String NONE = "none";
  static final String EMITTED = "task_block_emitted";
  static final String TOO_SHORT = "task_block_skipped_too_short";
  static final String SKIPPED_TRACE_CONTEXT = "task_block_skipped_trace_context";
  static final String NATIVE_IO_HOOKS_PATCHED = "native_io_standard_hooks_patched";

  private static final String DEBUG_ONLY_COUNTER = "safefetch_while_protected";
  private static final String LIBRARY_PROPERTY = "ddprof.bench.lib";
  private static final String WALL_INTERVAL_PROPERTY = "ddprof.bench.wall";

  private TaskBlockBenchmarkSupport() {}

  /**
   * Maps a {@code config} parameter to a profiler command: {@code wall} is unfiltered wall-clock
   * without TaskBlock and {@code taskblock} adds {@code wallprecheck=true}. Any other value is used
   * as the command with {@code ;} for {@code ,}, because JMH's {@code -p} splits values on commas.
   */
  static String command(String config) {
    String wall = "wall=" + System.getProperty(WALL_INTERVAL_PROPERTY, "10ms") + ",filter=";
    switch (config) {
      case "wall":
        return wall;
      case "taskblock":
        return wall + ",wallprecheck=true";
      default:
        return config.replace(';', ',');
    }
  }

  /** Loads the profiler library, honouring {@code -Dddprof.bench.lib}. */
  static JavaProfiler loadProfiler() throws IOException {
    String library = System.getProperty(LIBRARY_PROPERTY);
    return library == null || library.isEmpty()
        ? JavaProfiler.getInstance()
        : JavaProfiler.getInstance(library, null);
  }

  static boolean isLinux() {
    return System.getProperty("os.name", "").toLowerCase(Locale.ROOT).startsWith("linux");
  }

  /**
   * Returns whether {@code command} requests TaskBlock recording, mirroring {@code
   * Arguments::parse} and {@code Profiler::start}: keys match case-insensitively and exactly, the
   * last occurrence wins, a bare {@code wall} enables wall-clock, a bare {@code filter} is empty
   * and a bare {@code wallprecheck} is true.
   */
  static boolean requestsTaskBlock(String command) {
    boolean wall = false;
    boolean precheck = false;
    boolean unfiltered = false;
    for (String option : command.split(",")) {
      int eq = option.indexOf('=');
      String key = eq < 0 ? option : option.substring(0, eq);
      String value = eq < 0 ? null : option.substring(eq + 1);
      if (key.equalsIgnoreCase("wall")) {
        wall = true;
      } else if (key.equalsIgnoreCase("wallprecheck")) {
        precheck = parseBool(value);
      } else if (key.equalsIgnoreCase("filter")) {
        unfiltered = value == null || value.isEmpty();
      }
    }
    return wall && precheck && unfiltered;
  }

  /** Mirrors {@code parseBoolOption}: no value is true; an unrecognised value is an error. */
  private static boolean parseBool(String value) {
    if (value == null) {
      return true;
    }
    switch (value) {
      case "y":
      case "yes":
      case "t":
      case "true":
      case "1":
        return true;
      case "n":
      case "no":
      case "f":
      case "false":
      case "0":
        return false;
      default:
        throw new IllegalArgumentException("Invalid wallprecheck value: " + value);
    }
  }

  /** Returns the benchmark method or group name of the running trial. */
  static String benchmarkName(BenchmarkParams params) {
    String benchmark = params.getBenchmark();
    return benchmark.substring(benchmark.lastIndexOf('.') + 1);
  }

  /**
   * Gives the calling helper thread a trace context, so its blocks are ineligible and counted in
   * {@link #SKIPPED_TRACE_CONTEXT} instead of {@link #EMITTED}. A no-op without a profiler.
   */
  static void excludeFromTaskBlock(JavaProfiler profiler) {
    if (profiler != null) {
      profiler.setTraceContext(1, 1, 0, 0, -1, null, -1, null);
    }
  }

  /** Fails unless {@code low <= value <= high}; the bounds are what attribute counts to workers. */
  static void checkBetween(String what, long value, long low, long high) {
    check(
        value >= low && value <= high, what + "=" + value + " outside [" + low + ", " + high + "]");
  }

  static void check(boolean condition, String message) {
    if (!condition) {
      throw new IllegalStateException(message);
    }
  }

  /** One trial's recording; {@link #stop} reports and returns the counter deltas. */
  static final class Recording {
    private final JavaProfiler profiler;
    private final String command;
    private final boolean taskBlockActive;
    private final Path file;
    private final Map<String, Long> before;
    private final long startNanos;

    private Recording(
        JavaProfiler profiler,
        String command,
        boolean taskBlockActive,
        Path file,
        Map<String, Long> before) {
      this.profiler = profiler;
      this.command = command;
      this.taskBlockActive = taskBlockActive;
      this.file = file;
      this.before = before;
      this.startNanos = System.nanoTime();
    }

    /**
     * Starts the recording {@code config} names and fails unless TaskBlock recording is active
     * exactly when its command requests it. Must run on a platform thread without a trace context:
     * the check is a {@code beginTaskBlock}/{@code endTaskBlock} probe, which returns 0 otherwise.
     *
     * @param profiler the loaded profiler, or {@code null} when {@code config} is {@link #NONE}
     */
    static Recording start(JavaProfiler profiler, String config) throws IOException {
      if (NONE.equals(config)) {
        Map<String, Long> counters =
            profiler != null ? profiler.getDebugCounters() : Collections.<String, Long>emptyMap();
        return new Recording(profiler, config, false, null, counters);
      }
      String command = command(config);
      Path file = Files.createTempFile("taskblock-bench-", ".jfr");
      boolean started = false;
      try {
        profiler.execute("start," + command + ",jfr,file=" + file.toAbsolutePath());
        started = true;
        long token = profiler.beginTaskBlock();
        if (token != 0) {
          profiler.endTaskBlock(token, 0, 0);
        }
        boolean active = token != 0;
        check(
            active == requestsTaskBlock(command),
            "TaskBlock recording is " + (active ? "on" : "off") + " for command '" + command + "'");
        Map<String, Long> counters = profiler.getDebugCounters();
        check(counters.containsKey(EMITTED), "Profiler library was built without COUNTERS");
        return new Recording(profiler, command, active, file, counters);
      } catch (Exception | Error e) {
        if (started) {
          profiler.stop();
        }
        Files.deleteIfExists(file);
        throw e;
      }
    }

    boolean taskBlockActive() {
      return taskBlockActive;
    }

    /**
     * Stops the recording and prints one {@code [taskblock-bench]} line with the TaskBlock event
     * count, event rate and JFR size of the whole trial, warmup included.
     *
     * @return counter deltas since {@link #start}; empty when the library was never loaded
     */
    Map<String, Long> stop(String benchmark) throws IOException {
      double seconds = (System.nanoTime() - startNanos) / 1e9;
      long bytes = 0;
      if (file != null) {
        // Stop before reading the counters, so intervals closed by stop are counted; counters
        // are reset only by the next start.
        profiler.stop();
        bytes = Files.size(file);
        if (Boolean.getBoolean("ddprof_test.keep_jfrs")) {
          System.out.println("===> benchmark recording: " + file.toAbsolutePath());
        } else {
          Files.deleteIfExists(file);
        }
      }
      Map<String, Long> deltas = new HashMap<>();
      if (profiler != null) {
        for (Map.Entry<String, Long> entry : profiler.getDebugCounters().entrySet()) {
          deltas.put(entry.getKey(), entry.getValue() - delta(before, entry.getKey()));
        }
      }
      long emitted = delta(deltas, EMITTED);
      // A DEBUG-only counter shows which library build was measured.
      String build =
          profiler == null ? "none" : deltas.containsKey(DEBUG_ONLY_COUNTER) ? "debug" : "release";
      System.out.printf(
          Locale.ROOT,
          "[taskblock-bench] benchmark=%s build=%s command=%s taskBlock=%s emitted=%d tooShort=%d"
              + " eventsPerSec=%.1f jfrBytes=%d seconds=%.1f%n",
          benchmark,
          build,
          command,
          taskBlockActive,
          emitted,
          delta(deltas, TOO_SHORT),
          emitted / seconds,
          bytes,
          seconds);
      return deltas;
    }
  }

  static long delta(Map<String, Long> deltas, String counter) {
    Long value = deltas.get(counter);
    return value != null ? value : 0L;
  }
}
