/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <set>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "arguments.h"
#include "counters.h"
#include "livenessTracker.h"
#include "os.h"
#include "profiler.h"
#include "rcDebugLevel.h"
#include "referenceChains.h"
#include "vmEntry.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include <unistd.h>
#include <cstdio>
#include <map>

static constexpr char REFERENCE_CHAINS_TEST_NAME[] = "ReferenceChainsTest";

class ReferenceChainsGlobalSetup {
public:
    ReferenceChainsGlobalSetup() {
        installGtestCrashHandler<REFERENCE_CHAINS_TEST_NAME>();
    }
    ~ReferenceChainsGlobalSetup() {
        restoreDefaultSignalHandlers();
    }
};

static ReferenceChainsGlobalSetup global_setup;

// Enable diagnostics for tests.
[[maybe_unused]] static const bool kRcDebugLevelPinnedForTests =
    setenv("DD_PROFILING_REFERENCE_CHAINS_DEBUG", "2", 1) == 0;

#include "referenceChainsCoreTests.inc"
#include "referenceChainsBfsTests.inc"
#include "referenceChainsPodTests.inc"
#include "referenceChainsTrackerTests.inc"
#include "referenceChainsRotationTests.inc"
#include "referenceChainsTraversalTests.inc"
#include "referenceChainsAnchorTests.inc"
#include "referenceChainsEventTests.inc"
