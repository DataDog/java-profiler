package com.datadoghq.profiler.stresstest.scenarios.throughput;

import com.datadoghq.profiler.JavaProfiler;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.Fork;
import org.openjdk.jmh.annotations.Level;
import org.openjdk.jmh.annotations.Measurement;
import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.TearDown;
import org.openjdk.jmh.annotations.Threads;
import org.openjdk.jmh.annotations.Warmup;

import java.io.FileInputStream;
import java.io.IOException;
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
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;

@State(Scope.Benchmark)
public class NativeSocketIoBenchmark {
    @Param({"none", "wall=1s,filter=0", "wall=1s,filter=0,wallprecheck=true"})
    public String command;

    private JavaProfiler profiler;
    private Path jfr;
    private InetAddress loopback;
    private ServerSocket serverSocket;
    private Socket clientSocket;
    private Socket serverSideSocket;
    private InputStream clientInput;
    private OutputStream clientOutput;
    private InputStream serverInput;
    private OutputStream serverOutput;
    private Path file;
    private FileInputStream fileInput;
    private ServerSocket connectServerSocket;
    private volatile boolean connectAcceptorRunning;
    private Thread connectAcceptorThread;
    private ServerSocket acceptServerSocket;
    private volatile boolean acceptConnectorRunning;
    private Thread acceptConnectorThread;
    private DatagramSocket udpReceiverSocket;
    private DatagramSocket udpSenderSocket;
    private byte[] udpReceiveBuffer;
    private byte[] udpSendBuffer;
    private DatagramPacket udpReceivePacket;
    private DatagramPacket udpSendPacket;
    private Selector selector;
    private Pipe selectorPipe;
    private ByteBuffer selectorWriteBuffer;
    private ByteBuffer selectorReadBuffer;
    private final AtomicReference<Throwable> backgroundError = new AtomicReference<>();

    @Setup(Level.Trial)
    public void setup() throws IOException {
        backgroundError.set(null);
        if (!"none".equals(command)) {
            profiler = JavaProfiler.getInstance();
            jfr = Files.createTempFile("native-socket-io-benchmark", ".jfr");
            profiler.execute("start," + command + ",jfr,file=" + jfr.toAbsolutePath());
            profiler.addThread();
        }

        loopback = InetAddress.getLoopbackAddress();

        serverSocket = new ServerSocket(0, 1, loopback);
        clientSocket = new Socket(loopback, serverSocket.getLocalPort());
        serverSideSocket = serverSocket.accept();
        clientSocket.setTcpNoDelay(true);
        serverSideSocket.setTcpNoDelay(true);
        clientInput = clientSocket.getInputStream();
        clientOutput = clientSocket.getOutputStream();
        serverInput = serverSideSocket.getInputStream();
        serverOutput = serverSideSocket.getOutputStream();

        file = Files.createTempFile("native-socket-io-benchmark", ".bin");
        byte[] data = new byte[1024 * 1024];
        Files.write(file, data);
        fileInput = new FileInputStream(file.toFile());

        connectServerSocket = new ServerSocket(0, 50, loopback);
        connectAcceptorRunning = true;
        connectAcceptorThread = new Thread(this::acceptConnectBenchmarkSockets,
                "native-io-connect-acceptor");
        connectAcceptorThread.setDaemon(true);
        connectAcceptorThread.start();

        acceptServerSocket = new ServerSocket(0, 50, loopback);
        acceptConnectorRunning = true;
        acceptConnectorThread = new Thread(this::connectAcceptBenchmarkSockets,
                "native-io-accept-connector");
        acceptConnectorThread.setDaemon(true);
        acceptConnectorThread.start();

        udpReceiverSocket = new DatagramSocket(new InetSocketAddress(loopback, 0));
        udpSenderSocket = new DatagramSocket();
        udpReceiveBuffer = new byte[64];
        udpSendBuffer = new byte[]{1};
        udpReceivePacket = new DatagramPacket(udpReceiveBuffer, udpReceiveBuffer.length);
        udpSendPacket = new DatagramPacket(
                udpSendBuffer, udpSendBuffer.length, loopback, udpReceiverSocket.getLocalPort());

        selector = Selector.open();
        selectorPipe = Pipe.open();
        selectorPipe.source().configureBlocking(false);
        selectorPipe.source().register(selector, SelectionKey.OP_READ);
        selectorWriteBuffer = ByteBuffer.allocate(1);
        selectorReadBuffer = ByteBuffer.allocate(64);
    }

    @TearDown(Level.Trial)
    public void tearDown() throws IOException {
        connectAcceptorRunning = false;
        acceptConnectorRunning = false;
        closeQuietly(connectServerSocket);
        closeQuietly(acceptServerSocket);
        joinQuietly(connectAcceptorThread);
        joinQuietly(acceptConnectorThread);
        closeQuietly(udpReceiverSocket);
        closeQuietly(udpSenderSocket);
        closeQuietly(selector);
        if (selectorPipe != null) {
            closeQuietly(selectorPipe.source());
            closeQuietly(selectorPipe.sink());
        }
        closeQuietly(fileInput);
        closeQuietly(clientSocket);
        closeQuietly(serverSideSocket);
        closeQuietly(serverSocket);
        if (file != null) {
            Files.deleteIfExists(file);
        }
        if (profiler != null) {
            profiler.execute("stop");
        }
        if (jfr != null) {
            Files.deleteIfExists(jfr);
        }
    }

