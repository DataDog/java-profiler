/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package io.netty.channel.epoll;

import static org.junit.jupiter.api.Assertions.*;

import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;

/** Real event-loop cleanup regression, run only by the independent child-JVM owner. */
@Tag("netty-child")
public class ProfilerEpollFixtureTest {
  /** A restored interrupt must not skip joining the fixture's independently owned event loop. */
  @Test
  public void interruptedCloseStillTerminatesEventLoop() throws Exception {
    Assumptions.assumeTrue(Platform.isLinux());
    if (!Boolean.getBoolean("ddprof.netty.child")) {
      throw new IllegalStateException(
          "fixture cleanup requires the independent NettyEpollTestChild owner");
    }
    String name = "netty-interrupted-close";
    ProfilerEpollFixture fixture = new ProfilerEpollFixture(name);
    try {
      fixture.timedWait();
      Thread worker = null;
      for (Thread thread : Thread.getAllStackTraces().keySet()) {
        if (name.equals(thread.getName())) {
          assertNull(worker, "event-loop thread identity must be unique");
          worker = thread;
        }
      }
      assertNotNull(worker, "must observe the actual live event-loop thread before cleanup");
      assertTrue(worker.isAlive());
      Thread.currentThread().interrupt();
      fixture.close();
      assertTrue(Thread.interrupted(), "close must restore interruption");
      worker.join(1_000);
      assertFalse(worker.isAlive(), "event-loop termination must be observed, not inferred");
    } finally {
      Thread.interrupted();
      fixture.close();
    }
  }
}
