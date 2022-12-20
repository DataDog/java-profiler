package com.datadoghq.profiler.filter;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class ThreadFilterSmokeTest extends AbstractProfilerTest {
  private ExecutorService executorService;

  @BeforeEach
  public void before() {
    executorService = Executors.newCachedThreadPool();
  }

  @AfterEach
  public void after() {
    executorService.shutdownNow();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=~1ms,filter=0";
  }

  @Test
  public void smokeTest() throws Exception {
    doThreadFiltering();
  }

  private void doThreadFiltering() throws Exception {
    Future<?>[] futures = new Future[1000];
    for (int i = 0; i < futures.length; i++) {
      int id = i;
      futures[i] = executorService.submit(() -> {
        int tid = profiler.getNativeThreadId();
        profiler.addThread(tid);
        profiler.setContext(id, 42);
        try {
          Thread.sleep(2);
        } catch(InterruptedException e) {
          Thread.currentThread().interrupt();
        }
        profiler.removeThread(tid);
      });
    }
    for (Future<?> future : futures) {
      future.get();
    }
  }
}
