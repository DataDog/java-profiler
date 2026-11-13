/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.queue;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import java.lang.reflect.Method;
import java.util.concurrent.ArrayBlockingQueue;
import org.junit.jupiter.api.Test;

public class QueueTimeTest extends AbstractProfilerTest {
  @Override
  protected String getProfilerCommand() {
    return "cpu=10ms";
  }

  private static final class Task implements Runnable {

    private final JavaProfiler profiler;
    private final long start;
    private final Thread origin;

    private Task(JavaProfiler profiler) {
      this.profiler = profiler;
      this.start = profiler.getCurrentTicks();
      this.origin = Thread.currentThread();
    }

    @Override
    public void run() {
      profiler.setTraceContext(2, 1, 0, 1, -1, null, -1, null);
      long now = profiler.getCurrentTicks();
      if (profiler.isThresholdExceeded(9, start, now)) {
        profiler.recordQueueTime(
            start, now, getClass(), QueueTimeTest.class, ArrayBlockingQueue.class, 10, origin);
      }
      profiler.clearTraceContext();
    }
  }

  @Test
  public void testRecordQueueTime() throws Exception {
    Thread origin = Thread.currentThread();
    origin.setName("origin");
    Task task = new Task(profiler);
    Thread thread = new Thread(task, "destination");
    Thread.sleep(10);
    thread.start();
    thread.join();
    stopProfiler();

    JfrEvents activeSettings = verifyEvents("jdk.ActiveSetting");
    for (JfrEvent item : activeSettings) {
      String name = item.getString("name");
      if ("tscfrequency".equals(name)) {
        String frequency = item.getString("value");
        assertTrue(Long.valueOf(frequency) > 0, frequency);
      }
    }

    JfrEvents events = verifyEvents("datadog.QueueTime");
    for (JfrEvent item : events) {
      assertTrue(item.getLong("startTime") > 0);
      // startTime/duration are TICKS-annotated so jafar auto-converts them to
      // epoch nanos / duration nanos respectively.
      long durationMillis = item.getLong("duration") / 1_000_000;
      assertTrue(durationMillis >= 9);
      assertEquals(task.getClass().getName(), item.getClassName("task"));
      assertEquals(getClass().getName(), item.getClassName("scheduler"));
      assertEquals(1, item.getLong(SPAN_ID));
      assertEquals(2, item.getLong(LOCAL_ROOT_SPAN_ID));
      assertEquals("origin", item.getThreadName("origin"));
      assertEquals(ArrayBlockingQueue.class.getName(), item.getClassName("queueType"));
      assertEquals(10, item.getLong("queueLength"));
    }
  }

  /**
   * recordQueueTime() dereferences its classes, so only a direct native call can pass a null name.
   * Each null name drops the event; the queue length tells the calls apart.
   */
  @Test
  public void testNullNamesDropQueueTimeEvent() throws Exception {
    Method recordQueueEnd0 =
        JavaProfiler.class.getDeclaredMethod(
            "recordQueueEnd0",
            long.class,
            long.class,
            String.class,
            String.class,
            Thread.class,
            String.class,
            int.class);
    recordQueueEnd0.setAccessible(true);
    Thread origin = Thread.currentThread();
    String task = Runnable.class.getName();
    String scheduler = getClass().getName();
    String queueType = ArrayBlockingQueue.class.getName();
    long end = profiler.getCurrentTicks();
    long start = end - 1000;

    recordQueueEnd0.invoke(null, start, end, null, scheduler, origin, queueType, 101);
    recordQueueEnd0.invoke(null, start, end, task, null, origin, queueType, 102);
    recordQueueEnd0.invoke(null, start, end, task, scheduler, origin, null, 103);
    recordQueueEnd0.invoke(null, start, end, task, scheduler, origin, queueType, 104);
    stopProfiler();

    int recorded = 0;
    for (JfrEvent item : verifyEvents("datadog.QueueTime")) {
      long queueLength = item.getLong("queueLength");
      if (queueLength >= 101 && queueLength <= 103) {
        fail("event with a null name was recorded (queueLength " + queueLength + ")");
      }
      if (queueLength == 104) {
        recorded++;
      }
    }
    assertEquals(1, recorded, "the call with every name set must be recorded");
  }
}
