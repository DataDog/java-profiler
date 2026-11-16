/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.datadoghq.profiler.Platform;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/**
 * Owns each real Netty case in a fresh JVM; an unresponsive JNI call cannot strand the test worker.
 */
public class NettyEpollIsolationTest {
  /** Exercises the default, unmodified EventLoopGroup wait strategy. */
  @Test
  public void defaultEventLoopWaitProducesTaskBlock() throws Exception {
    run("defaultEventLoopWaitProducesTaskBlock");
  }

  /** Holds both JNI owners at actual kernel wait boundaries across a recording transition. */
  @Test
  public void survivingOwnerAndNewWorkerAreDisjointAcrossRestart() throws Exception {
    run("survivingOwnerAndNewWorkerAreDisjointAcrossRestart");
  }

  /** Distinguishes a fresh post-EINTR scope from replay of a surviving old hook. */
  @Test
  public void interruptedSurvivorStartsFreshScopeAfterRestart() throws Exception {
    run("interruptedSurvivorStartsFreshScopeAfterRestart");
  }

  /** Exercises Netty's own extraction/deletion after package-prefix shading. */
  @Test
  public void shadedDeletedImageProducesTaskBlock() throws Exception {
    // Netty's JNI_OnUnload calls FindClass during the J9-8 classloader teardown at
    // DestroyJavaVM and segfaults the JVM after the child's recording and assertions
    // completed; reproducible in a child without the profiler loaded.
    Assumptions.assumeFalse(
        System.getProperty("java.vm.name", "").contains("J9")
            && "1.8".equals(System.getProperty("java.specification.version")),
        "the J9-8 JVM segfaults at DestroyJavaVM during shaded-image unload");
    run("shadedDeletedImageProducesTaskBlock");
  }

  /** Exercises installation/restoration across two recordings on an already loaded image. */
  @Test
  public void alreadyLoadedDeletedImageSurvivesProfilerRestart() throws Exception {
    run("alreadyLoadedDeletedImageSurvivesProfilerRestart");
  }

  /** Exercises the real positive-timeout JNI wait, not merely Netty's zero-timeout probe. */
  @Test
  public void timedNativeWaitProducesTaskBlock() throws Exception {
    run("timedNativeWaitProducesTaskBlock");
  }

  /** Requires absence of TaskBlock without changing real JNI behavior. */
  @Test
  public void disabledTaskBlockPreservesNativeWaits() throws Exception {
    run("disabledTaskBlockPreservesNativeWaits");
  }

  /** Requires both producers to work in one recording. */
  @Test
  public void nativeSocketSamplerCoexistsWithTaskBlock() throws Exception {
    run("nativeSocketSamplerCoexistsWithTaskBlock");
  }

  /** Keeps a stuck real event loop in the same independently owned JVM boundary as JNI waits. */
  @Test
  public void interruptedCloseStillTerminatesEventLoop() throws Exception {
    run("interruptedCloseStillTerminatesEventLoop");
  }

  /**
   * Uses the task's explicit runtime classpath, not Gradle worker java.class.path or inherited
   * agents.
   */
  private static void run(String method) throws Exception {
    Assumptions.assumeTrue(
        Platform.isLinux() && !Platform.isMusl(),
        "the published Netty epoll native artifact requires glibc");
    String classpath = System.getProperty("ddprof.netty.classpath");
    if (classpath == null || classpath.isEmpty()) {
      throw new IllegalStateException("test task must supply ddprof.netty.classpath");
    }
    Path directory = Paths.get("build", "netty-epoll");
    Files.createDirectories(directory);
    Path run = Files.createTempDirectory(directory, method + "-");
    List<String> command = new ArrayList<>();
    command.add(Paths.get(System.getProperty("java.home"), "bin", "java").toString());
    command.add("-Xmx512m");
    command.add("-Djdk.attach.allowAttachSelf=true");
    command.add("-Dddprof.disable_unsafe=true");
    command.add("-Dddprof.netty.reports=" + run.resolve("junit").toAbsolutePath());
    command.add("-XX:ErrorFile=" + run.resolve("hs_err_pid%p.log").toAbsolutePath());
    for (String name :
        new String[] {
          "java.library.path",
          "ddprof_test.keep_jfrs",
          "ddprof_test.config",
          "ddprof_test.ci",
          "DDPROF_TEST_DISABLE_RATE_LIMIT"
        }) {
      String value = System.getProperty(name);
      if (value != null) {
        command.add("-D" + name + "=" + value);
      }
    }
    command.add("-cp");
    command.add(classpath);
    command.add(NettyEpollTestChild.class.getName());
    command.add(method);
    Files.write(run.resolve("argv.txt"), command, java.nio.charset.StandardCharsets.UTF_8);
    Path log = run.resolve("child.log");
    assertEquals(
        0,
        NettyEpollJvm.run(command, log, TimeUnit.SECONDS.toNanos(30)),
        "isolated Netty test failed; retained log=" + log.toAbsolutePath());
  }
}
