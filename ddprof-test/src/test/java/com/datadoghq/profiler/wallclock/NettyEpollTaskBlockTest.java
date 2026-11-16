/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.NativeWaitTestSupport;
import com.datadoghq.profiler.Platform;
import io.netty.channel.epoll.ProfilerEpollFixture;
import java.io.DataInputStream;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;

/** Real Netty coverage; Linux epoll unavailability is a failure, not a supported-platform skip. */
@Tag("netty-child")
public class NettyEpollTaskBlockTest extends AbstractProfilerTest {
  @Override
  protected void withTestAssumptions() {
    if (!Boolean.getBoolean("ddprof.netty.child")) {
      throw new IllegalStateException(
          "real Netty tests require the independent NettyEpollTestChild owner");
    }
  }

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isLinux();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  /** Keeps Netty's default select strategy and timeout policy unchanged. */
  @Test
  public void defaultEventLoopWaitProducesTaskBlock() throws Exception {
    String name = "netty-default-epoll";
    try (ProfilerEpollFixture fixture = new ProfilerEpollFixture(name)) {
      assertEquals("4.1.137.Final", fixture.version());
      assertDeletedMapping(false);
      exerciseBothWorkers(fixture, name + "-timed");
    }
    stopProfiler();
    JfrEvents events = verifyEvents("datadog.TaskBlock", false);
    assertEpollTaskBlock(events, name, "io.netty.");
    assertTimedEpollTaskBlocks(events, name + "-timed", "io.netty.");
  }

  /** Relocates real classes and lets Netty extract and delete its own renamed native image. */
  @Test
  public void shadedDeletedImageProducesTaskBlock() throws Exception {
    String name = "netty-shaded-epoll";
    ClassLoader loader = new ShadedNettyClassLoader(getClass().getClassLoader());
    Class<?> type =
        loader.loadClass(
            ShadedNettyClassLoader.PREFIX + "io.netty.channel.epoll.ProfilerEpollFixture");
    try (AutoCloseable fixture =
            (AutoCloseable) type.getConstructor(String.class).newInstance(name);
        AutoCloseable timedFixture =
            (AutoCloseable) type.getConstructor(String.class).newInstance(name + "-timed")) {
      assertEquals("4.1.137.Final", type.getMethod("version").invoke(fixture));
      assertDeletedMapping(true);
      for (int i = 0; i < 5; i++) {
        type.getMethod("timedWait").invoke(fixture);
      }
      TimedNativeWorker.run(
          name + "-controller",
          1,
          () -> type.getMethod("timedNativeWaits", int.class).invoke(timedFixture, 5),
          TimeUnit.SECONDS.toNanos(5),
          TimeUnit.SECONDS.toNanos(5));
    }
    stopProfiler();
    JfrEvents events = verifyEvents("datadog.TaskBlock", false);
    assertEpollTaskBlock(events, name, ShadedNettyClassLoader.PREFIX + "io.netty.");
    assertTimedEpollTaskBlocks(
        events, name + "-timed", ShadedNettyClassLoader.PREFIX + "io.netty.");
  }

