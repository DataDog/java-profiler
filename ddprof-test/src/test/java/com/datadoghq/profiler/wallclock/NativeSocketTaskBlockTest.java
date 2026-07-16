/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import java.io.InputStream;
import java.io.OutputStream;
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
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Verifies Linux native socket and readiness waits produce self-contained TaskBlock events. */
public class NativeSocketTaskBlockTest extends AbstractProfilerTest {
    private static final int BLOCK_HOLD_MILLIS = 250;
    private static final int NATIVE_BLOCK_ATTEMPTS = 5;

    @BeforeAll
    static void preloadNativeHelper() {
        if (Platform.isLinux()) {
            NativeIoBlockHelper.blockingPpoll(0);
        }
    }

    @Test
    public void blockingSocketReadEmitsIoWaitTaskBlock() throws Exception {
        for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
            runBlockingSocketReadOnce();
        }

        stopProfiler();
        assertIoWaitTaskBlockSelfContained();
    }

    private void runBlockingSocketReadOnce() throws Exception {
        CountDownLatch readAttempted = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();

        try (ServerSocket server = new ServerSocket(0)) {
            Thread reader = new Thread(() -> {
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
            }, "taskblock-native-socket-read");

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
        assertIoWaitTaskBlockSelfContained();
    }

    private void runBlockingServerSocketAcceptOnce() throws Exception {
        CountDownLatch acceptAttempted = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();
        InetAddress loopback = InetAddress.getLoopbackAddress();

        try (ServerSocket server = new ServerSocket(0, 1, loopback)) {
            Thread accepter = new Thread(() -> {
                try {
                    acceptAttempted.countDown();
                    try (Socket accepted = server.accept()) {
                        assertTrue(accepted.isConnected());
                    }
                } catch (Throwable t) {
                    error.set(t);
                }
            }, "taskblock-native-socket-accept");

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
        assertIoWaitTaskBlockSelfContained();
    }

    private void runBlockingDatagramReceiveOnce() throws Exception {
        CountDownLatch receiveAttempted = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();
        InetAddress loopback = InetAddress.getLoopbackAddress();

        try (DatagramSocket receiver = new DatagramSocket(new InetSocketAddress(loopback, 0))) {
            Thread receiverThread = new Thread(() -> {
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
            }, "taskblock-native-datagram-receive");

            receiverThread.start();
            assertTrue(receiveAttempted.await(5, TimeUnit.SECONDS), "receive did not start");
            Thread.sleep(BLOCK_HOLD_MILLIS);
            try (DatagramSocket sender = new DatagramSocket()) {
                byte[] data = new byte[]{7};
                DatagramPacket packet = new DatagramPacket(
                        data, data.length, loopback, receiver.getLocalPort());
                sender.send(packet);
            }
            assertCompleted(receiverThread, error);
        }
    }

    @Test
    public void blockingSelectorSelectEmitsIoWaitTaskBlock() throws Exception {
        for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
            runBlockingSelectorSelectOnce();
        }

        stopProfiler();
        assertIoWaitTaskBlockSelfContained();
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

            Thread selectorThread = new Thread(() -> {
                try {
                    selectAttempted.countDown();
                    int selected = selectUntilReady(selector, 5_000L);
                    assertTrue(selected > 0, "selector did not observe pipe readiness");
                    selector.selectedKeys().clear();
                    ByteBuffer data = ByteBuffer.allocate(1);
                    while (data.hasRemaining() && source.read(data) > 0) {
                    }
                } catch (Throwable t) {
                    error.set(t);
                }
            }, "taskblock-native-selector-select");

            selectorThread.start();
            assertTrue(selectAttempted.await(5, TimeUnit.SECONDS), "select did not start");
            Thread.sleep(BLOCK_HOLD_MILLIS);
            sink.write(ByteBuffer.wrap(new byte[]{1}));
            assertCompleted(selectorThread, error);
        }
    }

    @Test
    public void blockingAccept4EmitsIoWaitTaskBlock() {
        long expectedBlocker =
                runNativeIoBlockRepeated(() -> NativeIoBlockHelper.blockingAccept4(BLOCK_HOLD_MILLIS));
        stopProfiler();
        assertNativeIoHelperCompleted(expectedBlocker);
    }

    @Test
    public void blockingPpollEmitsIoWaitTaskBlock() {
        long expectedBlocker =
                runNativeIoBlockRepeated(() -> NativeIoBlockHelper.blockingPpoll(BLOCK_HOLD_MILLIS));
        stopProfiler();
        assertNativeIoHelperCompleted(expectedBlocker);
    }

    @Test
    public void ownedNativeIoSuppressesWallSignalsBeforeCompletion() throws Exception {
        long before = profiler.getDebugCounters()
                .getOrDefault("wc_signals_suppressed_owned_block", 0L);
        AtomicLong blocker = new AtomicLong();
        AtomicReference<Throwable> error = new AtomicReference<>();
        Thread worker = new Thread(() -> {
            try {
                blocker.set(NativeIoBlockHelper.blockingPpoll(BLOCK_HOLD_MILLIS));
            } catch (Throwable t) {
                error.set(t);
            }
        }, "taskblock-native-suppression");

        worker.start();
        waitForCounterAbove("wc_signals_suppressed_owned_block", before, 5_000L);
        assertCompleted(worker, error);

        stopProfiler();
        assertNativeIoHelperCompleted(blocker.get());
    }

    @Test
    public void blockingPselectEmitsIoWaitTaskBlock() {
        long expectedBlocker =
                runNativeIoBlockRepeated(() -> NativeIoBlockHelper.blockingPselect(BLOCK_HOLD_MILLIS));
        stopProfiler();
        assertNativeIoHelperCompleted(expectedBlocker);
    }

    @Test
    public void blockingEpollWaitEmitsIoWaitTaskBlock() {
        long expectedBlocker =
                runNativeIoBlockRepeated(() -> NativeIoBlockHelper.blockingEpollWait(BLOCK_HOLD_MILLIS));
        stopProfiler();
        assertNativeIoHelperCompleted(expectedBlocker);
    }

    @Test
    public void blockingEpollPwaitEmitsIoWaitTaskBlock() {
        long expectedBlocker =
                runNativeIoBlockRepeated(() -> NativeIoBlockHelper.blockingEpollPwait(BLOCK_HOLD_MILLIS));
        stopProfiler();
        assertNativeIoHelperCompleted(expectedBlocker);
    }

    @Test
    public void tracedBlockingSocketReadDoesNotEmitTaskBlock() throws Exception {
        CountDownLatch readAttempted = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();

        try (ServerSocket server = new ServerSocket(0)) {
            Thread reader = new Thread(() -> {
                try {
                    profiler.setContext(0x5100L, 0x5101L, 0L, 0x5101L);
                    try (Socket socket = new Socket("127.0.0.1", server.getLocalPort())) {
                        InputStream input = socket.getInputStream();
                        readAttempted.countDown();
                        int value = input.read();
                        if (value != 1) {
                            throw new AssertionError("unexpected socket byte: " + value);
                        }
                    } finally {
                        profiler.clearContext();
                    }
                } catch (Throwable t) {
                    error.set(t);
                }
            }, "taskblock-traced-native-socket-read");

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

        stopProfiler();
        assertFalse(
                TaskBlockAssertions.containsSpan(verifyEvents("datadog.TaskBlock", false), 0x5101L),
                "Traced socket I/O must keep MethodSample wall-clock data instead of emitting TaskBlock");
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux();
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,wallscope=all,wallprecheck=true";
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

    protected void assertIoWaitTaskBlockSelfContained() {
        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock", false);
        assertNativeTaskBlockPresent(taskBlockEvents);
        TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
        assertTaskBlockStackReference(taskBlockEvents);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "IO_WAIT");
    }

    protected void assertIoWaitTaskBlockSelfContained(long expectedBlocker) {
        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock", false);
        assertNativeTaskBlockPresent(taskBlockEvents);
        TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
        assertTaskBlockStackReference(taskBlockEvents);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "IO_WAIT");
        assertTrue(TaskBlockAssertions.containsBlocker(taskBlockEvents, expectedBlocker),
                "Expected native blocker " + expectedBlocker);
    }

    private void assertNativeIoHelperCompleted(long expectedBlocker) {
        assertTrue(expectedBlocker != 0L, "native I/O helper must report the expected blocker");
        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock", false);
        assertNativeTaskBlockPresent(taskBlockEvents);
        TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
        assertTaskBlockStackReference(taskBlockEvents);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "IO_WAIT");
        assertTrue(TaskBlockAssertions.containsBlocker(taskBlockEvents, expectedBlocker),
                "Expected native blocker " + expectedBlocker);
    }

    protected void assertTaskBlockStackReference(IItemCollection taskBlockEvents) {
        TaskBlockAssertions.assertContainsStackTrace(taskBlockEvents);
        TaskBlockAssertions.assertContainsJavaType(taskBlockEvents, "NativeSocketTaskBlockTest");
        TaskBlockAssertions.assertNoCorrelationId(taskBlockEvents);
    }

    private long runNativeIoBlockRepeated(NativeIoBlockWorkload workload) {
        AtomicLong blocker = new AtomicLong();
        AtomicReference<Throwable> error = new AtomicReference<>();
        Thread worker = new Thread(() -> {
            try {
                for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
                    blocker.set(workload.run());
                }
            } catch (Throwable t) {
                error.set(t);
            }
        }, "taskblock-native-helper");
        worker.start();
        try {
            worker.join(5_000L);
        } catch (InterruptedException interrupted) {
            Thread.currentThread().interrupt();
            throw new AssertionError("interrupted while waiting for native helper", interrupted);
        }
        assertFalse(worker.isAlive(), "native helper did not complete");
        if (error.get() != null) {
            throw new AssertionError(error.get());
        }
        return blocker.get();
    }

    private void assertNativeTaskBlockPresent(IItemCollection taskBlockEvents) {
        if (!taskBlockEvents.hasItems()) {
            String diagnostic = missingTaskBlockDiagnostic();
            System.out.println(diagnostic);
            assertTrue(false, diagnostic);
        }
    }

    private String missingTaskBlockDiagnostic() {
        return "Expected native socket TaskBlock after " + NATIVE_BLOCK_ATTEMPTS
                + " blocked interval(s); emitted=" + getRecordedCounterValue("task_block_emitted")
                + ", stack_capture_failed="
                + getRecordedCounterValue("task_block_stack_capture_failed")
                + ", skipped_too_short=" + getRecordedCounterValue("task_block_skipped_too_short")
                + ", skipped_trace_context="
                + getRecordedCounterValue("task_block_skipped_trace_context")
                + ", record_failed=" + getRecordedCounterValue("task_block_record_failed");
    }

    private void waitForCounterAbove(String name, long baseline, long timeoutMillis)
            throws Exception {
        long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(timeoutMillis);
        while (System.nanoTime() < deadline) {
            if (profiler.getDebugCounters().getOrDefault(name, 0L) > baseline) {
                return;
            }
            Thread.sleep(10L);
        }
        throw new AssertionError("Counter did not increase: " + name);
    }

    @FunctionalInterface
    private interface NativeIoBlockWorkload {
        long run();
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
