/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

/** Verifies that OpenJ9's ASGCT wall engine supports native socket TaskBlock production. */
public class OpenJ9NativeSocketTaskBlockTest extends AbstractProfilerTest {
  private static final int BLOCK_HOLD_MILLIS = 250;

  /** Requires hook installation, signal suppression, and a self-contained worker TaskBlock. */
  @Test
  public void asgctWallEngineEmitsNativeSocketTaskBlock() throws Exception {
    String workerName = "taskblock-openj9-native-socket-read";
    Map<String, Long> before = profiler.getDebugCounters();
    assertExpectedHookPath(before);

    runBlockingSocketRead(workerName);

    Map<String, Long> after = profiler.getDebugCounters();
    assertTrue(
        after.getOrDefault("task_block_emitted", 0L)
            > before.getOrDefault("task_block_emitted", 0L),
        "OpenJ9 native socket read did not emit a TaskBlock");
    assertTrue(
        after.getOrDefault("wc_signals_suppressed_owned_block", 0L)
            > before.getOrDefault("wc_signals_suppressed_owned_block", 0L),
        "OpenJ9 ASGCT wall precheck did not suppress the owned native block");
    assertEquals(
        before.getOrDefault("task_block_stack_capture_failed", 0L),
        after.getOrDefault("task_block_stack_capture_failed", 0L),
        "OpenJ9 TaskBlock stack capture failed");
    assertEquals(
        before.getOrDefault("task_block_record_failed", 0L),
        after.getOrDefault("task_block_record_failed", 0L),
        "OpenJ9 TaskBlock recording failed");

    stopProfiler();
    IItemCollection taskBlocks = verifyEvents("datadog.TaskBlock", false);
    assertTrue(
        TaskBlockAssertions.containsObservedStateForEventThread(
            taskBlocks, "IO_WAIT", workerName),
        "Expected an OpenJ9 native IO_WAIT TaskBlock for " + workerName);
    TaskBlockAssertions.assertContainsStackTrace(taskBlocks);
    TaskBlockAssertions.assertContainsJavaType(taskBlocks, "OpenJ9NativeSocketTaskBlockTest");
    TaskBlockAssertions.assertNoCorrelationId(taskBlocks);
  }

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isLinux() && Platform.isJ9();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  private static void assertExpectedHookPath(Map<String, Long> counters) {
    long standardHooks = counters.getOrDefault("native_io_standard_hooks_patched", 0L);
    long ibmBridgeHooks = counters.getOrDefault("native_io_ibm_bridge_hooks_patched", 0L);
    if (isLegacyIbmJ9()) {
      assertTrue(
          ibmBridgeHooks > 0,
          "Legacy IBM J9 must install native I/O hooks in the IBM JCL bridge; "
              + hookDiagnostic(standardHooks, ibmBridgeHooks));
    } else {
      assertTrue(
          standardHooks > 0,
          "Semeru/OpenJ9 must install native I/O hooks in standard JDK networking libraries; "
              + hookDiagnostic(standardHooks, ibmBridgeHooks));
    }
  }

  private static boolean isLegacyIbmJ9() {
    String vmName = System.getProperty("java.vm.name", "");
    String fullVersion = System.getProperty("java.fullversion", "");
    return vmName.contains("IBM J9") || fullVersion.startsWith("JRE 1.8.0 IBM");
  }

  private static String hookDiagnostic(long standardHooks, long ibmBridgeHooks) {
    return "java.vm.name="
        + System.getProperty("java.vm.name", "")
        + ", java.fullversion="
        + System.getProperty("java.fullversion", "")
        + ", standard hooks="
        + standardHooks
        + ", IBM bridge hooks="
        + ibmBridgeHooks;
  }

  private static void runBlockingSocketRead(String workerName) throws Exception {
    CountDownLatch readAttempted = new CountDownLatch(1);
    AtomicReference<Throwable> error = new AtomicReference<>();

    try (ServerSocket server = new ServerSocket(0)) {
      Thread reader =
          new Thread(
              () -> {
                try (Socket socket = new Socket("127.0.0.1", server.getLocalPort())) {
                  InputStream input = socket.getInputStream();
                  readAttempted.countDown();
                  int value = input.read();
                  if (value != 1) {
                    throw new AssertionError("unexpected socket byte: " + value);
                  }
                } catch (Throwable t) {
                  error.set(t);
                }
              },
              workerName);

      reader.start();
      try (Socket accepted = server.accept()) {
        assertTrue(readAttempted.await(5, TimeUnit.SECONDS), "reader did not enter socket read");
        Thread.sleep(BLOCK_HOLD_MILLIS);
        OutputStream output = accepted.getOutputStream();
        output.write(1);
        output.flush();
      }
      reader.join(5_000L);
      assertFalse(reader.isAlive(), "socket reader did not complete");
      if (error.get() != null) {
        throw new AssertionError(error.get());
      }
    }
  }
}
