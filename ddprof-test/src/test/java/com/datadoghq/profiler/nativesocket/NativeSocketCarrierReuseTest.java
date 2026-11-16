/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativesocket;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

import com.datadoghq.profiler.CarrierThreadTestSupport;
import com.datadoghq.profiler.Platform;
import java.lang.management.ManagementFactory;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.junit.jupiter.api.Test;
import org.junit.platform.engine.discovery.DiscoverySelectors;
import org.junit.platform.launcher.core.LauncherDiscoveryRequestBuilder;
import org.junit.platform.launcher.core.LauncherFactory;
import org.junit.platform.launcher.listeners.SummaryGeneratingListener;

/** Replays context writes followed by a pinned socket read on a reused, single JVM carrier. */
public class NativeSocketCarrierReuseTest {
  @Test
  public void contextWriterThenPinnedReadOnReusedCarrier() throws Exception {
    assumeTrue(Platform.isLinux() && Platform.isJavaVersionAtLeast(21));
    List<String> command = new ArrayList<>();
    command.add(Paths.get(System.getProperty("java.home"), "bin", "java").toString());
    command.addAll(ManagementFactory.getRuntimeMXBean().getInputArguments());
    command.add("-Djdk.virtualThreadScheduler.parallelism=1");
    command.add("-Djdk.virtualThreadScheduler.maxPoolSize=1");
    command.add("-cp");
    command.add(System.getProperty("java.class.path"));
    command.add(NativeSocketCarrierReuseTest.class.getName());
    Path output =
        Files.createTempFile(
            Files.createDirectories(Paths.get("/tmp/recordings")),
            "native-socket-carrier-reuse",
            ".log");
    Process child =
        new ProcessBuilder(command)
            .redirectErrorStream(true)
            .redirectOutput(output.toFile())
            .start();
    try {
      assertTrue(
          child.waitFor(180, TimeUnit.SECONDS), "ordered carrier-reuse JVM timed out: " + output);
      String log = new String(Files.readAllBytes(output), StandardCharsets.UTF_8);
      assertEquals(0, child.exitValue(), log);
      assertTrue(log.contains("ORDERED_CARRIER_REUSE_PASSED"), log);
      Matcher expected = Pattern.compile("CARRIER_REUSE_EXPECTED carrier=(\\d+)").matcher(log);
      Matcher actual = Pattern.compile("PINNED_READ_OBSERVED carrier=(\\d+)").matcher(log);
      assertTrue(expected.find(), log);
      assertTrue(actual.find(), log);
      assertEquals(
          expected.group(1), actual.group(1), "T1 must reuse the predecessor's carrier: " + log);
      assertFalse(actual.find(), "ordered run must contain exactly one pinned read: " + log);
    } finally {
      if (child.isAlive()) {
        child.destroyForcibly();
        assertTrue(child.waitFor(10, TimeUnit.SECONDS), "ordered carrier-reuse JVM did not exit");
      }
      System.out.println("Ordered carrier-reuse log: " + output);
    }
  }

  /** Runs both real test lifecycles in order, rather than relying on test discovery order. */
  public static void main(String[] args) throws Exception {
    assertEquals("1", System.getProperty("jdk.virtualThreadScheduler.parallelism"));
    assertEquals("1", System.getProperty("jdk.virtualThreadScheduler.maxPoolSize"));
    long carrier = observeCarrier();
    String[] methods = {
      "com.datadoghq.profiler.context.AllNativeContextTest#nativeWritesFromVirtualThreadsAreCoherent",
      "com.datadoghq.profiler.nativesocket.NativeSocketCoexistenceTest#pinnedJniSocketReadIdentifiesObservedCarrierAndNativeThread"
    };
    for (String method : methods) {
      SummaryGeneratingListener listener = new SummaryGeneratingListener();
      LauncherFactory.create()
          .execute(
              LauncherDiscoveryRequestBuilder.request()
                  .selectors(DiscoverySelectors.selectMethod(method))
                  .build(),
              listener);
      listener.getSummary().printFailuresTo(new java.io.PrintWriter(System.out, true));
      assertEquals(1, listener.getSummary().getTestsSucceededCount(), method);
      assertEquals(0, listener.getSummary().getTestsSkippedCount(), method);
    }
    assertEquals(carrier, observeCarrier(), "the sole carrier must survive both test lifecycles");
    System.out.println("CARRIER_REUSE_EXPECTED carrier=" + carrier);
    System.out.println("ORDERED_CARRIER_REUSE_PASSED");
  }

  private static long observeCarrier() throws Exception {
    AtomicLong identity = new AtomicLong();
    Thread virtual =
        (Thread)
            Thread.class
                .getMethod("startVirtualThread", Runnable.class)
                .invoke(
                    null,
                    (Runnable) () -> identity.set(CarrierThreadTestSupport.runPinned(() -> {})));
    virtual.join(5_000L);
    assertFalse(virtual.isAlive(), "carrier identity probe did not complete");
    assertTrue(identity.get() > 0, "carrier identity probe failed");
    return identity.get();
  }
}
