/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Deque;
import java.util.List;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;
import static org.junit.jupiter.api.Assumptions.assumeFalse;

/**
 * End-to-end coverage of the leak-tag correlation use case in a genuinely separate child
 * JVM (same rationale as {@code ExternalProcessReferenceChainTest}'s own class comment -
 * the one-shot root-seeded BFS walk is a per-process resource): a growing static-collection
 * leak amid ephemeral stack-local noise and a large live filler graph must be reported as a
 * {@code datadog.ReferenceChain} whose {@code targetTag} is in the leak-tag pool's range
 * AND matches a {@code datadog.HeapLiveObject}'s {@code leakTag}. See
 * {@link LeakTagCorrelationScenario}'s own header for what each ingredient reproduces.
 *
 * <p><b>Diagnostics on failure:</b> unlike the pod-debugging loop this scenario exists to
 * replace, the child's {@code TEST_LOG} stream (queue depths, batch sizes, interception
 * counts - the same evidence collected off a live pod's logs) arrives on this process's
 * stdout consumer. A failing run embeds a filtered tail of it in the assertion message, so
 * the failure mode is diagnosable without redeploying anything.
 */
@Tag("slow")
public class LeakTagCorrelationReferenceChainTest extends AbstractProcessProfilerTest {

  // Mirrored from referenceChains.h (LEAK_TAG_BASE/LEAK_TAG_POOL_SIZE) - the contract under
  // test, asserted against the runtime event values the child reports.
  private static final long LEAK_TAG_BASE = 0x40000000L;
  private static final long LEAK_TAG_POOL_SIZE = 256;

  @Test
  void shouldCorrelateLeakChainTargetTagWithLiveObjectLeakTag() throws Exception {
    assumeFalse(Platform.isJavaVersion(8));
    assumeFalse(Platform.isJ9());
    assumeFalse(Platform.isZing());

    Path scratchDumpPath = Files.createTempFile("referencechains-correlation-", ".jfr");
    Files.deleteIfExists(scratchDumpPath);
    Path continuousJfrPath = Files.createTempFile("referencechains-correlation-continuous-", ".jfr");
    // Rolling tail of the child's TEST_LOG stream for failure diagnostics - bounded so a
    // long run cannot grow this without limit.
    Deque<String> testLogTail = new ArrayDeque<>();
    try {
      // Same raised budget/pausetarget as ExternalProcessReferenceChainTest's own scenarios:
      // a genuinely fresh, cold external JVM's reachable graph is far larger than the
      // in-process tests', and this scenario adds ~100k filler objects on top.
      String startCommand = "start,memory=64:l,generations=true,"
          + "referencechains=true:hops=64:budget=200000:ttl=120000:framecap=2000000:pausetarget=60000"
          + ",jfr,file=" + continuousJfrPath.toAbsolutePath();
      String packedCommand = startCommand + "|||" + scratchDumpPath.toAbsolutePath();

      List<String> jvmArgs = Collections.singletonList(
          "-Dddprof_test.config=" + System.getProperty("ddprof_test.config"));

      AtomicReference<String> resultLine = new AtomicReference<>();
      LaunchResult result = launch("leak-correlation", jvmArgs, packedCommand,
          Collections.emptyMap(),
          // The scenario's own round loop (up to 25 rounds plus a 5-attempt grace period,
          // ~40-60s observed) on top of a cold external JVM's startup/classloading cost and
          // this scenario's larger graph - same margin logic as the existing scenarios.
          150,
          line -> {
            if (line.startsWith(LeakTagCorrelationScenario.FOUND_MARKER)
                || line.equals(LeakTagCorrelationScenario.NOT_FOUND_MARKER)
                || line.startsWith(LeakTagCorrelationScenario.TAG_OUT_OF_POOL_MARKER)
                || line.startsWith(LeakTagCorrelationScenario.NO_LIVE_OBJECT_MARKER)
                || line.startsWith(LeakTagCorrelationScenario.TRANSIENT_CHAIN_MARKER)
                || line.startsWith(LeakTagCorrelationScenario.NOISE_CHAIN_MARKER)) {
              resultLine.set(line);
            }
            if (line.startsWith("[TEST::INFO]")) {
              testLogTail.addLast(line);
              while (testLogTail.size() > 2000) {
                testLogTail.removeFirst();
              }
            }
            return LineConsumerResult.CONTINUE;
          },
          null);

      assertTrue(result.inTime, "Child process did not exit within the wait timeout");
      assertEquals(0, result.exitCode, "Child process exited with a non-zero code");
      assertNotNull(resultLine.get(), "Child process never printed a recognizable result marker"
          + " on stdout" + diagnostics(testLogTail));
      String line = resultLine.get();
      if (line.startsWith(LeakTagCorrelationScenario.FOUND_MARKER)) {
        long targetTag = Long.parseLong(
            line.substring(LeakTagCorrelationScenario.FOUND_MARKER.length()).trim());
        assertTrue(targetTag >= LEAK_TAG_BASE && targetTag < LEAK_TAG_BASE + LEAK_TAG_POOL_SIZE,
            "Reported targetTag " + targetTag + " is outside the leak-tag pool range ["
                + LEAK_TAG_BASE + ", " + (LEAK_TAG_BASE + LEAK_TAG_POOL_SIZE) + ")");
        return;
      }
      fail("Leak-tag correlation did not succeed: " + line + diagnostics(testLogTail));
    } finally {
      Files.deleteIfExists(scratchDumpPath);
      Files.deleteIfExists(continuousJfrPath);
    }
  }

  /**
   * A filtered summary of the child's TEST_LOG stream for failure messages: the last few
   * pass summaries (queue depths are the first thing to check on any crawl stall), the
   * gotw batch-size trace (batch control regressions), and any leak-tag interception or
   * correlation lines. Capped so the message stays readable.
   */
  private static String diagnostics(Deque<String> testLogTail) {
    if (testLogTail.isEmpty()) {
      return "\n(no TEST_LOG output captured - non-debug build or no reference-chain passes ran)";
    }
    List<String> runPassDone = new ArrayList<>();
    List<String> gotw = new ArrayList<>();
    List<String> leakTagLines = new ArrayList<>();
    for (String s : testLogTail) {
      if (s.contains("runPass done:")) {
        runPassDone.add(s);
      } else if (s.contains("expandFrontier gotw")) {
        gotw.add(s);
      } else if (s.contains("intercepted") || s.contains("correlateAdmittedLeakTag")
          || s.contains("recordDiscoveredInstance") || s.contains("auto-mark")
          || s.contains("rotation_candidates")) {
        leakTagLines.add(s);
      }
    }
    StringBuilder sb = new StringBuilder("\n--- child diagnostics (filtered TEST_LOG) ---");
    appendLast(sb, "runPass done", runPassDone, 5);
    appendLast(sb, "gotw", gotw, 5);
    appendLast(sb, "leak-tag activity", leakTagLines, 20);
    return sb.toString();
  }

  private static void appendLast(StringBuilder sb, String label, List<String> lines, int max) {
    sb.append("\n").append(label).append(" (last ").append(max).append(" of ")
        .append(lines.size()).append("):");
    int from = Math.max(0, lines.size() - max);
    for (int i = from; i < lines.size(); i++) {
      sb.append("\n  ").append(lines.get(i));
    }
  }
}
