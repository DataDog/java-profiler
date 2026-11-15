/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import io.netty.channel.epoll.ProfilerEpollFixtureTest;
import java.io.PrintWriter;
import java.lang.management.ManagementFactory;
import java.nio.file.Paths;
import org.junit.platform.engine.discovery.DiscoverySelectors;
import org.junit.platform.launcher.core.LauncherDiscoveryRequestBuilder;
import org.junit.platform.launcher.core.LauncherFactory;
import org.junit.platform.launcher.listeners.SummaryGeneratingListener;
import org.junit.platform.launcher.listeners.TestExecutionSummary;
import org.junit.platform.reporting.legacy.xml.LegacyXmlReportGeneratingListener;

/** Executes exactly one real Netty test inside a JVM owned by {@link NettyEpollJvm}. */
public final class NettyEpollTestChild {
  private NettyEpollTestChild() {}

  /**
   * Reports a result without System.exit: a surviving non-daemon worker must keep the JVM alive.
   */
  public static void main(String[] args) {
    if (args.length != 1
        || !("timedNativeWaitProducesTaskBlock".equals(args[0])
            || "defaultEventLoopWaitProducesTaskBlock".equals(args[0])
            || "shadedDeletedImageProducesTaskBlock".equals(args[0])
            || "alreadyLoadedDeletedImageSurvivesProfilerRestart".equals(args[0])
            || "disabledTaskBlockPreservesNativeWaits".equals(args[0])
            || "nativeSocketSamplerCoexistsWithTaskBlock".equals(args[0])
            || "interruptedCloseStillTerminatesEventLoop".equals(args[0])
            || "survivingOwnerAndNewWorkerAreDisjointAcrossRestart".equals(args[0]))) {
      throw new IllegalArgumentException("expected one allowlisted Netty test method name");
    }
    String reports = System.getProperty("ddprof.netty.reports");
    if (reports == null) {
      throw new IllegalArgumentException("expected ddprof.netty.reports directory");
    }
    System.setProperty("ddprof.netty.child", "true");
    System.out.println(
        "NETTY_TEST_VM "
            + ManagementFactory.getRuntimeMXBean().getName()
            + " "
            + System.getProperty("java.vm.name")
            + " "
            + System.getProperty("java.runtime.version")
            + " "
            + System.getProperty("os.arch"));
    SummaryGeneratingListener listener = new SummaryGeneratingListener();
    LegacyXmlReportGeneratingListener xml =
        new LegacyXmlReportGeneratingListener(
            Paths.get(reports), new PrintWriter(System.err, true));
    Class<?> testClass =
        "interruptedCloseStillTerminatesEventLoop".equals(args[0])
            ? ProfilerEpollFixtureTest.class
            : NettyEpollTaskBlockTest.class;
    LauncherFactory.create()
        .execute(
            LauncherDiscoveryRequestBuilder.request()
                .selectors(DiscoverySelectors.selectMethod(testClass, args[0]))
                .build(),
            listener,
            xml);
    TestExecutionSummary summary = listener.getSummary();
    summary.printTo(new PrintWriter(System.out, true));
    summary.printFailuresTo(new PrintWriter(System.err, true));
    if (summary.getTestsFoundCount() != 1
        || summary.getTestsSucceededCount() != 1
        || !summary.getFailures().isEmpty()) {
      throw new AssertionError("NETTY_TEST_RESULT FAIL " + args[0]);
    }
    System.out.println("NETTY_TEST_RESULT PASS " + args[0]);
  }
}
