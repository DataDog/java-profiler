/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CLASS_TAG_ALLOCATOR_H
#define _CLASS_TAG_ALLOCATOR_H

#include "arch.h"
#include <jni.h>

// Process-wide, negative JVMTI class-object tag allocator, shared by
// ReferenceChainTracker (which tags every loaded class's own jclass object
// via SetTag - see resolveLoadedClasses(), referenceChains.cpp) and
// LivenessTracker (which needs a stable per-class identifier independent of
// Profiler::classMap()'s dictionary id - see KlassPopulationEntry::
// stable_class_tag's own comment, livenessTracker.h, for why: that
// dictionary can be compacted/regenerated, silently reassigning the same
// class a different id at different points in the process's life, breaking
// any attempt to correlate a klass_id LivenessTracker reports as growing
// against ReferenceChainTracker::FrontierEntry::referrer_klass values
// recorded at a different time).
//
// A single shared counter, not one independently owned by each subsystem,
// for two reasons, both load-bearing:
// 1. Two independent counters could otherwise hand out the SAME numeric
//    value to TWO DIFFERENT classes (one minted by each subsystem for a
//    class the other has not seen yet), making any cross-subsystem
//    comparison meaningless.
// 2. Class tags must stay strictly NEGATIVE:
//    ReferenceChainTracker::heapReferenceCallback() (referenceChains.cpp)
//    uses `*tag_ptr < 0` to distinguish "this heap-walk-visited object is a
//    pre-tagged class object" from an ordinary admitted instance (always
//    tagged with a positive value via nextTag()). A class tagged by a
//    counter that does not preserve this sign convention would be
//    misidentified as an ordinary object and incorrectly admitted into the
//    frontier table - a real correctness bug, not just a matching
//    inconvenience.
//
// Deliberately a plain header-only function (Meyer's-singleton pattern,
// exactly like LivenessTracker::instance()/ReferenceChainTracker::
// instance()'s own lazy-static singletons) rather than a member of either
// singleton class: ReferenceChainTracker already depends on LivenessTracker
// (referenceChains.cpp includes livenessTracker.h and calls into it), so
// putting this counter inside either one and having the other call into it
// would introduce a circular dependency between the two headers.
namespace ClassTagAllocator {

inline volatile jlong &magnitude() {
  static volatile jlong m = 1;
  return m;
}

// Hands out a fresh negative class tag - see this file's own header comment
// for why negative, and why this must be the only place in the process that
// mints one.
inline jlong next() { return -atomicIncRelaxed(magnitude(), (jlong)1); }

// Test-only: resets the shared counter back to its starting value. Without
// this, gtest cases that assert on exact tag values (e.g. "the first class
// tagged gets -1") would see values keep climbing across every TEST_F in the
// same gtest binary, since this counter is genuinely process-wide (shared
// with LivenessTracker) rather than per-ReferenceChainTracker-instance.
inline void resetForTest() { magnitude() = 1; }

} // namespace ClassTagAllocator

#endif
