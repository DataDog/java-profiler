/*
 * Copyright 2026, Datadog, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.datadoghq.profiler.stresstest.scenarios.throughput;

import com.datadoghq.profiler.JavaProfiler;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.TimeUnit;
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
import org.openjdk.jmh.annotations.Warmup;

/**
 * Measures overhead of the nativesocket PLT write/read hooks on:
 * <ul>
 *   <li><b>fileWrite</b> — write() to a regular file. After the first call the
 *       fd-type cache classifies it as non-socket (one atomic load per subsequent
 *       call). This is the worst-case overhead scenario for code that does heavy
 *       file I/O with nativesocket enabled.
 *   <li><b>socketWrite</b> — write() to a TCP socket (blocking, PlainSocket).
 *   <li><b>nioSocketWrite</b> — write() via NIO SocketChannel (JDK11+ path).
 * </ul>
 *
 * <p>Compare {@code profilerActive=false} vs {@code profilerActive=true} to
 * quantify the hook overhead. Revert if fileWrite throughput degrades > 5%.
 *
 * <p>The profiler uses time-weighted (duration-based) inverse-transform
 * sampling: {@code P(sample) = 1 - exp(-duration_ticks / interval_ticks)}.
 * Slow I/O calls are sampled more often; fast calls are down-sampled.
 *
 * <pre>
 *   ./gradlew :ddprof-stresstest:jmh -PjmhInclude="NativeSocketOverheadBenchmark"
 * </pre>
 */
@BenchmarkMode(Mode.Throughput)
@OutputTimeUnit(TimeUnit.MILLISECONDS)
@Fork(value = 1, warmups = 0)
@Warmup(iterations = 3, time = 2)
@Measurement(iterations = 5, time = 3)
@State(Scope.Thread)
public class NativeSocketOverheadBenchmark {

    private static final int CHUNK = 4096;

    @Param({"false", "true"})
    public boolean profilerActive;

    private Path tmpFile;
    private OutputStream fileOut;

    private ServerSocket server;
    private Socket client;
    private Socket serverConn;
    private OutputStream sockOut;
    private Thread serverAcceptor;

    private ServerSocket nioServer;
    private SocketChannel nioClient;
    private ByteBuffer nioBuf;

    private final byte[] buf = new byte[CHUNK];

    @Setup(Level.Trial)
    public void setup() throws Exception {
        if (profilerActive) {
            JavaProfiler profiler = JavaProfiler.getInstance();
            Path jfr = Files.createTempFile("nativesocket-bench", ".jfr");
            profiler.execute("start,nativesocket,jfr,file=" + jfr.toAbsolutePath());
        }

        // File I/O: regular file, will be classified non-socket after first write
        tmpFile = Files.createTempFile("nativesocket-bench-file", ".bin");
        fileOut = Files.newOutputStream(tmpFile);

        // Blocking TCP socket (PlainSocket / JDK 8 send path)
        server = new ServerSocket(0);
        serverAcceptor = new Thread(() -> {
            try {
                serverConn = server.accept();
                // drain so the client write buffer never fills
                InputStream drain = serverConn.getInputStream();
                byte[] dbuf = new byte[CHUNK];
                while (drain.read(dbuf) != -1) { /* drain */ }
            } catch (IOException ignored) {}
        });
        serverAcceptor.setDaemon(true);
        serverAcceptor.start();
        client  = new Socket("127.0.0.1", server.getLocalPort());
        sockOut = client.getOutputStream();

        // NIO SocketChannel (write(2) path used by JDK 11+)
        nioServer = new ServerSocket(0);
        Thread nioAcceptor = new Thread(() -> {
            try {
                Socket ac = nioServer.accept();
                // drain
                InputStream drain = ac.getInputStream();
                byte[] dbuf = new byte[CHUNK];
                while (drain.read(dbuf) != -1) { /* drain */ }
            } catch (IOException ignored) {}
        });
        nioAcceptor.setDaemon(true);
        nioAcceptor.start();
        nioClient = SocketChannel.open(new InetSocketAddress("127.0.0.1", nioServer.getLocalPort()));
        nioBuf = ByteBuffer.allocate(CHUNK);
    }

    @TearDown(Level.Trial)
    public void teardown() throws Exception {
        if (profilerActive) {
            JavaProfiler.getInstance().execute("stop");
        }
        fileOut.close();
        Files.deleteIfExists(tmpFile);
        client.close();
        if (serverConn != null) serverConn.close();
        server.close();
        nioClient.close();
        nioServer.close();
    }

    /** write() to a regular file — measures fd-type-cache overhead on non-socket fds. */
    @Benchmark
    public void fileWrite() throws IOException {
        fileOut.write(buf);
    }

    /** write() to a blocking TCP socket — the socket sampling path. */
    @Benchmark
    public void socketWrite() throws IOException {
        sockOut.write(buf);
    }

    /** SocketChannel.write() — the NIO path used by JDK 11+ java.net.Socket. */
    @Benchmark
    public long nioSocketWrite() throws IOException {
        nioBuf.clear();
        nioBuf.put(buf);
        nioBuf.flip();
        return nioClient.write(nioBuf);
    }
}
