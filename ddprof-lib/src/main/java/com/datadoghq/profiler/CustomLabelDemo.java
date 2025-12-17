package com.datadoghq.profiler;

import java.io.IOException;

public class CustomLabelDemo {
  private static JavaProfiler profiler;
  private static ContextSetter contextSetter;

  public static void main(String... args) throws IOException {
    System.out.println("Test version 4");
    profiler = JavaProfiler.getInstance();
    contextSetter = new ContextSetter(profiler, null);
    for (int i = 0; i < 10; i++) {
      new Thread(new Worker(i)).start();
    }
  }

  private static class Worker implements Runnable {
    private final int index;

    public Worker(int index) {
      this.index = index;
    }

    /* Runs for 30 secs */
    @Override
    public void run() {
      System.out.println("[Thread" + index + "] Writing labels");
      contextSetter.setContextValue("test", "value-"+ index);
      contextSetter.setContextValue("another-test", "another-value-"+ index);
      for (int i = 0; i < 30; i++) {
        System.out.println("[Thread" + index + "] Writing context");
        profiler.setContext(index, index +1000);
        JavaProfiler.dumpContext();
        busyWait();
      }
    }

    private void busyWait() {
      try {
        Thread.sleep(1_000);
      } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
      }
    }
  }
}
