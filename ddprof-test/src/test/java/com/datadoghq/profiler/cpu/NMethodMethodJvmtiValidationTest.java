/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.Platform;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.atomic.AtomicReference;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

/**
 * Validates, against JVMTI itself, the {@code nmethod::_method} offset the profiler reads when it
 * resolves a compiled method.
 *
 * <p>A child JVM starts the profiler, forces {@code ExternalLauncher.nmethodMethodTarget} to be
 * compiled, and asks the profiler's test seam for every compiled body of that method. For each body
 * the child prints the code address JVMTI {@code CompiledMethodLoad} gives for it, whether the
 * profiler's code-heap lookup found the nmethod, and the jmethodID the profiler reads through that
 * nmethod's {@code _method} field. The test compares the last value with the jmethodID JVMTI
 * reports for the same code address.
 *
 * <p>The two values come from independent sources: HotSpot produces the event from its own
 * nmethod-to-{@code Method} link, which never passes through the profiler's vmStructs offsets.
 * {@code -Xbatch} makes compilation synchronous, so the target is compiled when the seam runs, and
 * the {@code dontinline} compile command gives the target its own nmethod instead of letting it be
 * inlined into the calling loop.
 */
public class NMethodMethodJvmtiValidationTest extends AbstractProcessProfilerTest {
  private static final String TARGET = "ExternalLauncher.nmethodMethodTarget";

  private static final String UNSUPPORTED = "[nmethod-method] unsupported";

  // The reads body is empty or "<addr>/<status>/<read>" triples; Long.toHexString is always
  // non-empty lowercase hex, so each token is bounded to at least one digit.
  private static final Pattern REPORT =
      Pattern.compile(
          "\\[nmethod-method\\] target=([0-9a-f]+) reads=((?:[0-9a-f]+/[0-9a-f]+/[0-9a-f]+)?(?:,[0-9a-f]+/[0-9a-f]+/[0-9a-f]+)*)");

  @Test
  @Timeout(120)
  public void nmethodMethodReadMatchesJvmti() throws Exception {
    Assumptions.assumeFalse(
        Platform.isZing() || Platform.isJ9() || Platform.isGraal(), "HotSpot only");
    Path recording = Files.createTempFile("nmethod-method-", ".jfr");
    try {
      // The line consumer runs on the reader thread.
      AtomicReference<String> report = new AtomicReference<>();
      LaunchResult result =
          launch(
              "nmethod-method",
              Arrays.asList(
                  "-Xbatch",
                  "-XX:CompileCommand=quiet",
                  "-XX:CompileCommand=dontinline,com/datadoghq/profiler/ExternalLauncher.nmethodMethodTarget"),
              "start,cpu=10ms,cstack=vm,jfr,file=" + recording,
              Collections.emptyMap(),
              60,
              line -> {
                if (line.startsWith("[nmethod-method] ")) {
                  report.set(line);
                }
                return LineConsumerResult.CONTINUE;
              },
              null);
      assertTrue(result.inTime, "child JVM did not finish in time");
      assertEquals(0, result.exitCode, "child JVM failed");
      String line = report.get();
      assertTrue(line != null, "the child did not report nmethod reads");
      Assumptions.assumeFalse(
          line.equals(UNSUPPORTED),
          "the compiled-method-read seam is unavailable (no code heap on this JVM, "
              + "or a release native build where the debug-only seam returns null)");
      long[] values = parseReport(line);
      long target = values[0];
      // A null target or code address makes the read == target check below
      // degenerate: an all-zero report must fail, not pass as a match.
      assertTrue(target != 0, "the seam resolved no jmethodID for " + TARGET);
      assertTrue(values.length > 1, "JVMTI reported no compiled code for " + TARGET);
      for (int i = 1; i + 2 < values.length; i += 3) {
        long addr = values[i];
        assertTrue(addr != 0, "a reported read has no code address");
        long status = values[i + 1];
        long read = values[i + 2];
        assertEquals(
            0,
            status,
            "the profiler found no nmethod at JVMTI code address 0x" + Long.toHexString(addr));
        assertEquals(
            target,
            read,
            "nmethod::_method at 0x"
                + Long.toHexString(addr)
                + " resolves to jmethodID 0x"
                + Long.toHexString(read)
                + ", JVMTI reports 0x"
                + Long.toHexString(target)
                + " for "
                + TARGET);
      }
    } finally {
      Files.deleteIfExists(recording);
    }
  }

  /**
   * Parses a {@code [nmethod-method] target=<hex> reads=<addr>/<status>/<read>,...} line into
   * {@code {target, addr, status, read, ...}}. Fails with "malformed nmethod-method report: " plus
   * the offending line when the line deviates from the format, instead of leaking a bare {@link
   * NumberFormatException}.
   */
  private static long[] parseReport(String line) {
    try {
      Matcher m = REPORT.matcher(line);
      if (!m.matches()) {
        throw new NumberFormatException(line);
      }
      List<Long> values = new ArrayList<>();
      values.add(Long.parseUnsignedLong(m.group(1), 16));
      if (!m.group(2).isEmpty()) {
        for (String triple : m.group(2).split(",")) {
          String[] parts = triple.split("/");
          values.add(Long.parseUnsignedLong(parts[0], 16));
          values.add(Long.parseUnsignedLong(parts[1], 16));
          values.add(Long.parseUnsignedLong(parts[2], 16));
        }
      }
      long[] parsed = new long[values.size()];
      for (int i = 0; i < parsed.length; i++) {
        parsed[i] = values.get(i);
      }
      return parsed;
    } catch (NumberFormatException e) {
      throw new AssertionError("malformed nmethod-method report: " + line, e);
    }
  }
}
