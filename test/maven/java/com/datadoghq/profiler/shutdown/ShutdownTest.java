package com.datadoghq.profiler.shutdown;

import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Queue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

import com.datadoghq.profiler.JavaProfiler;

import static com.datadoghq.profiler.AbstractProfilerTest.getJavaProfilerLib;
import static org.junit.jupiter.api.Assertions.fail;

public class ShutdownTest {


  @Test
  public void testShutdownCpu() throws IOException {
    System.out.println("=== testShutdownCpu()");
    JavaProfiler profiler = JavaProfiler.getInstance(getJavaProfilerLib());
    runTest(profiler, "start,cpu=10us,filter=0");
  }

  @Test
  public void testShutdownWall() throws IOException {
    System.out.println("=== testShutdownWall()");
    JavaProfiler profiler = JavaProfiler.getInstance(getJavaProfilerLib());
    profiler.addThread(profiler.getNativeThreadId());
    runTest(profiler, "start,wall=10us,filter=0");
  }

  @Test
  public void testShutdownCpuAndWall() throws IOException {
    System.out.println("=== testShutdownCpuAndWall()");
    JavaProfiler profiler = JavaProfiler.getInstance(getJavaProfilerLib());
    profiler.addThread(profiler.getNativeThreadId());
    runTest(profiler, "start,cpu=10us,wall=~10us,filter=0");
  }

  private static void runTest(JavaProfiler profiler, String command) throws IOException {
    Path jfrDump = Files.createTempFile("filter-test", ".jfr");
    String commandWithDump = command + ",jfr,file=" + jfrDump.toAbsolutePath();
    ExecutorService executor = Executors.newSingleThreadExecutor();
    Queue<Throwable> errors = new LinkedBlockingQueue<>();
    try {
      executor.submit(new Runnable() {
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
                profiler.stop();
              }
            } catch (Throwable error) {
              errors.offer(error);
              return;
            }
          }
        }
      }).get();
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
