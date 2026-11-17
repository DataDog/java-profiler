/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _MALLOCARENAINPUTS_H
#define _MALLOCARENAINPUTS_H

// Process-static inputs of the arena detector (CPU quota, memory limit, arena
// limit, glibc version), captured once per recording. The parsers do not allocate.
struct MallocArenaInputs {
    // CPU quota in millicores, or -1 when there is no quota.
    long cpuQuotaMilli;
    // Online CPUs from OS::getCpuCount(), at least 1.
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

// Looks up `key` in a GLIBC_TUNABLES-style list ("k1=v1:k2=v2"); the last match wins.
// Sets *out only if its value parses like glibc's (sign, decimal, 0x hex or octal).
// Returns false for a null list, a missing key, or a value such as "max" or "4x".
bool parseTunableLong(const char* tunables, const char* key, long* out);

// Arena limit glibc applies: the glibc.malloc.arena_max tunable, else `env`
// (MALLOC_ARENA_MAX), ignoring non-positive values, else 8 * onlineCpus
// (2 * onlineCpus on 32-bit). *source is "tunable", "env" or "default".
long effectiveArenaLimit(const char* tunables, const char* env, int onlineCpus,
                         const char** source);

#endif // _MALLOCARENAINPUTS_H