  /** Loads the deleted image while stopped, then requires events in both subsequent sessions. */
  @Test
  public void alreadyLoadedDeletedImageSurvivesProfilerRestart() throws Exception {
    stopProfiler();
    String name = "netty-restart-epoll";
    try (ProfilerEpollFixture fixture = new ProfilerEpollFixture(name)) {
      assertDeletedMapping(false);
      assertEquals(-9, fixture.invalidDescriptorErrno(), "inactive JNI must preserve EBADF");
      assertEquals(
          -9, fixture.invalidTimedDescriptorErrno(), "inactive timed JNI must preserve EBADF");
      for (int session = 0; session < 2; session++) {
        Path recording =
            Files.createTempFile(Paths.get("/tmp/recordings"), "netty-restart-", ".jfr");
        boolean running = false;
        try {
          profiler.execute(
              "start," + getProfilerCommand() + ",jfr,file=" + recording.toAbsolutePath());
          running = true;
          assertEquals(-9, fixture.invalidDescriptorErrno(), "active JNI must preserve EBADF");
          assertEquals(
              -9, fixture.invalidTimedDescriptorErrno(), "active timed JNI must preserve EBADF");
          exerciseBothWorkers(fixture, name + "-timed");
          profiler.stop();
          running = false;
          JfrEvents events = verifyEvents(recording, "datadog.TaskBlock", false);
          assertEpollTaskBlock(events, name, "io.netty.");
          assertTimedEpollTaskBlocks(events, name + "-timed", "io.netty.");
          assertEquals(-9, fixture.invalidDescriptorErrno(), "restored JNI must preserve EBADF");
          assertEquals(
              -9, fixture.invalidTimedDescriptorErrno(), "restored timed JNI must preserve EBADF");
        } finally {
          if (running) {
            profiler.stop();
          }
          if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) {
            Files.deleteIfExists(recording);
          }
        }
      }
    }
  }

  /** Holds one old hook scope, not merely a retrying JNI invocation, across restart. */
  @Test
  public void survivingOwnerAndNewWorkerAreDisjointAcrossRestart() throws Exception {
    verifySurvivorAcrossRestart(false);
  }

  /**
   * One deliberate EINTR opens fresh recording-local work without stealing the new worker's run.
   */
  @Test
  public void interruptedSurvivorStartsFreshScopeAfterRestart() throws Exception {
    verifySurvivorAcrossRestart(true);
  }

  private void verifySurvivorAcrossRestart(boolean interruptSurvivor) throws Exception {
    stopProfiler();
    String name = "netty-controlled-loop";
    Path first = Files.createTempFile(Paths.get("/tmp/recordings"), "netty-old-owner-", ".jfr");
    Path second = Files.createTempFile(Paths.get("/tmp/recordings"), "netty-new-owner-", ".jfr");
    boolean running = false;
    try (ProfilerEpollFixture fixture = new ProfilerEpollFixture(name)) {
      profiler.execute("start," + getProfilerCommand() + ",jfr,file=" + first.toAbsolutePath());
      running = true;
      exerciseBothWorkers(fixture, name + "-timed-first");
      try (ProfilerEpollFixture.ControlledWait old = fixture.controlledWait(name + "-survivor")) {
        WallClockBlockTrackerTestSupport.NativeOwnerSnapshot before =
            WallClockBlockTrackerTestSupport.available()
                ? WallClockBlockTrackerTestSupport.nativeOwnerSnapshot(old.nativeTid())
                : null;
        profiler.stop();
        running = false;
        profiler.execute("start," + getProfilerCommand() + ",jfr,file=" + second.toAbsolutePath());
        running = true;
        try (ProfilerEpollFixture.ControlledWait next = fixture.controlledWait(name + "-new")) {
          old.assertBlocked();
          assertSameNativeOwner(before, old.nativeTid(), false);
          if (interruptSurvivor) {
            NativeWaitTestSupport.interruptWait(old.nativeTid());
            old.assertBlocked();
            assertSameNativeOwner(before, old.nativeTid(), true);
            // Keep the fresh scope beyond the duration threshold before releasing its eventfd.
            exerciseBothWorkers(fixture, name + "-timed-second");
          }
          old.close();
          next.assertBlocked();
          if (!interruptSurvivor) exerciseBothWorkers(fixture, name + "-timed-second");
        }
        profiler.stop();
        running = false;
      }
      JfrEvents oldEvents = verifyEvents(first, "datadog.TaskBlock", false);
      JfrEvents newEvents = verifyEvents(second, "datadog.TaskBlock", false);
      assertEpollTaskBlock(oldEvents, name, "io.netty.");
      assertTimedEpollTaskBlocks(oldEvents, name + "-timed-first", "io.netty.");
      assertEpollTaskBlock(newEvents, name, "io.netty.");
      assertTimedEpollTaskBlocks(newEvents, name + "-timed-second", "io.netty.");
      assertEquals(0, TaskBlockAssertions.countEventsForThread(oldEvents, name + "-survivor"));
      assertEquals(
          interruptSurvivor ? 1 : 0,
          TaskBlockAssertions.countEventsForThread(newEvents, name + "-survivor"));
      assertEquals(1, TaskBlockAssertions.countEventsForThread(newEvents, name + "-new"));
      if (interruptSurvivor) {
        JfrEvents recordingInfo = verifyEvents(second, "jdk.ActiveRecording", false);
        assertEquals(1, recordingInfo.count());
        Long recordingStart = recordingInfo.iterator().next().getLong("startTime");
        assertNotNull(recordingStart, "missing restarted recording startTime");
        for (JfrEvent event : newEvents) {
          if ((name + "-survivor").equals(event.getThreadName("eventThread"))) {
            Long start = event.getLong("startTime");
            assertNotNull(start, "missing fresh survivor startTime");
            assertTrue(start > recordingStart, "old-scope entry must not replay after restart");
            assertEquals("IO_WAIT", event.getString("observedBlockingState"));
            assertNotNull(event.get("stackTrace"));
            assertTrue(event.getStackTraceString().contains("ControlledWait"));
          }
        }
      }
    } finally {
      if (running) profiler.stop();
      if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) {
        Files.deleteIfExists(first);
        Files.deleteIfExists(second);
      }
    }
  }

  /** Generation observations are DEBUG-only; release retains kernel, mask and JFR oracles. */
  private static void assertSameNativeOwner(
      WallClockBlockTrackerTestSupport.NativeOwnerSnapshot before, int tid, boolean reentered) {
    if (before == null) return;
    long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(5);
    WallClockBlockTrackerTestSupport.NativeOwnerSnapshot after;
    do {
      after = WallClockBlockTrackerTestSupport.nativeOwnerSnapshot(tid);
      if (!reentered || after.blockGeneration > before.blockGeneration) break;
      Thread.yield();
    } while (System.nanoTime() - deadline < 0);
    assertTrue(before.blockGeneration > 0, "old native hook must actually own a token");
    assertEquals(before.slotId, after.slotId, "restart must retain the native slot");
    assertEquals(before.lifecycleGeneration, after.lifecycleGeneration);
    assertEquals(before.blockGeneration + (reentered ? 1 : 0), after.blockGeneration);
    if (reentered) {
      assertTrue(after.recordingEpoch > before.recordingEpoch);
      assertEquals(after.currentRecordingEpoch, after.recordingEpoch);
    } else {
      assertEquals(before.recordingEpoch, after.recordingEpoch);
      assertTrue(after.currentRecordingEpoch > after.recordingEpoch);
    }
  }

  private static void exerciseBothWorkers(ProfilerEpollFixture fixture, String name)
      throws Exception {
    for (int i = 0; i < 5; i++) fixture.timedWait();
    try (ProfilerEpollFixture timedFixture = new ProfilerEpollFixture(name)) {
      runTimedWorker(timedFixture, name);
    }
  }

  /** The controller bounds ownership; the fixture executes all five JNI waits on its event loop. */
  private static void runTimedWorker(ProfilerEpollFixture fixture, String name) throws Exception {
    TimedNativeWorker.run(
        name + "-controller",
        1,
        () -> fixture.timedNativeWaits(5),
        TimeUnit.SECONDS.toNanos(5),
        TimeUnit.SECONDS.toNanos(5));
  }

  /** Makes the timed native branch reachable independently of event-loop wakeup timing. */
  @Test
  public void timedNativeWaitProducesTaskBlock() throws Exception {
    String name = "netty-timed-native-epoll";
    try (ProfilerEpollFixture fixture = new ProfilerEpollFixture(name)) {
      assertEquals("4.1.137.Final", fixture.version());
      assertDeletedMapping(false);
      runTimedWorker(fixture, name);
    }
    stopProfiler();
    assertTimedEpollTaskBlocks(verifyEvents("datadog.TaskBlock", false), name, "io.netty.");
  }

  /** Keeps real JNI waits functional while TaskBlock is explicitly disabled. */
  @Test
  public void disabledTaskBlockPreservesNativeWaits() throws Exception {
    runAdditionalSession("wall=1ms,filter=,wallprecheck=false", false, false);
  }

  /** Requires both real native socket events and Netty TaskBlocks in the same recording. */
  @Test
  public void nativeSocketSamplerCoexistsWithTaskBlock() throws Exception {
    runAdditionalSession(getProfilerCommand() + ",natsock=100us", true, true);
  }

  /** Owns a separate recording so the normal setup session cannot satisfy either oracle. */
  private void runAdditionalSession(String command, boolean expectBlocks, boolean socketTraffic)
      throws Exception {
    stopProfiler();
    String name = "netty-additional-epoll";
    Path recording = Files.createTempFile(Paths.get("/tmp/recordings"), "netty-extra-", ".jfr");
    boolean running = false;
    try (ProfilerEpollFixture fixture = new ProfilerEpollFixture(name)) {
      assertEquals("4.1.137.Final", fixture.version());
      assertDeletedMapping(false);
      profiler.execute("start," + command + ",jfr,file=" + recording.toAbsolutePath());
      running = true;
      assertEquals(-9, fixture.invalidTimedDescriptorErrno());
      runTimedWorker(fixture, name);
      if (socketTraffic) {
        // Sequential bounded loopback exchange needs no extra worker or daemon to hide failures.
        try (ServerSocket server = new ServerSocket(0, 1, InetAddress.getLoopbackAddress());
            Socket client = new Socket()) {
          server.setSoTimeout(5_000);
          client.connect(
              new InetSocketAddress(InetAddress.getLoopbackAddress(), server.getLocalPort()),
              5_000);
          try (Socket peer = server.accept()) {
            peer.setSoTimeout(5_000);
            DataInputStream input = new DataInputStream(peer.getInputStream());
            byte[] data = new byte[4_096];
            for (int i = 0; i < 1_024; i++) {
              client.getOutputStream().write(data);
              input.readFully(data);
            }
          }
        }
      }
      profiler.stop();
      running = false;
      JfrEvents events = verifyEvents(recording, "datadog.TaskBlock", false);
      if (expectBlocks) {
        assertTimedEpollTaskBlocks(events, name, "io.netty.");
      } else {
        assertTrue(!events.hasItems(), "TaskBlock must be absent with wallprecheck=false");
      }
      if (socketTraffic) {
        assertTrue(
            verifyEvents(recording, "datadog.NativeSocketEvent", false).hasItems(),
            "native socket sampler must remain functional alongside Netty TaskBlock hooks");
      }
    } finally {
      if (running) {
        profiler.stop();
      }
      if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) {
        Files.deleteIfExists(recording);
      }
    }
  }

  /** Requires the five explicit timed JNI intervals, separately from ordinary loop waits. */
  public static void assertTimedEpollTaskBlocks(
      Iterable<JfrEvent> events, String name, String packagePrefix) {
    assertEpollTaskBlocks(events, name, packagePrefix, true);
  }

  private static void assertDeletedMapping(boolean shaded) throws Exception {
    String marker =
        shaded ? "ddproffixture_netty_transport_native_epoll" : "libnetty_transport_native_epoll";
    boolean found = false;
    for (String line : Files.readAllLines(Paths.get("/proc/self/maps"), StandardCharsets.UTF_8)) {
      if (line.contains(marker)) {
        found = true;
        System.out.println("NETTY_IMAGE_MAP " + line);
        assertTrue(line.endsWith(" (deleted)"), "Netty did not delete its mapped image: " + line);
      }
    }
    assertTrue(found, "missing actual Netty native mapping for " + marker);
  }

  /** Requires five Netty epoll waits without accepting unrelated blocks on that worker. */
  public static void assertEpollTaskBlock(
      Iterable<JfrEvent> events, String name, String packagePrefix) {
    assertEpollTaskBlocks(events, name, packagePrefix, false);
  }

  private static void assertEpollTaskBlocks(
      Iterable<JfrEvent> events, String name, String packagePrefix, boolean timed) {
    int matched = 0;
    Set<Long> intervalStarts = new HashSet<>();
    for (JfrEvent event : events) {
      if (!name.equals(event.getThreadName("eventThread"))) {
        continue;
      }
      assertNotNull(event.get("stackTrace"), "missing TaskBlock stack");
      boolean epollFrame = false;
      boolean timedFrame = false;
      for (JfrFrame frame : event.getStackTrace().frames()) {
        String type = frame.className();
        epollFrame |=
            (packagePrefix + "channel.epoll.Native").equals(type)
                && frame.methodName() != null
                && frame.methodName().startsWith("epollWait");
        timedFrame |=
            (packagePrefix + "channel.epoll.ProfilerEpollFixture").equals(type)
                && frame.methodName() != null
                && (frame.methodName().startsWith("timedNativeWait")
                    || frame.methodName().startsWith("lambda$timedNativeWaits"));
      }
      if (!epollFrame || (timed && !timedFrame)) {
        continue;
      }
      assertTrue(event.has("observedBlockingState"), "missing TaskBlock state");
      assertEquals("IO_WAIT", event.getString("observedBlockingState"));
      assertNotNull(event.getLong("duration"), "missing TaskBlock duration");
      assertTrue(event.getLong("duration") > 0, "nonpositive wait duration");
      assertTrue(
          !event.has("correlationId"), "synchronous TaskBlock has no async correlation field");
      if (timed) {
        Long start = event.getLong("startTime");
        assertNotNull(start, "missing timed TaskBlock startTime");
        assertTrue(intervalStarts.add(start), "duplicate timed TaskBlock interval");
      }
      matched++;
    }
    if (timed) {
      assertEquals(5, matched, "expected five distinct timedNativeWait intervals on " + name);
    } else {
      assertTrue(matched >= 5, "fewer than five IO_WAIT TaskBlocks on real Netty worker " + name);
    }
  }
}
