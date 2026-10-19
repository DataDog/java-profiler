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

import static com.datadoghq.profiler.referencechains.ReferenceChainAssertions.LEAK_TAG_BASE;
import static com.datadoghq.profiler.referencechains.ReferenceChainAssertions.LEAK_TAG_POOL_SIZE;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;
import static org.junit.jupiter.api.Assumptions.assumeFalse;

/**
 * The thread-local taxonomy of the leak-tag correlation use case, end-to-end
 * in a separate child JVM (same separate-process rationale as
 * {@code LeakTagCorrelationReferenceChainTest}'s own class comment): a growing
 * {@code byte[]} collection held ONLY through the leaking thread's
 * {@code ThreadLocal} map must still produce a correlated
 * {@code datadog.ReferenceChain} - {@code targetTag} in the leak-tag pool
 * range, matched by a {@code datadog.HeapLiveObject} {@code leakTag}. The
 * scenario is {@code ThreadLocalLeakScenario}.
 */
@Tag("slow")
public class ThreadLocalLeakReferenceChainTest extends AbstractProcessProfilerTest {

  @Test
  void shouldCorrelateThreadLocalHeldLeakChain() throws Exception {
    assumeFalse(Platform.isJavaVersion(8));
    assumeFalse(Platform.isJ9());
    assumeFalse(Platform.isZing());

    Path scratchDumpPath = Files.createTempFile("referencechains-tl-correlation-", ".jfr");
    Files.deleteIfExists(scratchDumpPath);
    Path continuousJfrPath = Files.createTempFile("referencechains-tl-correlation-continuous-", ".jfr");
    Deque<String> testLogTail = new ArrayDeque<>();
    try {
      // Same raised budget/ratio rationale as
      // LeakTagCorrelationReferenceChainTest (cold external JVM, ~100k filler,
      // memory=64:l:1.0 keeping every chunk allocation tracked).
      String startCommand = "start,memory=64:l:1.0,generations=true,"
          + "referencechains=true:hops=64:budget=200000:ttl=120000:framecap=2000000:"
          + "pausetarget=60000"
          + ",jfr,file=" + continuousJfrPath.toAbsolutePath();
      String packedCommand = startCommand + "|||" + scratchDumpPath.toAbsolutePath();

      List<String> jvmArgs = Collections.singletonList(
          "-Dddprof_test.config=" + ReferenceChainAssertions.requiredTestConfig());

      AtomicReference<String> resultLine = new AtomicReference<>();
      LaunchResult result = launch("threadlocal-leak", jvmArgs, packedCommand,
          Collections.emptyMap(),
          childTimeoutSeconds(150),
          line -> {
            if (line.startsWith(ThreadLocalLeakScenario.FOUND_MARKER)
                || line.equals(ThreadLocalLeakScenario.NOT_FOUND_MARKER)
                || line.startsWith(ThreadLocalLeakScenario.TAG_OUT_OF_POOL_MARKER)
                || line.startsWith(ThreadLocalLeakScenario.NO_LIVE_OBJECT_MARKER)
                || line.equals(ThreadLocalLeakScenario.HANDOFF_TIMEOUT_MARKER)) {
              resultLine.set(line);
            }
            if (line.startsWith("[TEST::INFO]")) {
              // Synchronized: the reader thread can outlive a join timeout.
              synchronized (testLogTail) {
                testLogTail.addLast(line);
                while (testLogTail.size() > 2000) {
                  testLogTail.removeFirst();
                }
              }
            }
            return LineConsumerResult.CONTINUE;
          },
          null);

      assertTrue(result.inTime, "Child process did not exit within the wait timeout"
          + diagnostics(testLogTail));
      assertEquals(0, result.exitCode, "Child process exited with a non-zero code");
      assertNotNull(resultLine.get(), "Child process never printed a recognizable result "
          + "marker on stdout" + diagnostics(testLogTail));
      String line = resultLine.get();
      if (line.startsWith(ThreadLocalLeakScenario.FOUND_MARKER)) {
        long targetTag = Long.parseLong(
            line.substring(ThreadLocalLeakScenario.FOUND_MARKER.length()).trim());
        assertTrue(targetTag >= LEAK_TAG_BASE && targetTag < LEAK_TAG_BASE + LEAK_TAG_POOL_SIZE,
            "Reported targetTag " + targetTag + " is outside the leak-tag pool range ["
                + LEAK_TAG_BASE + ", " + (LEAK_TAG_BASE + LEAK_TAG_POOL_SIZE) + ")");
        return;
      }
      fail("Thread-local leak-tag correlation did not succeed: " + line
          + diagnostics(testLogTail));
    } finally {
      Files.deleteIfExists(scratchDumpPath);
      Files.deleteIfExists(continuousJfrPath);
    }
  }

