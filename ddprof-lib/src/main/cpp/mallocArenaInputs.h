/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _MALLOCARENAINPUTS_H
#define _MALLOCARENAINPUTS_H

// Process-static inputs of the glibc malloc arena detector: the CPU quota, the
// memory limit, the arena limit glibc applies, and the glibc version. They are
// captured once per recording. The parsers are pure functions and do not
// allocate.
struct MallocArenaInputs {
    // CPU quota in millicores, or -1 when there is no quota.
    long cpuQuotaMilli;
    // Online CPUs, as OS::getCpuCount() reports them.
    int onlineCpus;
    // Arena limit glibc applies: the arena_max tunable, MALLOC_ARENA_MAX, or
    // the default of 8 arenas per online CPU (2 on 32-bit).
    long arenaLimit;
    // "tunable", "env" or "default". A string literal.
    const char* arenaLimitSource;
    // Memory limit in bytes, or -1 when unknown.
    long memoryLimit;
    // "cgroup", "physical" or "unknown". A string literal.
    const char* memoryLimitSource;
    // Version string from gnu_get_libc_version(), or "" when the build does
    // not use glibc.
    char glibcVersion[16];
    // True when glibc.malloc.hugetlb is 2 or more. That value changes the heap
    // size that the arena walk assumes.
    bool hugetlbHeaps;

    static MallocArenaInputs capture();
};

// Looks up `key` in a GLIBC_TUNABLES style list ("k1=v1:k2=v2"). Returns true
// and sets *out only when the key is present as a whole key with a value that
// is a complete decimal integer with an optional leading '-'
// (no leading whitespace or '+'). Returns false for a null list, a missing key
// or a value such as "max".
bool parseTunableLong(const char* tunables, const char* key, long* out);

// Returns the arena limit glibc applies. The glibc.malloc.arena_max tunable in
// `tunables` has precedence over `env` (the MALLOC_ARENA_MAX value). A value
// that is not a positive integer is ignored. Otherwise the limit is 8 *
// onlineCpus (2 * onlineCpus when pointers are 32-bit). *source is set to
// "tunable", "env" or "default".
long effectiveArenaLimit(const char* tunables, const char* env, int onlineCpus,
                         const char** source);

#endif // _MALLOCARENAINPUTS_H
