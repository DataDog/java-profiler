// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler.shutdown;

import static org.junit.jupiter.api.Assertions.fail;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Queue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

public class ShutdownTest {

  /**
   * Engine-mix parameter points for {@link #testShutdown(String)}. Wall-clock-based commands need
   * the current thread registered ({@code addThread()}); cpu-only does not.
   */
  static Stream<Arguments> engineCommands() {
    return Stream.of(
        Arguments.of("start,cpu=10us,filter=0", false),
        Arguments.of("start,wall=10us,filter=0", true),
        Arguments.of("start,cpu=10us,wall=~10us,filter=0", true));
  }

  @ParameterizedTest
  @MethodSource("engineCommands")
  public void testShutdown(String command, boolean registerThread) throws IOException {
    System.out.println("=== testShutdown(" + command + ")");
    JavaProfiler profiler = JavaProfiler.getInstance();
    if (registerThread) {
      profiler.addThread();
    }
    runTest(profiler, command);
  }

  /**
   * Stops the profiler, retrying the documented-retryable "did not drain" outcome per {@link
   * AbstractProfilerTest#stopRetryingOnDrainTimeout}.
   */
  private static void runTest(JavaProfiler profiler, String command) throws IOException {
    Path rootDir = Paths.get("/tmp/recordings");
    Files.createDirectories(rootDir);
    Path jfrDump = Files.createTempFile(rootDir, "shutdown-test", ".jfr");
    String commandWithDump = command + ",jfr,file=" + jfrDump.toAbsolutePath();
    ExecutorService executor = Executors.newSingleThreadExecutor();
    Queue<Throwable> errors = new LinkedBlockingQueue<>();
    try {
      executor
          .submit(
              new Runnable() {
                @Override
                public void run() {
                  for (int i = 0; i < 100; i++) {
                    try {
                      profiler.execute(commandWithDump);
                      try {
                        Thread.sleep(20);
                      } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                      } finally {
                        AbstractProfilerTest.stopRetryingOnDrainTimeout(profiler);
                      }
                    } catch (Throwable error) {
                      errors.offer(error);
                      return;
                    }
                  }
                }
              })
          .get();
    } catch (Throwable t) {
      fail(t.getMessage());
    } finally {
      executor.shutdownNow();
    }
    if (!errors.isEmpty()) {
      fail(errors.poll());
    }
  }
}
