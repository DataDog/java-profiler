/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CLASS_TAG_ALLOCATOR_H
#define _CLASS_TAG_ALLOCATOR_H

#include "arch.h"
#include <jni.h>

// Process-wide allocator of negative JVMTI class-object tags, shared by
// ReferenceChainTracker (tags each loaded class's own jclass via
// resolveLoadedClasses(), referenceChains.cpp) and LivenessTracker
// (KlassPopulationEntry::stable_class_tag, livenessTracker.h). One shared
// counter: two independent counters could mint the same value for two
// different classes. heapReferenceCallback() (referenceChains.cpp)
// identifies a pre-tagged class object by `*tag_ptr < 0` (ordinary admitted
// instances carry positive nextTag() values), so tags must stay negative.
// A free function: neither singleton header needs to depend on the other.
namespace ClassTagAllocator {

inline volatile jlong &magnitude() {
  static volatile jlong m = 1;
  return m;
}

// Hands out a fresh negative class tag; the only minting site in the process.
inline jlong next() { return -atomicIncRelaxed(magnitude(), (jlong)1); }

// Test-only: resets the process-wide counter (shared with LivenessTracker).
inline void resetForTest() { magnitude() = 1; }

} // namespace ClassTagAllocator

#endif
