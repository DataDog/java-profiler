/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.Method;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.Pipe;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.util.Arrays;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/** Verifies Linux native socket and readiness waits produce self-contained TaskBlock events. */
public class NativeSocketTaskBlockTest extends AbstractProfilerTest {
  private static final int BLOCK_HOLD_MILLIS = 250;
  private static final int NATIVE_BLOCK_ATTEMPTS = 5;
  private Thread preExistingPlatformPoller;

  @Override
  protected void beforeProfilerStart() throws Exception {
    System.loadLibrary("ddproftest");
    if (testInfo
        .getTestMethod()
        .get()
        .getName()
        .equals("preExistingPlatformPollerDoesNotEmitTaskBlock")) {
      Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(21), "virtual threads require JDK 21");
      runVirtualSocketRead();
      for (Thread thread : Thread.getAllStackTraces().keySet()) {
        // JDK 25's default topology uses a platform MasterPoller and virtual SubPollers.
        if (thread.getName().equals("MasterPoller") || thread.getName().equals("Read-Poller")) {
          preExistingPlatformPoller = thread;
          break;
        }
      }
      assertNotNull(
          preExistingPlatformPoller,
          "virtual socket read must create a platform poller before recording");
      assertEquals(
          "jdk.internal.misc.InnocuousThread", preExistingPlatformPoller.getClass().getName());
      assertTrue(
          preExistingPlatformPoller.isAlive(), "pre-recording platform poller must be alive");
      System.out.println(
          "PLATFORM_POLLER_OBSERVED name="
              + preExistingPlatformPoller.getName()
              + " id="
              + preExistingPlatformPoller.getId()
              + " class="
              + preExistingPlatformPoller.getClass().getName());
    }
  }

  @Test
  public void blockingSocketReadEmitsIoWaitTaskBlock() throws Exception {
    for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
      runBlockingSocketReadOnce();
    }

    stopProfiler();
    assertIoWaitTaskBlockSelfContained("taskblock-native-socket-read");
  }

  private void runBlockingSocketReadOnce() throws Exception {
    CountDownLatch readAttempted = new CountDownLatch(1);
    AtomicReference<Throwable> error = new AtomicReference<>();

    try (ServerSocket server = new ServerSocket(0)) {
      Thread reader =
          new Thread(
              () -> {
                try {
                  try (Socket socket = new Socket("127.0.0.1", server.getLocalPort())) {
                    InputStream input = socket.getInputStream();
                    readAttempted.countDown();
                    int value = input.read();
                    if (value != 1) {
                      throw new AssertionError("unexpected socket byte: " + value);
                    }
                  }
                } catch (Throwable t) {
                  error.set(t);
                }
              },
              "taskblock-native-socket-read");

      reader.start();
      try (Socket accepted = server.accept()) {
        assertTrue(readAttempted.await(5, TimeUnit.SECONDS), "reader did not enter socket read");
        Thread.sleep(BLOCK_HOLD_MILLIS);
        OutputStream output = accepted.getOutputStream();
        output.write(1);
        output.flush();
      }
      assertCompleted(reader, error);
    }
  }

  @Test
  public void blockingServerSocketAcceptEmitsIoWaitTaskBlock() throws Exception {
    for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
      runBlockingServerSocketAcceptOnce();
    }

    stopProfiler();
    assertIoWaitTaskBlockSelfContained("taskblock-native-socket-accept");
  }

  private void runBlockingServerSocketAcceptOnce() throws Exception {
    CountDownLatch acceptAttempted = new CountDownLatch(1);
    AtomicReference<Throwable> error = new AtomicReference<>();
    InetAddress loopback = InetAddress.getLoopbackAddress();

    try (ServerSocket server = new ServerSocket(0, 1, loopback)) {
      Thread accepter =
          new Thread(
              () -> {
                try {
                  acceptAttempted.countDown();
                  try (Socket accepted = server.accept()) {
                    assertTrue(accepted.isConnected());
                  }
                } catch (Throwable t) {
                  error.set(t);
                }
              },
              "taskblock-native-socket-accept");

      accepter.start();
      assertTrue(acceptAttempted.await(5, TimeUnit.SECONDS), "accept did not start");
      Thread.sleep(BLOCK_HOLD_MILLIS);
      try (Socket ignored = new Socket(loopback, server.getLocalPort())) {
        assertTrue(ignored.isConnected());
      }
      assertCompleted(accepter, error);
    }
  }

  @Test
  public void blockingDatagramReceiveEmitsIoWaitTaskBlock() throws Exception {
    for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
      runBlockingDatagramReceiveOnce();
    }

    stopProfiler();
    assertIoWaitTaskBlockSelfContained("taskblock-native-datagram-receive");
  }

  private void runBlockingDatagramReceiveOnce() throws Exception {
    CountDownLatch receiveAttempted = new CountDownLatch(1);
    AtomicReference<Throwable> error = new AtomicReference<>();
    InetAddress loopback = InetAddress.getLoopbackAddress();

    try (DatagramSocket receiver = new DatagramSocket(new InetSocketAddress(loopback, 0))) {
      Thread receiverThread =
          new Thread(
              () -> {
                try {
                  byte[] data = new byte[1];
                  DatagramPacket packet = new DatagramPacket(data, data.length);
                  receiveAttempted.countDown();
                  receiver.receive(packet);
                  assertEquals(1, packet.getLength());
                  assertEquals(7, data[0]);
                } catch (Throwable t) {
                  error.set(t);
                }
              },
              "taskblock-native-datagram-receive");

      receiverThread.start();
      assertTrue(receiveAttempted.await(5, TimeUnit.SECONDS), "receive did not start");
      Thread.sleep(BLOCK_HOLD_MILLIS);
      try (DatagramSocket sender = new DatagramSocket()) {
        byte[] data = new byte[] {7};
        DatagramPacket packet =
            new DatagramPacket(data, data.length, loopback, receiver.getLocalPort());
        sender.send(packet);
      }
      assertCompleted(receiverThread, error);
    }
  }

  @Test
  public void blockingSelectorSelectEmitsIoWaitTaskBlock() throws Exception {
    String workerName = "taskblock-native-selector-select";
    long suppressedBefore =
        profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L);
    runBlockingSelectorSelectOnce();
    long suppressedAfter =
        profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L);
    assertTrue(
        suppressedAfter > suppressedBefore,
        "Expected wall signals to be suppressed during the native selector wait");

    stopProfiler();
    JfrEvents taskBlocks = verifyEvents("datadog.TaskBlock", false);
    assertIoWaitTaskBlockSelfContained(taskBlocks, workerName);
    int workerEvents = TaskBlockAssertions.countEventsForThread(taskBlocks, workerName);
    assertTrue(
        workerEvents >= 1 && workerEvents <= 2,
        "Expected one logical selector wait to produce at most two TaskBlocks, got: "
            + workerEvents);
  }

  private void runBlockingSelectorSelectOnce() throws Exception {
    CountDownLatch selectAttempted = new CountDownLatch(1);
    AtomicReference<Throwable> error = new AtomicReference<>();

    Pipe pipe = Pipe.open();
    try (Selector selector = Selector.open();
        Pipe.SourceChannel source = pipe.source();
        Pipe.SinkChannel sink = pipe.sink()) {
      source.configureBlocking(false);
      source.register(selector, SelectionKey.OP_READ);

      Thread selectorThread =
          new Thread(
              () -> {
                try {
                  selectAttempted.countDown();
                  int selected = selectUntilReady(selector, 5_000L);
                  assertTrue(selected > 0, "selector did not observe pipe readiness");
                  selector.selectedKeys().clear();
                  ByteBuffer data = ByteBuffer.allocate(1);
                  while (data.hasRemaining() && source.read(data) > 0) {}
                } catch (Throwable t) {
                  error.set(t);
                }
              },
              "taskblock-native-selector-select");

      selectorThread.start();
      assertTrue(selectAttempted.await(5, TimeUnit.SECONDS), "select did not start");
      Thread.sleep(BLOCK_HOLD_MILLIS);
      sink.write(ByteBuffer.wrap(new byte[] {1}));
      assertCompleted(selectorThread, error);
    }
  }

  @Test
  public void unpinnedVirtualSocketReadDoesNotAttributeTaskBlockToVirtualThread() throws Exception {
    Method startVirtualThread;
    try {
      startVirtualThread = Thread.class.getMethod("startVirtualThread", Runnable.class);
    } catch (NoSuchMethodException unavailableBeforeJdk21) {
      Assumptions.assumeTrue(false, "virtual threads require JDK 21");
      return;
    }

    AtomicReference<Thread> virtualThreadRef = new AtomicReference<>();
    CountDownLatch readAttempted = new CountDownLatch(1);
    AtomicReference<Throwable> error = new AtomicReference<>();

    try (ServerSocket server = new ServerSocket(0)) {
      Runnable task =
          () -> {
            virtualThreadRef.set(Thread.currentThread());
            try {
              try (Socket socket = new Socket("127.0.0.1", server.getLocalPort())) {
                InputStream input = socket.getInputStream();
                readAttempted.countDown();
                int value = input.read();
                if (value != 1) {
                  throw new AssertionError("unexpected socket byte: " + value);
                }
              }
            } catch (Throwable t) {
              error.set(t);
            }
          };
      Thread virtual = (Thread) startVirtualThread.invoke(null, task);
      try (Socket accepted = server.accept()) {
        assertTrue(readAttempted.await(5, TimeUnit.SECONDS), "reader did not enter socket read");
        Thread.sleep(BLOCK_HOLD_MILLIS);
        OutputStream output = accepted.getOutputStream();
        output.write(1);
        output.flush();
      }
      assertCompleted(virtual, error);
    }

    // Unpinned virtual I/O need not enter a native wait on its carrier. The platform
    // control verifies production is enabled; carrier attribution is tested separately.
    runBlockingSocketReadOnce();

    stopProfiler();
    JfrEvents taskBlocks = verifyEvents("datadog.TaskBlock");
    assertIoWaitTaskBlockSelfContained(taskBlocks, "taskblock-native-socket-read");
    long virtualThreadId = virtualThreadRef.get().getId();
    for (long blocker : TaskBlockAssertions.distinctBlockers(taskBlocks)) {
      TaskBlockAssertions.assertBlockerEventThreadDiffers(taskBlocks, blocker, virtualThreadId);
    }
  }

  @Test
  public void tracedBlockingSocketReadDoesNotEmitTaskBlock() throws Exception {
    String workerName = "taskblock-traced-native-socket-read";
    long skippedBefore =
        profiler.getDebugCounters().getOrDefault("task_block_skipped_trace_context", 0L);
    CountDownLatch readAttempted = new CountDownLatch(1);
    AtomicReference<Throwable> error = new AtomicReference<>();

    try (ServerSocket server = new ServerSocket(0)) {
      Thread reader =
          new Thread(
              () -> {
                try {
                  profiler.setTraceContext(0x5100L, 0x5101L, 0L, 0x5101L, -1, null, -1, null);
                  try (Socket socket = new Socket("127.0.0.1", server.getLocalPort())) {
                    InputStream input = socket.getInputStream();
                    readAttempted.countDown();
                    int value = input.read();
                    if (value != 1) {
                      throw new AssertionError("unexpected socket byte: " + value);
                    }
                  } finally {
                    profiler.clearTraceContext();
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
      assertCompleted(reader, error);
    }

    assertTrue(
        profiler.getDebugCounters().getOrDefault("task_block_skipped_trace_context", 0L)
            > skippedBefore,
        "Native socket hook did not reject the traced blocking read");
    stopProfiler();
    JfrEvents taskBlocks = verifyEvents("datadog.TaskBlock", false);
    assertFalse(
        TaskBlockAssertions.containsEventThread(taskBlocks, workerName),
        "Traced socket I/O must not emit a TaskBlock for the worker");
    JfrEvents methodSamples = verifyEvents("datadog.MethodSample", false);
    assertTrue(
        TaskBlockAssertions.containsEventThread(methodSamples, workerName),
        "Traced socket I/O must retain MethodSample wall-clock data for the worker");
    assertTrue(
        TaskBlockAssertions.containsSpan(methodSamples, 0x5101L),
        "Traced socket MethodSample must retain its span context");
  }

  @Test
  public void preExistingPlatformPollerDoesNotEmitTaskBlock() throws Exception {
    assertTrue(
        preExistingPlatformPoller.isAlive(), "pre-recording platform poller must still be alive");
    long skippedBefore =
        profiler.getDebugCounters().getOrDefault("task_block_skipped_jvm_internal_thread", 0L);
    for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
      runVirtualSocketRead();
    }
    runBlockingSocketReadOnce();
    assertTrue(preExistingPlatformPoller.isAlive(), "test must exercise the pre-recording poller");
    long skippedAfter =
        profiler.getDebugCounters().getOrDefault("task_block_skipped_jvm_internal_thread", 0L);
    stopProfiler();
    JfrEvents taskBlocks = verifyEvents("datadog.TaskBlock", false);
    assertIoWaitTaskBlockSelfContained(taskBlocks, "taskblock-native-socket-read");
    for (JfrEvent event : taskBlocks) {
      assertNotNull(event.getThreadJavaId("eventThread"));
      assertNotEquals(
          Long.valueOf(preExistingPlatformPoller.getId()),
          event.getThreadJavaId("eventThread"),
          "the actual pre-recording platform poller must not emit TaskBlocks");
    }
    assertTrue(
        skippedAfter > skippedBefore, "native admission must observe and reject JVM-internal work");
  }

  private void runVirtualSocketRead() throws Exception {
    Method startVirtualThread = Thread.class.getMethod("startVirtualThread", Runnable.class);
    CountDownLatch readAttempted = new CountDownLatch(1);
    AtomicReference<Throwable> error = new AtomicReference<>();
    try (ServerSocket server = new ServerSocket(0)) {
      Thread virtual =
          (Thread)
              startVirtualThread.invoke(
                  null,
                  (Runnable)
                      () -> {
                        try (Socket socket = new Socket("127.0.0.1", server.getLocalPort())) {
                          readAttempted.countDown();
                          assertEquals(1, socket.getInputStream().read());
                        } catch (Throwable t) {
                          error.set(t);
                        }
                      });
      try (Socket accepted = server.accept()) {
        assertTrue(readAttempted.await(5, TimeUnit.SECONDS), "virtual read did not start");
        Thread.sleep(BLOCK_HOLD_MILLIS);
        accepted.getOutputStream().write(1);
      }
      assertCompleted(virtual, error);
    }
  }

  @Test
  public void pinnedJniSocketReadIdentifiesObservedCarrierAndNativeThread() throws Exception {
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(21), "virtual threads require JDK 21");
    Method startVirtualThread = Thread.class.getMethod("startVirtualThread", Runnable.class);
    int[] sockets = openPinnedSocket0();
    assertNotNull(sockets);
    assertEquals(2, sockets.length);
    long[] observed = new long[5];
    CountDownLatch entered = new CountDownLatch(1);
    AtomicReference<Throwable> error = new AtomicReference<>();
    Thread virtual =
        (Thread)
            startVirtualThread.invoke(
                null,
                (Runnable)
                    () -> {
                      try {
                        int result = pinnedRead0(sockets[0], observed, entered);
                        assertEquals(
                            1,
                            result,
                            "carrier, tid, read result, errno, byte: " + Arrays.toString(observed));
                      } catch (Throwable t) {
                        error.set(t);
                      }
                    });
    try {
      assertTrue(entered.await(5, TimeUnit.SECONDS), "JNI read did not publish carrier identity");
      Thread.sleep(BLOCK_HOLD_MILLIS);
      assertEquals(1, releasePinnedRead0(sockets[1]));
      assertCompleted(virtual, error);
    } finally {
      closePinnedSocket0(sockets[1]);
      virtual.join(5_000L);
      closePinnedSocket0(sockets[0]);
      assertFalse(virtual.isAlive(), "pinned JNI worker did not terminate");
    }
    assertTrue(observed[0] > 0, "JNI must observe an actual carrier Java id");
    assertTrue(observed[1] > 0, "JNI must observe an actual Linux tid");
    assertNotEquals(virtual.getId(), observed[0]);
    stopProfiler();
    int matching = 0;
    long blocker = (8L << 32) | (sockets[0] & 0xffffffffL);
    for (JfrEvent event : verifyEvents("datadog.TaskBlock", false)) {
      assertNotNull(event.getLong("blocker"));
      if (event.getLong("blocker") != blocker) continue;
      matching++;
      assertEquals(Long.valueOf(observed[0]), event.getThreadJavaId("eventThread"));
      assertNotNull(event.get("eventThread"));
      Map<?, ?> eventThread = (Map<?, ?>) event.get("eventThread");
      assertNotNull(eventThread.get("osThreadId"));
      assertEquals(observed[1], ((Number) eventThread.get("osThreadId")).longValue());
      assertEquals("IO_WAIT", event.getEnumName("observedBlockingState"));
      assertNotNull(event.getLong("duration"));
      assertTrue(event.getLong("duration") >= TimeUnit.MILLISECONDS.toNanos(1));
      assertNotNull(event.get("stackTrace"));
      assertTrue(
          event.getStackTrace().frames().stream()
              .anyMatch(frame -> "pinnedRead0".equals(frame.methodName())),
          "the matching native interval must retain its pinned JNI workload frame");
    }
    assertEquals(1, matching, "the pinned JNI read must emit exactly its own TaskBlock");
    System.out.println("PINNED_READ_OBSERVED carrier=" + observed[0] + " tid=" + observed[1]);
  }

  /** Validation runs inside pinnedRead0, so a virtual-thread migration cannot change the record. */
  private static void assertCleanPinnedReadContext() throws Exception {
    for (String accessor : new String[] {"testGetSpanId", "testGetRootSpanId"}) {
      Method read = JavaProfiler.class.getDeclaredMethod(accessor);
      read.setAccessible(true);
      assertEquals(
          0L,
          read.invoke(JavaProfiler.getInstance()),
          "pinned JNI read requires clean carrier context: " + accessor);
    }
  }

  private static native int[] openPinnedSocket0();

  /** Observes the JDK carrier id and Linux tid before entering an installed native read hook. */
  private static native int pinnedRead0(int fd, long[] observed, CountDownLatch entered);

  private static native int releasePinnedRead0(int fd);

  private static native void closePinnedSocket0(int fd);

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isLinux();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  private static int selectUntilReady(Selector selector, long timeoutMillis) throws Exception {
    long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(timeoutMillis);
    int selected;
    do {
      long remainingNanos = deadline - System.nanoTime();
      if (remainingNanos <= 0L) {
        return 0;
      }
      selected = selector.select(Math.max(1L, TimeUnit.NANOSECONDS.toMillis(remainingNanos)));
    } while (selected == 0);
    return selected;
  }

  protected void assertIoWaitTaskBlockSelfContained(String workerName) {
    assertIoWaitTaskBlockSelfContained(verifyEvents("datadog.TaskBlock", false), workerName);
  }

  private void assertIoWaitTaskBlockSelfContained(JfrEvents taskBlockEvents, String workerName) {
    assertNativeTaskBlockPresent(taskBlockEvents);
    TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
    assertTaskBlockStackReference(taskBlockEvents);
    TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "IO_WAIT");
    assertTrue(
        TaskBlockAssertions.containsObservedStateForEventThread(
            taskBlockEvents, "IO_WAIT", workerName),
        "Expected native IO_WAIT TaskBlock for " + workerName);
  }

  protected void assertTaskBlockStackReference(JfrEvents taskBlockEvents) {
    TaskBlockAssertions.assertContainsStackTrace(taskBlockEvents);
    TaskBlockAssertions.assertContainsJavaType(taskBlockEvents, "NativeSocketTaskBlockTest");
    TaskBlockAssertions.assertNoCorrelationId(taskBlockEvents);
  }

  private void assertNativeTaskBlockPresent(JfrEvents taskBlockEvents) {
    if (!taskBlockEvents.hasItems()) {
      String diagnostic = missingTaskBlockDiagnostic();
      System.out.println(diagnostic);
      assertTrue(false, diagnostic);
    }
  }

  private String missingTaskBlockDiagnostic() {
    return "Expected native socket TaskBlock after "
        + NATIVE_BLOCK_ATTEMPTS
        + " blocked interval(s); emitted="
        + getRecordedCounterValue("task_block_emitted")
        + ", stack_capture_failed="
        + getRecordedCounterValue("task_block_stack_capture_failed")
        + ", skipped_too_short="
        + getRecordedCounterValue("task_block_skipped_too_short")
        + ", skipped_trace_context="
        + getRecordedCounterValue("task_block_skipped_trace_context")
        + ", record_failed="
        + getRecordedCounterValue("task_block_record_failed");
  }

  private static void assertCompleted(Thread thread, AtomicReference<Throwable> error)
      throws InterruptedException {
    thread.join(5_000L);
    assertFalse(thread.isAlive(), thread.getName() + " did not complete");
    if (error.get() != null) {
      throw new AssertionError(error.get());
    }
  }
}
