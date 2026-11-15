/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

/** Exercises retained context and epoch-weight tails in unfiltered stackful ASGCT recordings. */
public class UnfilteredUnownedWallTailContextTransitionTest
    extends UnownedWallTailContextTransitionTest {
  @Override
  protected boolean unfiltered() {
    return true;
  }
}
