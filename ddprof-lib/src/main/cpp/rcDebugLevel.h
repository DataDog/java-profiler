#ifndef _RC_DEBUG_LEVEL_H
#define _RC_DEBUG_LEVEL_H

// Runtime level gate for the reference-chains subsystem's TEST_LOG
// diagnostics (referenceChains.cpp + livenessTracker.cpp). Included
// AFTER common.h, this re-points THIS translation unit's TEST_LOG at a
// level check and adds TEST_LOG_SUMMARY:
//
//   level 0  silent (the default - keeps DEBUG builds pod-safe)
//   level 1  lifecycle/summary: state-machine transitions, per-pass and
//            per-poll outcomes (candidates, canary, rotation counters,
//            drain/re-emit, leak-tag correlation)
//   level 2  full diagnostics: per-object/per-klass/per-entry lines
//            (heap admits, auto-marks, sweep/fold internals)
//
// Sources, in order: the env var below at first use, overridden at
// runtime by the file below (re-checked about once per second from the
// reference-chains thread loop - refresh does open/read, so it never
// runs in heap callbacks; heap callbacks only read the cached atomic).
//
//   env:  DD_PROFILING_REFERENCE_CHAINS_DEBUG=0|1|2
//   file: /tmp/ddprof_root/refchains_debug_level   (single digit 0/1/2;
//         remove the file to fall back to the env value)
//
// All machinery is DEBUG-build-only: in non-debug builds TEST_LOG is
// already a no-op (common.h) and TEST_LOG_SUMMARY matches it, so this
// header costs nothing.

#include "common.h"

// The level machinery is compiled in ALL builds (the gtest binary is a
// non-DEBUG build and tests it directly; in non-DEBUG builds nothing calls
// it because the TEST_LOG macros are no-ops), while the macros below stay
// DEBUG-only like TEST_LOG itself.
int rcDebugLevel();                      // cached; lazy env init on first use
void rcDebugLevelRefresh(bool force = false); // file override check, ~1s TTL
int parseRcDebugLevel(const char *value); // pure: NULL/invalid -> -1, else 0/1/2
int readRcDebugLevelFile(const char *path); // pure: -1 missing/invalid

#ifdef DEBUG

#undef TEST_LOG
#define TEST_LOG(fmt, ...)                                                                  \
  do {                                                                                      \
    if (rcDebugLevel() >= 2) {                                                              \
      fprintf(stdout, "[TEST::INFO] " fmt "\n", ##__VA_ARGS__);                             \
      fflush(stdout);                                                                       \
    }                                                                                       \
  } while (0)

#define TEST_LOG_SUMMARY(fmt, ...)                                                         \
  do {                                                                                      \
    if (rcDebugLevel() >= 1) {                                                              \
      fprintf(stdout, "[TEST::INFO] " fmt "\n", ##__VA_ARGS__);                             \
      fflush(stdout);                                                                       \
    }                                                                                       \
  } while (0)

#else // DEBUG

#define TEST_LOG_SUMMARY(fmt, ...) // No-op in non-debug mode

#endif // DEBUG

#endif // _RC_DEBUG_LEVEL_H
