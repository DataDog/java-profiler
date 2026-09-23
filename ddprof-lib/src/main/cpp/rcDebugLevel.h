#ifndef _RC_DEBUG_LEVEL_H
#define _RC_DEBUG_LEVEL_H

// Runtime level gate for the reference-chains subsystem's TEST_LOG
// diagnostics (referenceChains.cpp + livenessTracker.cpp). Included AFTER
// common.h, this re-points this translation unit's TEST_LOG at a level
// check and adds TEST_LOG_SUMMARY:
//   0  silent (default)    1  lifecycle/summary (TEST_LOG_SUMMARY)
//   2  full per-object/per-klass diagnostics (TEST_LOG)
// Sources: DD_PROFILING_REFERENCE_CHAINS_DEBUG=0|1|2 at first use,
// overridden at runtime by /tmp/ddprof_root/refchains_debug_level (single
// digit; remove the file to fall back to the env value). Refresh does
// open/read ~once per second, so it never runs in heap callbacks. DEBUG
// builds only: elsewhere TEST_LOG is a no-op (common.h).

#include "common.h"

// Compiled in ALL builds (the gtest binary is a non-DEBUG build and tests
// it directly); the macros below stay DEBUG-only like TEST_LOG itself.
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
