/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Dependency fixture: defines both ddprof markers so that a hook fixture
// built with -DREFERENCE_MARKERS resolves them from here. Its own image also
// classifies as a recognized ddprof image when loaded alone.

#include <stdint.h>

__attribute__((visibility("default"))) uint64_t fixture_start_marker_calls;
__attribute__((visibility("default"))) uint64_t fixture_stop_marker_calls;

__attribute__((visibility("default"))) void ddprof_start_profiling(void) {
    fixture_start_marker_calls++;
}

__attribute__((visibility("default"))) void ddprof_stop_profiling(void) {
    fixture_stop_marker_calls++;
}
