/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "jvmHeap.h"

// JDK-8356848 ("Separate Metaspace and GC printing"), present since JDK 25 GA,
// inserted a GCMetaspaceLog* field into CollectedHeap ahead of
// _capacity_at_last_gc/_used_at_last_gc, shifting both fields one pointer
// width later on 64-bit builds. These tests pin the two wrapper layouts and
// the version gate that selects between them, so a future edit that breaks
// either is caught here instead of silently misreporting heap usage.

// The JDK 25+ layout must be exactly one pointer wider than the pre-25
// layout (the inserted _metaspace_log field) - any other size delta means
// the wrappers no longer model the documented upstream change.
TEST(CollectedHeapWrapperLayoutTest, V25PlusIsExactlyOnePointerWiderThanPre25) {
    EXPECT_EQ(sizeof(CollectedHeapWrapperPre25) + sizeof(void*),
              sizeof(CollectedHeapWrapperV25Plus));
}

// Below the JDK-8356848 boundary, the accessors must read through the
// single-pointer-prefix (pre-25) layout.
TEST(CollectedHeapAccessorTest, BelowVersion25UsesPre25Layout) {
    CollectedHeapWrapperPre25 heap;
    heap._capacity_at_last_gc = 4096;
    heap._used_at_last_gc = 1024;

    EXPECT_EQ(1024u, collectedHeapUsedAtLastGc(&heap, 24));
    EXPECT_EQ(4096u, collectedHeapCapacityAtLastGc(&heap, 24));
}

// At and above the JDK-8356848 boundary, the accessors must read through the
// dual-pointer-prefix (25+) layout.
TEST(CollectedHeapAccessorTest, FromVersion25UsesV25PlusLayout) {
    CollectedHeapWrapperV25Plus heap;
    heap._capacity_at_last_gc = 8ull * 1024 * 1024 * 1024; // 8GB
    heap._used_at_last_gc = 2ull * 1024 * 1024 * 1024;     // 2GB

    EXPECT_EQ(2ull * 1024 * 1024 * 1024, collectedHeapUsedAtLastGc(&heap, 25));
    EXPECT_EQ(8ull * 1024 * 1024 * 1024, collectedHeapCapacityAtLastGc(&heap, 25));

    // The gate is version-wide, not GC-algorithm-specific or ZGC-only.
    EXPECT_EQ(2ull * 1024 * 1024 * 1024, collectedHeapUsedAtLastGc(&heap, 26));
    EXPECT_EQ(2ull * 1024 * 1024 * 1024, collectedHeapUsedAtLastGc(&heap, 30));
}

// Reproduces the reported symptom: a JDK 25+ CollectedHeap read through the
// pre-25 layout (i.e. without the version gate) reports its real capacity
// where used-at-last-gc is expected, because the pre-25 layout is missing
// the _metaspace_log field the real struct has ahead of these two counters.
// This is the regression the version gate exists to prevent.
TEST(CollectedHeapAccessorTest, MissingVersionGateMisreadsCapacityAsUsed) {
    CollectedHeapWrapperV25Plus jdk25_heap;
    jdk25_heap._capacity_at_last_gc = 7500ull * 1024 * 1024; // ~7.5GB, observed symptom
    jdk25_heap._used_at_last_gc = 2190ull * 1024 * 1024;     // ~2.19GB, real used bytes

    // Correct: version-gated read on a JDK 25+ heap returns the real used bytes.
    EXPECT_EQ(jdk25_heap._used_at_last_gc, collectedHeapUsedAtLastGc(&jdk25_heap, 25));

    // Buggy: reading the same JDK 25+ heap with a pre-25 java_version
    // reproduces the reported bug - capacity comes back where used was expected.
    EXPECT_EQ(jdk25_heap._capacity_at_last_gc, collectedHeapUsedAtLastGc(&jdk25_heap, 24));
    EXPECT_NE(jdk25_heap._used_at_last_gc, collectedHeapUsedAtLastGc(&jdk25_heap, 24));
}

// Regression test for the JDK 8 GA version-parsing trap: get_hotspot_version()
// misparses java.vm.version="25.0-b70" as 25 (the prop_value[3] > '0' guard
// fails for '0'), so a hotspot_version gate would apply the V25+ layout to a
// JDK 8 CollectedHeap. Gating on java_version() instead avoids this: JDK 8
// (java_version == 8) selects the pre-25 layout regardless of the misparsed
// hotspot_version.
TEST(CollectedHeapAccessorTest, Jdk8GaUsesPre25LayoutDespiteMisparsedHotspotVersion) {
    CollectedHeapWrapperPre25 heap;
    heap._capacity_at_last_gc = 4096;
    heap._used_at_last_gc = 1024;

    // java_version == 8 must select the pre-25 layout even though
    // hotspot_version() would have returned 25 on JDK 8 GA ("25.0-b70").
    EXPECT_EQ(1024u, collectedHeapUsedAtLastGc(&heap, 8));
    EXPECT_EQ(4096u, collectedHeapCapacityAtLastGc(&heap, 8));
}

// Sanity: used-at-last-gc must never exceed capacity-at-last-gc - this is a
// basic heap invariant, and a field swap in either wrapper (or in the gate)
// would violate it for realistic values.
TEST(CollectedHeapAccessorTest, UsedNeverExceedsCapacityPre25) {
    CollectedHeapWrapperPre25 heap;
    heap._capacity_at_last_gc = 1000;
    heap._used_at_last_gc = 250;

    EXPECT_LE(collectedHeapUsedAtLastGc(&heap, 17), collectedHeapCapacityAtLastGc(&heap, 17));
}

TEST(CollectedHeapAccessorTest, UsedNeverExceedsCapacityV25Plus) {
    CollectedHeapWrapperV25Plus heap;
    heap._capacity_at_last_gc = 1000;
    heap._used_at_last_gc = 250;

    EXPECT_LE(collectedHeapUsedAtLastGc(&heap, 25), collectedHeapCapacityAtLastGc(&heap, 25));
}
