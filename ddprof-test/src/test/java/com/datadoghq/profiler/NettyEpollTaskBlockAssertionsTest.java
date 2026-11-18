/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import static org.junit.jupiter.api.Assertions.assertThrows;

import com.datadoghq.profiler.wallclock.NettyEpollTaskBlockTest;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import org.junit.jupiter.api.Test;

/** Synthetic controls keep ordinary event-loop waits from satisfying the timed JNI oracle. */
public class NettyEpollTaskBlockAssertionsTest {
  private static final String WORKER = "netty-timed-worker";

  /** Ordinary Native.epollWait frames remain valid only for the default-loop oracle. */
  @Test
  public void ordinaryEpollFramesCannotReplaceTimedWaits() {
    List<JfrEvent> events = waits("io.netty.", false, 5);
    NettyEpollTaskBlockTest.assertEpollTaskBlock(events, WORKER, "io.netty.", 0);
    assertThrows(
        AssertionError.class,
        () -> NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(events, WORKER, "io.netty.", 0));
  }

  /** Four explicit intervals plus an ordinary loop event still lack the fifth JNI interval. */
  @Test
  public void ordinaryWaitCannotCompensateForMissingTimedInterval() {
    List<JfrEvent> events = waits("io.netty.", true, 4);
    events.add(wait("io.netty.", false, 99));
    assertThrows(
        AssertionError.class,
        () -> NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(events, WORKER, "io.netty.", 0));
  }

  /** Repeating a captured event cannot compensate for a missing explicit wait. */
  @Test
  public void duplicatedIntervalCannotReplaceFifthTimedWait() {
    List<JfrEvent> events = waits("io.netty.", true, 4);
    events.add(events.get(0));
    assertThrows(
        AssertionError.class,
        () -> NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(events, WORKER, "io.netty.", 0));
  }

  /** Both original and relocated fixture frames identify five distinct explicit intervals. */
  @Test
  public void fiveDistinctTimedIntervalsAcceptOriginalAndShadedFixtures() {
    for (String prefix : Arrays.asList("io.netty.", "ddproffixture.io.netty.")) {
      List<JfrEvent> events = waits(prefix, true, 5);
      events.add(wait(prefix, false, 99));
      NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(events, WORKER, prefix, 0);
    }
  }

  /** The explicit-interval marker cannot substitute for the actual Netty native epoll frame. */
  @Test
  public void fixtureFrameWithoutNativeEpollCannotSatisfyTimedOracle() {
    List<JfrEvent> events = waits("io.netty.", true, 5);
    for (JfrEvent event : events) {
      event
          .raw()
          .put(
              "stackTrace",
              Collections.singletonMap(
                  "frames",
                  new Object[] {
                    frame("io.netty.channel.epoll.ProfilerEpollFixture", "timedNativeWait")
                  }));
    }
    assertThrows(
        AssertionError.class,
        () -> NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(events, WORKER, "io.netty.", 0));
  }

  /**
   * The lambda frame of the fixture's explicit waits satisfies the oracle when the named frame is
   * unresolved.
   */
  @Test
  public void lambdaFrameIdentifiesTimedIntervalWithoutNamedMethod() {
    List<JfrEvent> events = waits("io.netty.", false, 5);
    for (JfrEvent event : events) {
      event
          .raw()
          .put(
              "stackTrace",
              Collections.singletonMap(
                  "frames",
                  new Object[] {
                    frame("io.netty.channel.epoll.Native", "epollWait0"),
                    frame(
                        "io.netty.channel.epoll.ProfilerEpollFixture", "lambda$timedNativeWaits$3")
                  }));
    }
    NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(events, WORKER, "io.netty.", 0);
  }

  /** An interval without its timestamp cannot participate in a distinct-interval assertion. */
  @Test
  public void missingTimestampFailsTimedOracle() {
    List<JfrEvent> events = waits("io.netty.", true, 5);
    events.get(0).raw().remove("startTime");
    assertThrows(
        AssertionError.class,
        () -> NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(events, WORKER, "io.netty.", 0));
  }

  /** An extra explicit interval is not evidence for the fixture's exact five-call workload. */
  @Test
  public void sixthTimedIntervalFailsExactCount() {
    List<JfrEvent> events = waits("io.netty.", true, 6);
    assertThrows(
        AssertionError.class,
        () -> NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(events, WORKER, "io.netty.", 0));
  }

  /** Missing stacks fail directly rather than silently disappearing from the event oracle. */
  @Test
  public void missingStackFailsTimedOracle() {
    List<JfrEvent> events = waits("io.netty.", true, 5);
    events.get(0).raw().remove("stackTrace");
    assertThrows(
        AssertionError.class,
        () -> NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(events, WORKER, "io.netty.", 0));
  }

  @Test
  public void recorderRejectionAccountsForMissingTimedAndOrdinaryIntervals() {
    for (String prefix : Arrays.asList("io.netty.", "ddproffixture.io.netty.")) {
      List<JfrEvent> events = waits(prefix, true, 4);
      NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(events, WORKER, prefix, 1);
      NettyEpollTaskBlockTest.assertEpollTaskBlock(events, WORKER, prefix, 1);
      assertThrows(
          AssertionError.class,
          () -> NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(events, WORKER, prefix, 0));
      assertThrows(
          AssertionError.class,
          () -> NettyEpollTaskBlockTest.assertEpollTaskBlock(events, WORKER, prefix, 0));
    }
  }

  @Test
  public void recorderRejectionDoesNotExcuseDuplicateExcessOrMalformedEmittedIntervals() {
    List<JfrEvent> duplicate = waits("io.netty.", true, 3);
    duplicate.add(duplicate.get(0));
    assertThrows(
        AssertionError.class,
        () ->
            NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(duplicate, WORKER, "io.netty.", 1));
    assertThrows(
        AssertionError.class,
        () ->
            NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(
                waits("io.netty.", true, 6), WORKER, "io.netty.", 1));
    for (String field :
        Arrays.asList("stackTrace", "observedBlockingState", "duration", "startTime")) {
      List<JfrEvent> events = waits("io.netty.", true, 4);
      events.get(0).raw().remove(field);
      assertThrows(
          AssertionError.class,
          () -> NettyEpollTaskBlockTest.assertTimedEpollTaskBlocks(events, WORKER, "io.netty.", 1));
    }
  }

  private static List<JfrEvent> waits(String prefix, boolean timed, int count) {
    List<JfrEvent> events = new ArrayList<>();
    for (int i = 0; i < count; i++) events.add(wait(prefix, timed, i + 1));
    return events;
  }

  private static JfrEvent wait(String prefix, boolean timed, long start) {
    List<Map<String, Object>> frames = new ArrayList<>();
    frames.add(frame(prefix + "channel.epoll.Native", "epollWait"));
    if (timed) frames.add(frame(prefix + "channel.epoll.ProfilerEpollFixture", "timedNativeWait"));
    Map<String, Object> values = new HashMap<>();
    values.put("eventThread", Collections.singletonMap("osName", WORKER));
    values.put("stackTrace", Collections.singletonMap("frames", frames.toArray()));
    values.put("observedBlockingState", "IO_WAIT");
    values.put("duration", 300_000_000L);
    values.put("startTime", start);
    return new JfrEvent("datadog.TaskBlock", values);
  }

  private static Map<String, Object> frame(String type, String name) {
    Map<String, Object> method = new HashMap<>();
    method.put("type", Collections.singletonMap("name", type));
    method.put("name", name);
    return Collections.singletonMap("method", method);
  }
}
