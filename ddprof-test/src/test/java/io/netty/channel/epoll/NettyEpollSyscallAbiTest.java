/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package io.netty.channel.epoll;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

/** Checks /proc ABI selection without depending on the JVM's possibly emulated architecture. */
public class NettyEpollSyscallAbiTest {
  @Test
  void arm64KernelUsesArm64SyscallsEvenForAnEmulatedJvm() {
    assertTrue(
        ProfilerEpollFixture.kernelUsesArm64Syscalls(
            "processor\t: 0\nCPU implementer\t: 0x00\nCPU architecture: 8\n"));
  }

  @Test
  void x64KernelUsesX64Syscalls() {
    assertFalse(
        ProfilerEpollFixture.kernelUsesArm64Syscalls(
            "processor\t: 0\nvendor_id\t: GenuineIntel\n"));
  }

  @Test
  void rejectsUnknownAndUnsupportedKernelAbis() {
    assertThrows(
        IllegalStateException.class,
        () -> ProfilerEpollFixture.kernelUsesArm64Syscalls("processor\t: 0\n"));
    assertThrows(
        IllegalStateException.class,
        () -> ProfilerEpollFixture.kernelUsesArm64Syscalls("CPU architecture: 7\n"));
  }
}
