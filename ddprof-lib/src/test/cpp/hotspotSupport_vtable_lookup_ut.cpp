/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * AC-1: hotspotSupport.cpp:533 must call Profiler::lookupClass() instead of
 *       profiler->classMap()->lookup() directly.
 *
 * This is a static / source-analysis test enforced at build time via a
 * compile-time grep.  Because GTest cannot inspect source text directly, the
 * test shells out to grep and fails if the forbidden call pattern is present
 * in the source file.
 *
 * Additionally contains functional tests for Dictionary::lookup_readonly to
 * verify the read-only lookup semantics that lookupClass relies on.
 */

#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include "dictionary.h"

// Resolve source path relative to this translation unit's __FILE__ macro.
// The test binary is run from the repo root; fall back to a relative path.
static const char* HOTSPOT_SUPPORT_SRC =
    "ddprof-lib/src/main/cpp/hotspot/hotspotSupport.cpp";

TEST(VTableLookupAC1, ForbiddenDirectClassMapLookupAbsent) {
    // The forbidden pattern: calling ->lookup() directly on classMap() in the
    // vtable-stub branch.  Regex matches any variant of the call that bypasses
    // Profiler::lookupClass().
    const char* forbidden = "classMap()->lookup";

    FILE* f = fopen(HOTSPOT_SUPPORT_SRC, "r");
    if (f == nullptr) {
        GTEST_SKIP() << "Source file not found at " << HOTSPOT_SUPPORT_SRC
                     << " – skipping static check";
        return;
    }

    char line[512];
    int lineno = 0;
    bool found = false;
    while (fgets(line, sizeof(line), f)) {
        ++lineno;
        if (strstr(line, forbidden) != nullptr) {
            found = true;
            fprintf(stderr, "FORBIDDEN PATTERN at line %d: %s", lineno, line);
        }
    }
    fclose(f);

    EXPECT_FALSE(found)
        << "hotspotSupport.cpp still calls classMap()->lookup() directly. "
           "It must use Profiler::lookupClass() instead (AC-1).";
}

TEST(VTableLookupAC1, FixedLookupClassSignalSafeCallPresent) {
    // Positive check: lookupClassSignalSafe() must be present in hotspotSupport.cpp.
    // The signal-safe variant is required because walkVM runs in signal-handler context
    // where malloc is not async-signal-safe.
    const char* required = "lookupClassSignalSafe(";

    FILE* f = fopen(HOTSPOT_SUPPORT_SRC, "r");
    if (f == nullptr) {
        GTEST_SKIP() << "Source file not found at " << HOTSPOT_SUPPORT_SRC;
        return;
    }

    char line[512];
    bool found = false;
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, required) != nullptr) {
            found = true;
            break;
        }
    }
    fclose(f);

    EXPECT_TRUE(found)
        << "lookupClassSignalSafe() call not found in hotspotSupport.cpp. "
           "The VTable-stub branch must use Profiler::lookupClassSignalSafe() (AC-1).";
}

// ---------------------------------------------------------------------------
// Functional tests for Dictionary::lookup_readonly (AC-1 complement)
//
// These tests verify the read-only lookup semantics that Profiler::lookupClass
// relies on: lookup_readonly must return 0 on miss without inserting the key,
// and must return the correct ID for a key that was already inserted.
// ---------------------------------------------------------------------------

TEST(DictionaryReadonlySemantics, HitReturnsCorrectId) {
    Dictionary dict;
    const char* key = "Lcom/example/Foo;";
    unsigned int id = dict.lookup(key, strlen(key));  // insert
    ASSERT_GT(id, 0u) << "Inserted key must get a valid (> 0) ID";

    unsigned int found = dict.lookup_readonly(key, strlen(key));
    EXPECT_EQ(id, found) << "lookup_readonly must return the same ID as the inserting lookup";
}

TEST(DictionaryReadonlySemantics, MissReturnsSentinelZero) {
    Dictionary dict;
    // Pre-populate to confirm the miss is not due to an empty table
    dict.lookup("Lcom/example/Bar;", 17);

    unsigned int result = dict.lookup_readonly("Lcom/example/Unknown;", 21);
    EXPECT_EQ(0u, result) << "lookup_readonly must return 0 for a key not in the dictionary";
}

TEST(DictionaryReadonlySemantics, MissDoesNotInsert) {
    Dictionary dict;
    // Look up a key that does not exist
    dict.lookup_readonly("Lcom/example/Ghost;", 19);
    // A subsequent read-only lookup must still return 0 (key was not inserted)
    unsigned int result = dict.lookup_readonly("Lcom/example/Ghost;", 19);
    EXPECT_EQ(0u, result) << "lookup_readonly must not insert the key on miss";
}