    @Benchmark
    @BenchmarkMode(Mode.AverageTime)
    @Fork(value = 1, warmups = 1)
    @Warmup(iterations = 3)
    @Measurement(iterations = 5)
    @Threads(1)
    @OutputTimeUnit(TimeUnit.NANOSECONDS)
    public int socketRoundTrip() throws IOException {
        clientOutput.write(1);
        clientOutput.flush();
        int value = serverInput.read();
        serverOutput.write(value);
        serverOutput.flush();
        return clientInput.read();
    }

    @Benchmark
    @BenchmarkMode(Mode.AverageTime)
    @Fork(value = 1, warmups = 1)
    @Warmup(iterations = 3)
    @Measurement(iterations = 5)
    @Threads(1)
    @OutputTimeUnit(TimeUnit.NANOSECONDS)
    public int connectClose() throws IOException {
        assertBackgroundHealthy();
        try (Socket socket = new Socket()) {
            socket.connect(new InetSocketAddress(loopback, connectServerSocket.getLocalPort()));
            return socket.getLocalPort();
        }
    }

    @Benchmark
    @BenchmarkMode(Mode.AverageTime)
    @Fork(value = 1, warmups = 1)
    @Warmup(iterations = 3)
    @Measurement(iterations = 5)
    @Threads(1)
    @OutputTimeUnit(TimeUnit.NANOSECONDS)
    public int acceptClose() throws IOException {
        assertBackgroundHealthy();
        try (Socket accepted = acceptServerSocket.accept()) {
            return accepted.getPort();
        }
    }

    @Benchmark
    @BenchmarkMode(Mode.AverageTime)
    @Fork(value = 1, warmups = 1)
    @Warmup(iterations = 3)
    @Measurement(iterations = 5)
    @Threads(1)
    @OutputTimeUnit(TimeUnit.NANOSECONDS)
    public int datagramReceive() throws IOException {
        udpSendBuffer[0]++;
        udpSenderSocket.send(udpSendPacket);
        udpReceivePacket.setLength(udpReceiveBuffer.length);
        udpReceiverSocket.receive(udpReceivePacket);
        return udpReceivePacket.getLength();
    }

    @Benchmark
    @BenchmarkMode(Mode.AverageTime)
    @Fork(value = 1, warmups = 1)
    @Warmup(iterations = 3)
    @Measurement(iterations = 5)
    @Threads(1)
    @OutputTimeUnit(TimeUnit.NANOSECONDS)
    public int selectorSelect() throws IOException {
        selectorWriteBuffer.clear();
        selectorWriteBuffer.put((byte) 1);
        selectorWriteBuffer.flip();
        while (selectorWriteBuffer.hasRemaining()) {
            selectorPipe.sink().write(selectorWriteBuffer);
        }
        int selected = selector.select(1_000L);
        selector.selectedKeys().clear();
        selectorReadBuffer.clear();
        while (selectorPipe.source().read(selectorReadBuffer) > 0) {
            selectorReadBuffer.clear();
        }
        return selected;
    }

    @Benchmark
    @BenchmarkMode(Mode.AverageTime)
    @Fork(value = 1, warmups = 1)
    @Warmup(iterations = 3)
    @Measurement(iterations = 5)
    @Threads(1)
    @OutputTimeUnit(TimeUnit.NANOSECONDS)
    public int regularFileRead() throws IOException {
        int value = fileInput.read();
        if (value >= 0) {
            return value;
        }
        fileInput.close();
        fileInput = new FileInputStream(file.toFile());
        return fileInput.read();
    }

    private void acceptConnectBenchmarkSockets() {
        while (connectAcceptorRunning) {
            try (Socket ignored = connectServerSocket.accept()) {
            } catch (IOException e) {
                if (connectAcceptorRunning) {
                    backgroundError.compareAndSet(null, e);
                }
            }
        }
    }

    private void connectAcceptBenchmarkSockets() {
        while (acceptConnectorRunning) {
            try (Socket ignored = new Socket(loopback, acceptServerSocket.getLocalPort())) {
            } catch (IOException e) {
                if (acceptConnectorRunning) {
                    backgroundError.compareAndSet(null, e);
                }
            }
        }
    }

    private void assertBackgroundHealthy() throws IOException {
        Throwable failure = backgroundError.get();
        if (failure == null) {
            return;
        }
        if (failure instanceof IOException) {
            throw (IOException) failure;
        }
        throw new IOException(failure);
    }

    private static void closeQuietly(AutoCloseable closeable) {
        if (closeable == null) {
            return;
        }
        try {
            closeable.close();
        } catch (Exception ignored) {
        }
    }

    private static void joinQuietly(Thread thread) {
        if (thread == null) {
            return;
        }
        try {
            thread.join(1_000L);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
