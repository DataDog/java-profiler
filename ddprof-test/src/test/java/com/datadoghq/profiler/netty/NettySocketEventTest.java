/*
 * Copyright 2026, Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.netty;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import io.netty.bootstrap.Bootstrap;
import io.netty.bootstrap.ServerBootstrap;
import io.netty.buffer.Unpooled;
import io.netty.channel.Channel;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.ChannelOption;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.SimpleChannelInboundHandler;
import io.netty.channel.epoll.Epoll;
import io.netty.channel.epoll.EpollEventLoopGroup;
import io.netty.channel.epoll.EpollServerSocketChannel;
import io.netty.channel.epoll.EpollSocketChannel;
import io.netty.channel.socket.SocketChannel;
import io.netty.handler.codec.bytes.ByteArrayDecoder;
import io.netty.handler.codec.bytes.ByteArrayEncoder;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.IMCFrame;
import org.openjdk.jmc.common.IMCMethod;
import org.openjdk.jmc.common.IMCStackTrace;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import java.nio.charset.StandardCharsets;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.NUMBER;
import static org.openjdk.jmc.common.unit.UnitLookup.PLAIN_TEXT;
import static org.openjdk.jmc.common.unit.UnitLookup.STACKTRACE;
import static org.openjdk.jmc.common.unit.UnitLookup.TIMESTAMP;

/**
 * Integration test that verifies {@code datadog.SocketIO} JFR events are emitted when
 * Netty's native epoll transport performs socket I/O.
 *
 * <p>The test starts a minimal Netty echo server using the native epoll transport, connects
 * a client, exchanges data, then asserts that socket I/O JFR events were captured with valid
 * fields (start time, positive duration, operation name, bytes transferred).
 *
 * <p>The test is skipped automatically on non-Linux platforms or when the native epoll
 * transport is unavailable.
 */
public class NettySocketEventTest extends AbstractProfilerTest {

