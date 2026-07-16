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
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Verifies native I/O hooks are fully restored and can be reinstalled across profiler restarts. */
public class NativeSocketTaskBlockLifecycleTest extends AbstractProfilerTest {
    private static final int BLOCK_HOLD_MILLIS = 250;
    private static final int NATIVE_BLOCK_ATTEMPTS = 5;

    @BeforeAll
    static void preloadNativeHelpers() throws Exception {
        if (Platform.isLinux()) {
            NativeIoBlockHelper.blockingPpoll(0);
            try (ServerSocket server = new ServerSocket(0);
                    Socket client = new Socket("127.0.0.1", server.getLocalPort());
                    Socket accepted = server.accept()) {
                // Exercise Java networking before profiler start so the native libraries
                // needed by socket reads are loaded before the initial patch pass.
            }
        }
    }

    @Test
    public void restartWithWallPrecheckDisabledStopsNativeSocketTaskBlocks() throws Exception {
        long enabledBlocker = runNativeIoBlock();
        stopProfiler();
        assertIoWaitTaskBlockPresent(verifyEvents("datadog.TaskBlock", false), enabledBlocker);

        Path disabledRecording = Files.createTempFile(Paths.get("/tmp/recordings"),
                "NativeSocketTaskBlockLifecycleTest_disabled_", ".jfr");
        try {
            profiler.execute("start,wall=1ms,wallscope=all,wallprecheck=false,jfr,file="
                    + disabledRecording.toAbsolutePath());
            runNativeIoBlock();
            profiler.stop();

            IItemCollection disabledTaskBlocks =
                    verifyEvents(disabledRecording, "datadog.TaskBlock", false);
            assertFalse(disabledTaskBlocks.hasItems(),
                    "wallprecheck=false restart must disable native socket TaskBlock emission");
        } finally {
            Files.deleteIfExists(disabledRecording);
        }

        Path reenabledRecording = Files.createTempFile(Paths.get("/tmp/recordings"),
                "NativeSocketTaskBlockLifecycleTest_reenabled_", ".jfr");
        try {
            profiler.execute("start,wall=1ms,wallscope=all,wallprecheck=true,jfr,file="
                    + reenabledRecording.toAbsolutePath());
            long reenabledBlocker = runNativeIoBlock();
            profiler.stop();

            assertIoWaitTaskBlockPresent(verifyEvents(
                    reenabledRecording, "datadog.TaskBlock", false), reenabledBlocker);
        } finally {
            Files.deleteIfExists(reenabledRecording);
        }
    }

