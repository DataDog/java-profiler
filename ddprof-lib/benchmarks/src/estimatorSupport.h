/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _ESTIMATOR_SUPPORT_H
#define _ESTIMATOR_SUPPORT_H

#include <cstdint>
#include <string>

// One window-marker record in the memory-gate format: five k=v tokens
// prefixed by "markers: ", each unavailable source rendered as the literal NA.
std::string readMarkerRecord();

// libc identification for the report; NA when the version is unknown.
std::string libcName();
std::string libcVersion();

// Monotonic nanosecond clock, used for spin calibration.
uint64_t monotonicNanos();

#endif // _ESTIMATOR_SUPPORT_H
