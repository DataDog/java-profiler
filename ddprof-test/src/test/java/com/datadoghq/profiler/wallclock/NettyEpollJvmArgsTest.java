/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.Arrays;
import java.util.Collections;
import org.junit.jupiter.api.Test;

/** Covers which parent JVM flags the isolated child launchers forward. */
class NettyEpollJvmArgsTest {
  @Test
  void asanParentForwardsHeapPlacementOnceWithEffectiveHeap() {
    assertEquals(
        Arrays.asList(
            "-Xmx1024m", "-XX:HeapBaseMinAddress=0x4000000", "-XX:CompressedClassSpaceSize=256m"),
        NettyEpollJvm.heapLayoutArgs(
            Arrays.asList(
                "-Djdk.attach.allowAttachSelf",
                "-XX:ErrorFile=build/hs_err_pid%p.log",
                "-Xmx512m",
                "-Djava.library.path=/lib",
                "-XX:OnError=/tmp/do_stuff.sh",
                "-XX:HeapBaseMinAddress=0x4000000",
                "-Xmx1024m",
                "-XX:CompressedClassSpaceSize=256m")));
  }

  @Test
  void parentWithoutHeapFlagsGetsDefaultHeapOnly() {
    assertEquals(
        Collections.singletonList(NettyEpollJvm.DEFAULT_CHILD_HEAP),
        NettyEpollJvm.heapLayoutArgs(
            Arrays.asList("-Xms64m", "-XX:+UseCompressedClassPointers", "-Dddprof.x=1")));
  }

  @Test
  void placementWithoutParentHeapKeepsDefaultHeap() {
    assertEquals(
        Arrays.asList(NettyEpollJvm.DEFAULT_CHILD_HEAP, "-XX:HeapBaseMinAddress=0x4000000"),
        NettyEpollJvm.heapLayoutArgs(
            Collections.singletonList("-XX:HeapBaseMinAddress=0x4000000")));
  }

  @Test
  void parentHeapOverridesDefault() {
    assertEquals(
        Collections.singletonList("-Xmx1536m"),
        NettyEpollJvm.heapLayoutArgs(Collections.singletonList("-Xmx1536m")));
  }
}
