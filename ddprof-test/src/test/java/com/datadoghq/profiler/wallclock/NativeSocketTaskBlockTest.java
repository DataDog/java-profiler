package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
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
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class NativeSocketTaskBlockTest extends AbstractProfilerTest {
    @Test
    public void blockingSocketReadEmitsIoWaitTaskBlock() throws Exception {
        CountDownLatch readAttempted = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();

        try (ServerSocket server = new ServerSocket(0)) {
            Thread reader = new Thread(() -> {
                try {
                    registerCurrentThreadForWallClockProfiling();
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
                Thread.sleep(80L);
                OutputStream output = accepted.getOutputStream();
                output.write(1);
                output.flush();
            }
            assertCompleted(reader, error);
        }

        stopProfiler();
        assertIoWaitTaskBlockSelfContained();
    }

    @Test
    public void blockingServerSocketAcceptEmitsIoWaitTaskBlock() throws Exception {
        CountDownLatch acceptAttempted = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();
        InetAddress loopback = InetAddress.getLoopbackAddress();

        try (ServerSocket server = new ServerSocket(0, 1, loopback)) {
            Thread accepter = new Thread(() -> {
                try {
                    registerCurrentThreadForWallClockProfiling();
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
            Thread.sleep(80L);
            try (Socket ignored = new Socket(loopback, server.getLocalPort())) {
                assertTrue(ignored.isConnected());
            }
            assertCompleted(accepter, error);
        }

        stopProfiler();
        assertIoWaitTaskBlockSelfContained();
    }

    @Test
    public void blockingDatagramReceiveEmitsIoWaitTaskBlock() throws Exception {
        CountDownLatch receiveAttempted = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();
        InetAddress loopback = InetAddress.getLoopbackAddress();

        try (DatagramSocket receiver = new DatagramSocket(new InetSocketAddress(loopback, 0))) {
            Thread receiverThread = new Thread(() -> {
                try {
                    registerCurrentThreadForWallClockProfiling();
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
            Thread.sleep(80L);
            try (DatagramSocket sender = new DatagramSocket()) {
                byte[] data = new byte[]{7};
                DatagramPacket packet = new DatagramPacket(
                        data, data.length, loopback, receiver.getLocalPort());
                sender.send(packet);
            }
            assertCompleted(receiverThread, error);
        }

        stopProfiler();
        assertIoWaitTaskBlockSelfContained();
    }

    @Test
    public void blockingSelectorSelectEmitsIoWaitTaskBlock() throws Exception {
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
                    registerCurrentThreadForWallClockProfiling();
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
            Thread.sleep(80L);
            sink.write(ByteBuffer.wrap(new byte[]{1}));
            assertCompleted(selectorThread, error);
        }

        stopProfiler();
        assertIoWaitTaskBlockSelfContained();
    }

    @Test
    public void tracedBlockingSocketReadDoesNotEmitTaskBlock() throws Exception {
        CountDownLatch readAttempted = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();

        try (ServerSocket server = new ServerSocket(0)) {
            Thread reader = new Thread(() -> {
                try {
                    registerCurrentThreadForWallClockProfiling();
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
                Thread.sleep(80L);
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
        return Platform.isLinux() && !Platform.isJ9() && !Platform.isZing();
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true";
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

    private void assertIoWaitTaskBlockSelfContained() {
        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock");
        TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
        TaskBlockAssertions.assertContainsStackTrace(taskBlockEvents);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "IO_WAIT");
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
