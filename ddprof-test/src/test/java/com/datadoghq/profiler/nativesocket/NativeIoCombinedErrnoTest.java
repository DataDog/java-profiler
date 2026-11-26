/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativesocket;

/**
 * Runs the same actual-import errno and sampled-recording qualification with both owners active.
 */
public class NativeIoCombinedErrnoTest extends NativeIoErrnoTest {
  @Override
  protected String getProfilerCommand() {
    return "natsock=1us,wall=1ms,filter=,wallprecheck=true";
  }
}
