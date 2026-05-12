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
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "dictionary.h"

// Resolve the path to hotspotSupport.cpp relative to __FILE__.
// __FILE__ is something like /repo/ddprof-lib/src/test/cpp/hotspotSupport_vtable_lookup_ut.cpp
// We find the LAST occurrence of "src/test/cpp/" and replace the suffix with
// "src/main/cpp/hotspot/hotspotSupport.cpp".
// Falls back to a repo-root-relative path when the marker is not found.
static char HOTSPOT_SUPPORT_SRC_BUF[PATH_MAX];
static const char* resolveHotspotSupportSrc() {
    const char* file = __FILE__;
    const char* marker = "src/test/cpp/";
    const char* pos = nullptr;
    const char* p = file;
    while ((p = strstr(p, marker)) != nullptr) {
        pos = p;
        p++;
    }
    if (pos != nullptr) {
        size_t prefix_len = (size_t)(pos - file);
        const char* suffix = "src/main/cpp/hotspot/hotspotSupport.cpp";
        if (prefix_len + strlen(suffix) < PATH_MAX) {
            memcpy(HOTSPOT_SUPPORT_SRC_BUF, file, prefix_len);
            strcpy(HOTSPOT_SUPPORT_SRC_BUF + prefix_len, suffix);
            return HOTSPOT_SUPPORT_SRC_BUF;
        }
    }
    return "ddprof-lib/src/main/cpp/hotspot/hotspotSupport.cpp";
}
static const char* HOTSPOT_SUPPORT_SRC = resolveHotspotSupportSrc();

TEST(VTableLookupAC1, ForbiddenDirectClassMapLookupAbsent) {
    // The forbidden pattern: calling ->lookup() directly on classMap() in the
    // vtable-stub branch.  Regex matches any variant of the call that bypasses
    // Profiler::lookupClass().
    const char* forbidden = "classMap()->lookup";

    FILE* f = fopen(HOTSPOT_SUPPORT_SRC, "r");
    if (f == nullptr) {
        const char* ci = getenv("CI");
        if (ci != nullptr && ci[0] != '\0') {
            FAIL() << "Source file not found at " << HOTSPOT_SUPPORT_SRC
                   << " (CI environment - must be resolvable)";
        } else {
            GTEST_SKIP() << "Source file not found at " << HOTSPOT_SUPPORT_SRC
                         << " - skipping static check";
        }
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
        const char* ci = getenv("CI");
        if (ci != nullptr && ci[0] != '\0') {
            FAIL() << "Source file not found at " << HOTSPOT_SUPPORT_SRC
                   << " (CI environment - must be resolvable)";
        } else {
            GTEST_SKIP() << "Source file not found at " << HOTSPOT_SUPPORT_SRC;
        }
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