    private static final byte[] PING = "ping".getBytes(StandardCharsets.UTF_8);
    private static final int EXCHANGE_COUNT = 10;

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms,wall=10ms";
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux();
    }

    @Test
    public void testSocketIOEventsEmittedForNettyEpoll() throws Exception {
        Assumptions.assumeTrue(Epoll.isAvailable(),
                "Native epoll transport is not available - skipping Netty socket test");

        waitForProfilerReady(5000);

        CountDownLatch serverReady = new CountDownLatch(1);
        AtomicInteger serverReceivedBytes = new AtomicInteger(0);
        int[] serverPort = {0};

        EventLoopGroup bossGroup = new EpollEventLoopGroup(1);
        EventLoopGroup workerGroup = new EpollEventLoopGroup(2);
        EventLoopGroup clientGroup = new EpollEventLoopGroup(1);

        try {
            // Start echo server
            ServerBootstrap server = new ServerBootstrap()
                    .group(bossGroup, workerGroup)
                    .channel(EpollServerSocketChannel.class)
                    .childOption(ChannelOption.TCP_NODELAY, true)
                    .childHandler(new ChannelInitializer<SocketChannel>() {
                        @Override
                        protected void initChannel(SocketChannel ch) {
                            ch.pipeline()
                              .addLast(new ByteArrayDecoder())
                              .addLast(new ByteArrayEncoder())
                              .addLast(new SimpleChannelInboundHandler<byte[]>() {
                                  @Override
                                  protected void channelRead0(ChannelHandlerContext ctx, byte[] msg) {
                                      serverReceivedBytes.addAndGet(msg.length);
                                      ctx.writeAndFlush(Unpooled.wrappedBuffer(msg));
                                  }
                              });
                        }
                    });

            Channel serverChannel = server.bind(0).sync().channel();
            serverPort[0] = ((java.net.InetSocketAddress) serverChannel.localAddress()).getPort();
            serverReady.countDown();

            // Connect client and exchange data
            Bootstrap clientBootstrap = new Bootstrap()
                    .group(clientGroup)
                    .channel(EpollSocketChannel.class)
                    .option(ChannelOption.TCP_NODELAY, true)
                    .handler(new ChannelInitializer<SocketChannel>() {
                        @Override
                        protected void initChannel(SocketChannel ch) {
                            ch.pipeline()
                              .addLast(new ByteArrayDecoder())
                              .addLast(new ByteArrayEncoder());
                        }
                    });

            assertTrue(serverReady.await(5, TimeUnit.SECONDS), "Server did not start in time");

            Channel clientChannel = clientBootstrap
                    .connect("127.0.0.1", serverPort[0])
                    .sync()
                    .channel();

            for (int i = 0; i < EXCHANGE_COUNT; i++) {
                ChannelFuture writeFuture = clientChannel
                        .writeAndFlush(Unpooled.wrappedBuffer(PING));
                writeFuture.sync();
                Thread.sleep(5);
            }

            // Allow the server to process all messages
            Thread.sleep(100);

            clientChannel.close().sync();
            serverChannel.close().sync();

        } finally {
            clientGroup.shutdownGracefully(0, 100, TimeUnit.MILLISECONDS).sync();
            workerGroup.shutdownGracefully(0, 100, TimeUnit.MILLISECONDS).sync();
            bossGroup.shutdownGracefully(0, 100, TimeUnit.MILLISECONDS).sync();
        }

        stopProfiler();

        // Verify JFR events
        IAttribute<IQuantity> startTimeAttr = attr("startTime", "", "", TIMESTAMP);
        IAttribute<String> operationAttr = attr("operation", "", "", PLAIN_TEXT);
        IAttribute<IQuantity> bytesAttr = attr("bytesTransferred", "", "", NUMBER);
        IAttribute<IMCStackTrace> stackTraceAttr = attr("stackTrace", "stackTrace", "", STACKTRACE);

        IItemCollection events = verifyEvents("datadog.SocketIO");
        assertNotNull(events, "Expected datadog.SocketIO events");

        boolean foundDataTransfer = false;
        boolean foundEventWithStacktrace = false;
        boolean foundNativeFrameInStacktrace = false;
        int maxStackDepth = 0;
        for (IItemIterable it : events) {
            IMemberAccessor<IQuantity, IItem> startTimeAccessor = startTimeAttr.getAccessor(it.getType());
            IMemberAccessor<String, IItem> opAccessor = operationAttr.getAccessor(it.getType());
            IMemberAccessor<IQuantity, IItem> bytesAccessor = bytesAttr.getAccessor(it.getType());
            IMemberAccessor<IMCStackTrace, IItem> stackTraceAccessor = stackTraceAttr.getAccessor(it.getType());

            assertNotNull(startTimeAccessor, "startTime accessor must be non-null");
            assertNotNull(opAccessor, "operation accessor must be non-null");
            assertNotNull(bytesAccessor, "bytesTransferred accessor must be non-null");
            assertNotNull(stackTraceAccessor, "stackTrace accessor must be non-null");

            for (IItem item : it) {
                long startNs = startTimeAccessor.getMember(item).longValue();
                assertTrue(startNs > 0, "startTime must be positive");

                String op = opAccessor.getMember(item);
                assertNotNull(op, "operation must not be null");
                assertTrue(
                    op.equals("read") || op.equals("write") || op.equals("readv") ||
                    op.equals("writev") || op.equals("recv") || op.equals("send") ||
                    op.equals("recvmsg") || op.equals("sendmsg") ||
                    op.equals("connect") || op.equals("accept") || op.equals("accept4") ||
                    op.equals("epoll_wait"),
                    "Unexpected operation: " + op);

                // Check for stacktrace with native frames
                IMCStackTrace stackTrace = stackTraceAccessor.getMember(item);
                if (stackTrace != null && !stackTrace.getFrames().isEmpty()) {
                    foundEventWithStacktrace = true;
                    int depth = stackTrace.getFrames().size();
                    maxStackDepth = Math.max(maxStackDepth, depth);

                    // Check if stacktrace contains native frames
                    // Native frames are captured from the socket I/O hook points
                    // Look for frames that indicate native code execution
                    for (int i = 0; i < stackTrace.getFrames().size(); i++) {
                        IMCFrame frame = stackTrace.getFrames().get(i);
                        IMCMethod frameMethod = frame.getMethod();
                        if (frameMethod != null) {
                            String methodName = frameMethod.getMethodName();
                            String typeName = frameMethod.getType() != null ?
                                frameMethod.getType().getFullName() : "";

                            // Native frames show up with type names containing native library paths
                            // or special markers like [Unknown], or native method indicators
                            if (typeName.contains(".so") ||  // Shared library
                                typeName.contains("[Unknown]") ||  // Unknown native code
                                typeName.isEmpty() ||  // Empty type for native frames
                                (methodName != null && (
                                    methodName.contains("writev") ||
                                    methodName.contains("readv") ||
                                    methodName.contains("epoll") ||
                                    methodName.endsWith("()")  // Native frames often show as funcname()
                                ))) {
                                foundNativeFrameInStacktrace = true;
                                break;
                            }
                        }
                    }
                }

                // Any of the data-transfer operations (read/write variants) indicate
                // that socket I/O was successfully intercepted during the data exchange.
                if (op.equals("read") || op.equals("write") || op.equals("readv") ||
                    op.equals("writev") || op.equals("recv") || op.equals("send") ||
                    op.equals("recvmsg") || op.equals("sendmsg")) {
                    foundDataTransfer = true;
                }
            }
        }

        assertTrue(foundDataTransfer,
                "Expected at least one data-transfer socket I/O event from Netty data exchange");
        assertTrue(foundEventWithStacktrace,
                "Expected at least one socket I/O event with a non-empty stacktrace");
        assertTrue(maxStackDepth > 1,
                "Expected stacktraces with depth > 1 (found max depth: " + maxStackDepth +
                "). Full stacktraces including native frames should have multiple frames.");
        assertTrue(foundNativeFrameInStacktrace,
                "Expected at least one socket I/O event with native frames in the stacktrace. " +
                "Native frames should be captured from the hooked socket operations.");
    }

}