  /**
   * Same contract as {@link #shouldCorrelateThreadLocalHeldLeakChain()}, but
   * the leak thread is started only AFTER the recording began. Regression
   * test for the {@code Profiler::onThreadStart} →
   * {@code registerThreadObject()} wiring: a mid-recording thread is
   * invisible to {@code registerExistingThreads()}'s one-time snapshot, so
   * only the onThreadStart registration lets
   * {@code walkCandidateThreadLocals()} reach its ThreadLocalMap-held leak.
   * With the wiring broken this child reports
   * {@code ThreadLocalLeakScenario.NOT_FOUND_MARKER} and this test fails.
   */
  @Test
  void shouldCorrelateLeakOnThreadCreatedAfterRecordingStart() throws Exception {
    assumeFalse(Platform.isJavaVersion(8));
    assumeFalse(Platform.isJ9());
    assumeFalse(Platform.isZing());

    Path scratchDumpPath = Files.createTempFile("referencechains-tl-late-", ".jfr");
    Files.deleteIfExists(scratchDumpPath);
    Path continuousJfrPath = Files.createTempFile("referencechains-tl-late-continuous-", ".jfr");
    Deque<String> testLogTail = new ArrayDeque<>();
    try {
      String startCommand = "start,memory=64:l:1.0,generations=true,"
          + "referencechains=true:hops=64:budget=200000:ttl=120000:framecap=2000000:"
          + "pausetarget=60000"
          + ",jfr,file=" + continuousJfrPath.toAbsolutePath();
      String packedCommand = startCommand + "|||" + scratchDumpPath.toAbsolutePath();

      List<String> jvmArgs = Collections.singletonList(
          "-Dddprof_test.config=" + ReferenceChainAssertions.requiredTestConfig());

      AtomicReference<String> resultLine = new AtomicReference<>();
      LaunchResult result = launch("threadlocal-leak-late", jvmArgs, packedCommand,
          Collections.emptyMap(),
          childTimeoutSeconds(150),
          line -> {
            if (line.startsWith(ThreadLocalLeakScenario.FOUND_MARKER)
                || line.equals(ThreadLocalLeakScenario.NOT_FOUND_MARKER)
                || line.startsWith(ThreadLocalLeakScenario.TAG_OUT_OF_POOL_MARKER)
                || line.startsWith(ThreadLocalLeakScenario.NO_LIVE_OBJECT_MARKER)
                || line.equals(ThreadLocalLeakScenario.HANDOFF_TIMEOUT_MARKER)) {
              resultLine.set(line);
            }
            if (line.startsWith("[TEST::INFO]")) {
              // Synchronized: the reader thread can outlive a join timeout.
              synchronized (testLogTail) {
                testLogTail.addLast(line);
                while (testLogTail.size() > 2000) {
                  testLogTail.removeFirst();
                }
              }
            }
            return LineConsumerResult.CONTINUE;
          },
          null);

      assertTrue(result.inTime, "Child process did not exit within the wait timeout"
          + diagnostics(testLogTail));
      assertEquals(0, result.exitCode, "Child process exited with a non-zero code");
      assertNotNull(resultLine.get(), "Child process never printed a recognizable result "
          + "marker on stdout" + diagnostics(testLogTail));
      String line = resultLine.get();
      assertTrue(line.startsWith(ThreadLocalLeakScenario.FOUND_MARKER),
          "Thread-local leak held by a thread created after recording start was not "
              + "correlated: " + line + diagnostics(testLogTail));
    } finally {
      Files.deleteIfExists(scratchDumpPath);
      Files.deleteIfExists(continuousJfrPath);
    }
  }

  /** Filtered summary of the child's TEST_LOG stream, embedded in failure messages. */
  private static String diagnostics(Deque<String> testLogTailRef) {
    List<String> testLogTail;
    synchronized (testLogTailRef) {
      testLogTail = new ArrayList<>(testLogTailRef);
    }
    if (testLogTail.isEmpty()) {
      return "\n(no TEST_LOG output captured - non-debug build or no reference-chain passes ran)";
    }
    List<String> threadWalk = new ArrayList<>();
    List<String> runPassDone = new ArrayList<>();
    List<String> gotw = new ArrayList<>();
    List<String> leakTagLines = new ArrayList<>();
    for (String s : testLogTail) {
      if (s.contains("walkCandidateThreadLocals")) {
        threadWalk.add(s);
      } else if (s.contains("runPass done:")) {
        runPassDone.add(s);
      } else if (s.contains("expandFrontier gotw")) {
        gotw.add(s);
      } else if (s.contains("leak-tag intercepted")
          || s.contains("correlateAdmittedLeakTag")
          || s.contains("tagLeakInstances summary")) {
        leakTagLines.add(s);
      }
    }
    StringBuilder sb = new StringBuilder("\n--- filtered TEST_LOG tail ---\n");
    appendTail(sb, "thread-walk:", threadWalk, 10);
    appendTail(sb, "runPass:", runPassDone, 5);
    appendTail(sb, "gotw:", gotw, 5);
    appendTail(sb, "leak-tag:", leakTagLines, 10);
    return sb.toString();
  }

  private static void appendTail(StringBuilder sb, String label, List<String> lines, int cap) {
    if (lines.isEmpty()) {
      return;
    }
    sb.append(label).append('\n');
    int start = Math.max(0, lines.size() - cap);
    for (int i = start; i < lines.size(); i++) {
      sb.append("  ").append(lines.get(i)).append('\n');
    }
  }
}
