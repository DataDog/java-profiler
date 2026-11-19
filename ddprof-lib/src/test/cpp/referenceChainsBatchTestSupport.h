/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Shared batch-entry seeding for expandFrontier() tests, included by the batch test .inc files
// (test-only; internal linkage, so every including TU gets its own copy).

#ifndef REFERENCE_CHAINS_BATCH_TEST_SUPPORT_H
#define REFERENCE_CHAINS_BATCH_TEST_SUPPORT_H

#include <stdexcept>

#include "referenceChainsMockHeap.h"

// Seeding is test setup that must never fail: a tag or insert failure means broken setup, so
// abort the test with an exception instead of returning a sentinel callers could ignore.
static jlong seedBatchEntry(ReferenceChainTracker *tracker,
                            ReferenceChainsMockHeap &mock,
                            FrontierTable *frontier, int node) {
    jlong tag = tracker->tagObject(&mock.mock_jvmti,
                                   reinterpret_cast<jobject>(&mock.node_tags[node]));
    if (tag == 0) {
        throw std::logic_error("seedBatchEntry: tagObject (SetTag) failed");
    }
    if (!frontier->insert(tag, 0, 1, 0, FrontierEntryState::EDGE)) {
        throw std::logic_error("seedBatchEntry: frontier insert failed");
    }
    ReferenceChainsTestAccessor::pushPendingExpandForTest(tag);
    return tag;
}

// Tracker state is process-global (instance() singleton): after a successful start(), every exit
// path must run stop() exactly once, or enabled state and the BFS thread leak into later tests.
namespace {
struct BatchTrackerGuard {
    explicit BatchTrackerGuard(const std::string &args_str)
        : _tracker(ReferenceChainTracker::instance()) {
        Arguments args;
        if (args.parse(args_str.c_str())) {
            throw std::logic_error("BatchTrackerGuard: Arguments::parse failed");
        }
        if (_tracker->start(args)) {
            throw std::logic_error("BatchTrackerGuard: tracker start failed");
        }
    }
    ~BatchTrackerGuard() { _tracker->stop(); }
    BatchTrackerGuard(const BatchTrackerGuard &) = delete;
    BatchTrackerGuard &operator=(const BatchTrackerGuard &) = delete;
    ReferenceChainTracker *tracker() const { return _tracker; }

private:
    ReferenceChainTracker *_tracker;
};
} // namespace

#endif // REFERENCE_CHAINS_BATCH_TEST_SUPPORT_H