    @Test
    public void stopWhileSocketReadIsBlockedCleansUpAndAllowsReinstall() throws Exception {
        String workerName = "taskblock-native-stop-inflight";
        CountDownLatch readAttempted = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();
        ServerSocket server = new ServerSocket(0);
        Socket accepted = null;
        boolean stopped = false;

        Thread reader = new Thread(() -> {
            try (Socket socket = new Socket("127.0.0.1", server.getLocalPort())) {
                InputStream input = socket.getInputStream();
                readAttempted.countDown();
                input.read();
            } catch (Throwable t) {
                error.set(t);
            }
        }, workerName);

        try {
            reader.start();
            accepted = server.accept();
            assertTrue(readAttempted.await(5, TimeUnit.SECONDS),
                    "reader did not attempt the blocking socket read");
            Thread.sleep(BLOCK_HOLD_MILLIS);
            assertTrue(reader.isAlive(),
                    "socket read returned before the profiler was stopped");

            stopProfiler();
            stopped = true;
            assertTrue(reader.isAlive(),
                    "socket read returned before profiler shutdown completed");
        } finally {
            if (!stopped) {
                stopProfiler();
            }
            if (accepted != null) {
                accepted.close();
            }
            server.close();
            reader.join(5_000L);
        }

        assertFalse(reader.isAlive(), "blocked socket reader did not terminate");
        if (error.get() != null) {
            throw new AssertionError(error.get());
        }
        assertFalse(TaskBlockAssertions.containsObservedStateForEventThread(
                        verifyEvents("datadog.TaskBlock", false), "IO_WAIT", workerName),
                "a native I/O operation returning after stop must not emit TaskBlock");

        Path restartedRecording = Files.createTempFile(Paths.get("/tmp/recordings"),
                "NativeSocketTaskBlockLifecycleTest_inflight_restart_", ".jfr");
        boolean restarted = false;
        try {
            profiler.execute("start,wall=1ms,wallscope=all,wallprecheck=true,jfr,file="
                    + restartedRecording.toAbsolutePath());
            restarted = true;
            String restartedWorkerName = "taskblock-native-stop-reinstalled";
            for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
                runCompletedSocketRead(restartedWorkerName);
            }
            profiler.stop();
            restarted = false;

            IItemCollection restartedTaskBlocks =
                    verifyEvents(restartedRecording, "datadog.TaskBlock", false);
            TaskBlockAssertions.assertNoAnchorFields(restartedTaskBlocks);
            TaskBlockAssertions.assertContainsStackTrace(restartedTaskBlocks);
            TaskBlockAssertions.assertContainsJavaType(
                    restartedTaskBlocks, "NativeSocketTaskBlockLifecycleTest");
            assertTrue(TaskBlockAssertions.containsObservedStateForEventThread(
                            restartedTaskBlocks, "IO_WAIT", restartedWorkerName),
                    "socket TaskBlock hooks were not reinstalled after profiler shutdown");
        } finally {
            if (restarted) {
                profiler.stop();
            }
            Files.deleteIfExists(restartedRecording);
        }
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux();
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,wallscope=all,wallprecheck=true";
    }

    private void assertIoWaitTaskBlockPresent(IItemCollection taskBlockEvents, long expectedBlocker) {
        assertTrue(expectedBlocker != 0L, "native lifecycle helper must report the expected blocker");
        if (!taskBlockEvents.hasItems()) {
            assertTrue(false, missingTaskBlockDiagnostic());
        }
        TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
        TaskBlockAssertions.assertContainsStackTrace(taskBlockEvents);
        TaskBlockAssertions.assertContainsJavaType(
                taskBlockEvents, "NativeSocketTaskBlockLifecycleTest");
        TaskBlockAssertions.assertNoCorrelationId(taskBlockEvents);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "IO_WAIT");
        assertTrue(TaskBlockAssertions.containsBlocker(taskBlockEvents, expectedBlocker),
                "Expected native blocker " + expectedBlocker);
    }

    private long runNativeIoBlock() throws InterruptedException {
        AtomicLong blocker = new AtomicLong();
        AtomicReference<Throwable> error = new AtomicReference<>();
        Thread worker = new Thread(() -> {
            try {
                for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
                    blocker.set(NativeIoBlockHelper.blockingPpoll(BLOCK_HOLD_MILLIS));
                }
            } catch (Throwable t) {
                error.set(t);
            }
        }, "taskblock-native-lifecycle-helper");
        worker.start();
        worker.join(5_000L);
        assertFalse(worker.isAlive(), "native lifecycle helper did not complete");
        if (error.get() != null) {
            throw new AssertionError(error.get());
        }
        return blocker.get();
    }

    private void runCompletedSocketRead(String workerName) throws Exception {
        CountDownLatch readAttempted = new CountDownLatch(1);
        AtomicReference<Throwable> error = new AtomicReference<>();

        try (ServerSocket server = new ServerSocket(0)) {
            Thread reader = new Thread(() -> {
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
            }, workerName);

            reader.start();
            try (Socket accepted = server.accept()) {
                assertTrue(readAttempted.await(5, TimeUnit.SECONDS),
                        "reader did not attempt the blocking socket read");
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

    private String missingTaskBlockDiagnostic() {
        return "Expected lifecycle native TaskBlock after " + NATIVE_BLOCK_ATTEMPTS
                + " blocked interval(s); emitted=" + getRecordedCounterValue("task_block_emitted")
                + ", stack_capture_failed="
                + getRecordedCounterValue("task_block_stack_capture_failed")
                + ", skipped_too_short=" + getRecordedCounterValue("task_block_skipped_too_short")
                + ", skipped_trace_context="
                + getRecordedCounterValue("task_block_skipped_trace_context")
                + ", record_failed=" + getRecordedCounterValue("task_block_record_failed");
    }
}
