/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.junit.jupiter.api.Test;

/**
 * Reloading a sampling {@code -agentpath} library reruns {@code VM::ready()}: it must skip the
 * table parsing, keep the segment shift final and keep sampling. Debug builds only ({@code
 * [TEST::INFO]}).
 */
public class VMReadyRerunTest extends AbstractProcessProfilerTest {
  private static final String INIT_SKIPPED = "VMStructs::init skipped: tables already parsed";
  private static final Pattern SHIFT =
      Pattern.compile("VMStructs::resolveOffsets shift entry=(-?\\d+) exit=(-?\\d+)");

  /**
   * True if entry equals exit and lies in 0..16. An int overflow counts as unstable instead of
   * killing the stdout reader thread.
   */
  private static boolean isStableShift(String entry, String exit) {
    try {
      int entryShift = Integer.parseInt(entry);
      int exitShift = Integer.parseInt(exit);
      return entryShift == exitShift && exitShift >= 0 && exitShift <= 16;
    } catch (NumberFormatException e) {
      return false;
    }
  }

  @Test
  void reloadWhileSamplingKeepsSegmentShift() throws Exception {
    assumeTrue(
        "debug".equals(System.getProperty("ddprof_test.config")), "needs [TEST::INFO] output");
    assumeTrue(!Platform.isJ9() && !Platform.isZing(), "VMStructs is HotSpot-only");
    Path agentLib = LibraryLoader.resolveLibraryPath(System.getProperty("java.io.tmpdir"));
    Path jfr = Files.createTempFile("vm-ready-rerun-", ".jfr");
    AtomicBoolean reloading = new AtomicBoolean();
    AtomicBoolean reloaded = new AtomicBoolean();
    AtomicInteger skips = new AtomicInteger();
    AtomicInteger resolves = new AtomicInteger();
    List<String> unstable = Collections.synchronizedList(new ArrayList<>());
    try {
      LaunchResult result =
          launch(
              "profiler-at",
              Collections.singletonList(
                  "-agentpath:"
                      + agentLib.toAbsolutePath()
                      + "=start,cpu=10ms,jfr,file="
                      + jfr.toAbsolutePath()),
              agentLib.toAbsolutePath().toString(),
              l -> {
                if (l.contains("[getInstance-begin]")) {
                  reloading.set(true);
                } else if (l.contains("[getInstance-done]")) {
                  reloading.set(false);
                  reloaded.set(true);
                } else if (reloading.get()) {
                  if (l.contains(INIT_SKIPPED)) {
                    skips.incrementAndGet();
                  }
                  Matcher m = SHIFT.matcher(l);
                  if (m.find()) {
                    resolves.incrementAndGet();
                    if (!isStableShift(m.group(1), m.group(2))) {
                      unstable.add(l);
                    }
                  }
                }
                return LineConsumerResult.CONTINUE;
              },
              null);

      assertTrue(result.inTime, "forked JVM did not exit in time");
      assertEquals(0, result.exitCode, "forked JVM exited with an error");
      assertTrue(reloaded.get(), "getInstance() on the agent library did not return");
      assertTrue(
          skips.get() > 0,
          "the reload did not rerun VM::ready() in the agent's library image, or reparsed the tables");
      assertTrue(resolves.get() > 0, "the reload did not resolve the VMStructs offsets");
      assertTrue(unstable.isEmpty(), "a rerun changed or invalidated the shift: " + unstable);

      AtomicBoolean sampledAfterReload = new AtomicBoolean();
      JfrEvents.load(
          jfr,
          "datadog.ExecutionSample"::equals,
          e -> {
            if (e.getStackTraceString().contains("spinAfterReload")) {
              sampledAfterReload.set(true);
            }
            return sampledAfterReload.get();
          });
      assertTrue(sampledAfterReload.get(), "the agent recorded no samples after the reload");
    } finally {
      Files.deleteIfExists(jfr);
    }
  }
}
