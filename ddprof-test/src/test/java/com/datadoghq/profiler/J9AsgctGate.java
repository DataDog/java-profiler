/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Java mirror of the native J9 ASGCT rules, so tests can predict on the running JVM which J9
 * sampler the profiler picks and whether it reports the ASGCT deadlock risk. Like the native
 * classifier, it assumes each version property carries its tag at most once.
 */
public final class J9AsgctGate {
  private static final Pattern OPENJ9_0_60 = Pattern.compile("openj9-0\\.60(?!\\d)");
  private static final Pattern IBM_FIX_PACK = Pattern.compile("\\(SR8 FP(\\d{1,4})(?!\\d)");

  private J9AsgctGate() {}

  /**
   * Mirrors {@code J9Support::can_use_ASGCT()}: the JDK updates that carry OpenJ9 0.51's fix for
   * the earlier ASGCT livelock.
   */
  public static boolean asgctAllowed() {
    return (Platform.isJavaVersion(8) && Platform.isJavaVersionAtLeast(8, 0, 451))
        || (Platform.isJavaVersion(11) && Platform.isJavaVersionAtLeast(11, 0, 27))
        || (Platform.isJavaVersion(17) && Platform.isJavaVersionAtLeast(17, 0, 15))
        || (Platform.isJavaVersion(21) && Platform.isJavaVersionAtLeast(21, 0, 7));
  }

  /** Mirrors {@code J9Support::isAsgctDeadlockProneVersion()} on this JVM's properties. */
  public static boolean deadlockProne() {
    String vmVersion = System.getProperty("java.vm.version", "");
    if (OPENJ9_0_60.matcher(vmVersion).find()) {
      return true;
    }
    Matcher fixPack = IBM_FIX_PACK.matcher(System.getProperty("java.runtime.version", ""));
    if (!fixPack.find()) {
      return false;
    }
    int number = Integer.parseInt(fixPack.group(1));
    return number >= 70 && number < 75;
  }
}
