/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// <stdlib.h> comes first: on glibc it pulls in features.h, which defines
// __GLIBC__ for the guards below.
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

#include "mallocArenaInputs.h"

#include "os.h"

#if defined(__linux__) && defined(__GLIBC__)
  #include <gnu/libc-version.h>
#endif

static const char KEY_ARENA_MAX[] = "glibc.malloc.arena_max";
static const char KEY_HUGETLB[] = "glibc.malloc.hugetlb";

// Parses [begin, end) as a decimal integer with an optional leading '-'. The
// whole range must be consumed. Leading whitespace and a leading '+' are
// rejected, although strtol would accept them.
static bool parseLongRange(const char* begin, const char* end, long* out) {
    char buf[32];
    size_t len = (size_t)(end - begin);
    if (len == 0 || len >= sizeof(buf) || *begin == '+' || isspace((unsigned char)*begin)) {
        return false;
    }
    memcpy(buf, begin, len);
    buf[len] = '\0';
    char* parsed_end = NULL;
    errno = 0;
    long value = strtol(buf, &parsed_end, 10);
    if (errno != 0 || parsed_end != buf + len) {
        return false;
    }
    *out = value;
    return true;
}

bool parseTunableLong(const char* tunables, const char* key, long* out) {
    if (tunables == NULL || key == NULL) {
        return false;
    }
    size_t key_len = strlen(key);
    const char* p = tunables;
    while (*p != '\0') {
        const char* end = strchr(p, ':');
        if (end == NULL) {
            end = p + strlen(p);
        }
        if ((size_t)(end - p) > key_len && strncmp(p, key, key_len) == 0 && p[key_len] == '=') {
            return parseLongRange(p + key_len + 1, end, out);
        }
        p = (*end == ':') ? end + 1 : end;
    }
    return false;
}

long effectiveArenaLimit(const char* tunables, const char* env, int onlineCpus,
                         const char** source) {
    long value;
    if (parseTunableLong(tunables, KEY_ARENA_MAX, &value) && value > 0) {
        *source = "tunable";
        return value;
    }
    if (env != NULL && parseLongRange(env, env + strlen(env), &value) && value > 0) {
        *source = "env";
        return value;
    }
    *source = "default";
    return (long)(sizeof(void*) == 8 ? 8 : 2) * onlineCpus;
}

MallocArenaInputs MallocArenaInputs::capture() {
    MallocArenaInputs in;
    in.cpuQuotaMilli = OS::getCgroupCpuMillicores();
    if (in.cpuQuotaMilli <= 0) {
        in.cpuQuotaMilli = -1;
    }
    in.onlineCpus = OS::getCpuCount();
    if (in.onlineCpus < 1) {
        in.onlineCpus = 1;
    }

    const char* tunables = getenv("GLIBC_TUNABLES");
    in.arenaLimit = effectiveArenaLimit(tunables, getenv("MALLOC_ARENA_MAX"),
                                        in.onlineCpus, &in.arenaLimitSource);

    long limit = OS::getContainerMemoryLimit();
    if (limit > 0) {
        in.memoryLimit = limit;
        in.memoryLimitSource = "cgroup";
    } else {
        long ram = (long)OS::getRamSize();
        if (ram > 0) {
            in.memoryLimit = ram;
            in.memoryLimitSource = "physical";
        } else {
            in.memoryLimit = -1;
            in.memoryLimitSource = "unknown";
        }
    }

    in.glibcVersion[0] = '\0';
#if defined(__linux__) && defined(__GLIBC__)
    strncpy(in.glibcVersion, gnu_get_libc_version(), sizeof(in.glibcVersion) - 1);
    in.glibcVersion[sizeof(in.glibcVersion) - 1] = '\0';
#endif

    long hugetlb;
    in.hugetlbHeaps = parseTunableLong(tunables, KEY_HUGETLB, &hugetlb) && hugetlb >= 2;
    return in;
}
