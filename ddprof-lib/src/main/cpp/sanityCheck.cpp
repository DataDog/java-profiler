/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cstdint>

#include "sanityCheck.h"
#include "common.h"
#include "os.h"
#include "vmEntry.h"
#include "hotspot/vmStructs.h"
#include "hotspot/vmStructs.inline.h"

// Returns the value of a size-typed JVM flag, or default_val if not found.
// ThreadStackSize is declared as `intx` on standard HotSpot builds, so the
// Intx type must be accepted here too — otherwise this call always falls
// back to default_val for that flag.
static size_t getVMSizeFlag(const char* name, size_t default_val) {
    VMFlag* f = VMFlag::find(name, {VMFlag::Type::Uintx, VMFlag::Type::Size_t,
                                     VMFlag::Type::Uint64_t, VMFlag::Type::Intx});
    if (f != NULL && f->addr() != NULL) {
        return *static_cast<size_t*>(f->addr());
    }
    return default_val;
}

// Adds b to a, clamping to UINT64_MAX on overflow instead of wrapping.
static u64 addClamped(u64 a, u64 b) {
    u64 sum = a + b;
    return sum < a ? UINT64_MAX : sum;
}

Error SanityChecker::runChecks(const Arguments& /*args*/) {
    // Static buffer for error message — safe because runChecks is called under
    // _state_lock and the result is cached as a static Error in profiler.cpp.
    static char err_buf[1024];

    // --- Gather all system info upfront ---
    int logical_cpus = OS::getCpuCount();
    int cgroup_mc = OS::getCgroupCpuMillicores();
    long container_limit = OS::getContainerMemoryLimit();
    bool containerized = (cgroup_mc > 0 || container_limit > 0);

    // -1 means "unknown" (OS::getCpuCount() failed, and no cgroup CPU limit is
    // in effect) — an unknown core count must not fail the check, since that
    // would reject on an OS query error rather than an actual resource
    // constraint.
    int effective_cores = (logical_cpus > 0) ? logical_cpus : -1;
    if (cgroup_mc > 0) {
        int cgroup_cores = cgroup_mc / 1000;
        if (effective_cores < 0 || cgroup_cores < effective_cores) {
            effective_cores = cgroup_cores;
        }
    }

    const u64 OS_RESERVE        = 128ULL * 1024 * 1024;
    const u64 PROFILER_OVERHEAD =  64ULL * 1024 * 1024;

    u64 ram = OS::getRamSize();
    u64 upper = (ram > OS_RESERVE) ? (ram - OS_RESERVE) : 0;
    if (container_limit > 0 && (u64)container_limit < upper) {
        upper = (u64)container_limit;
    }

    const size_t DEFAULT_METASPACE    = 256ULL * 1024 * 1024;
    const size_t DEFAULT_CODECACHE    = 240ULL * 1024 * 1024;
    const size_t DEFAULT_STACK_SIZE   = 512ULL * 1024;
    const int    DEFAULT_THREAD_COUNT = 200;

    // VMFlag::find() walks the HotSpot VMStructs flag table, which does not
    // exist on OpenJ9/Zing — the calls below would silently report a
    // zero-byte heap and fall back to fixed guesses for the other regions.
    // Skip the memory estimate entirely on those runtimes rather than fail
    // (or pass) the check on numbers that don't reflect the actual JVM.
    bool hotspot = !VM::isOpenJ9() && !VM::isZing();

    size_t heap_max      = hotspot ? getVMSizeFlag("MaxHeapSize",           0) : 0;
    size_t metaspace_max = hotspot ? getVMSizeFlag("MaxMetaspaceSize",      DEFAULT_METASPACE) : 0;
    size_t codecache     = hotspot ? getVMSizeFlag("ReservedCodeCacheSize", DEFAULT_CODECACHE) : 0;
    size_t stack_size    = hotspot ? getVMSizeFlag("ThreadStackSize",       DEFAULT_STACK_SIZE / 1024) * 1024 : 0;

    // MaxMetaspaceSize defaults to unbounded (max_uintx) on standard HotSpot
    // builds, so the flag is present and the default_val fallback above never
    // triggers. The exact sentinel value isn't reliable to match against —
    // debug builds align it down during ergonomics, leaving it astronomically
    // large but not bit-identical to SIZE_MAX. Any "limit" larger than total
    // available memory isn't a real limit, so normalize on that instead.
    if (metaspace_max > upper) {
        metaspace_max = DEFAULT_METASPACE;
    }

    int thread_count = DEFAULT_THREAD_COUNT;
    ProcessInfo info = {};
    if (OS::getBasicProcessInfo(OS::processId(), &info) && info.threads > 0) {
        thread_count = info.threads;
    }

    u64 gc_overhead = (u64)heap_max * 30 / 100;
    u64 lower = (u64)heap_max;
    lower = addClamped(lower, (u64)metaspace_max);
    lower = addClamped(lower, (u64)codecache);
    lower = addClamped(lower, gc_overhead);
    lower = addClamped(lower, (u64)thread_count * (u64)stack_size);
    lower = addClamped(lower, PROFILER_OVERHEAD);

    // --- Run checks ---
    // Per DataDog/java-profiler#480, the profiler refuses to run with fewer
    // than 1 core. An unknown core count (-1) never fails this check — see
    // the effective_cores computation above.
    bool cpu_fail = (effective_cores >= 0 && effective_cores < 1);
    bool mem_fail = (hotspot && upper > 0 && lower > upper);

    if (!cpu_fail && !mem_fail) {
        return Error::OK;
    }

    if (cpu_fail) {
        LOG_WARN("Sanity check failed: effective CPU count is %d (logical=%d, cgroup=%dmc).",
                 effective_cores, logical_cpus, cgroup_mc);
    }
    if (mem_fail) {
        LOG_WARN("Sanity check failed: estimated memory requirement (%llu MB) exceeds available memory (%llu MB).",
                 (unsigned long long)(lower / (1024 * 1024)),
                 (unsigned long long)(upper / (1024 * 1024)));
    }

    snprintf(err_buf, sizeof(err_buf),
             "[sanity] cpu=%s,memory=%s,"
             "logical_cores=%d,cgroup_millicores=%d,effective_cores=%d,"
             "ram_mb=%llu,container_limit_mb=%lld,upper_mb=%llu,lower_mb=%llu,"
             "heap_mb=%llu,metaspace_mb=%llu,codecache_mb=%llu,"
             "gc_overhead_mb=%llu,threads=%d,stack_kb=%llu,profiler_mb=%llu,"
             "containerized=%s",
             cpu_fail ? "fail" : "ok",
             mem_fail ? "fail" : "ok",
             logical_cpus, cgroup_mc, effective_cores,
             (unsigned long long)(ram / (1024 * 1024)),
             container_limit > 0 ? (long long)(container_limit / (1024 * 1024)) : -1LL,
             (unsigned long long)(upper / (1024 * 1024)),
             (unsigned long long)(lower / (1024 * 1024)),
             (unsigned long long)(heap_max / (1024 * 1024)),
             (unsigned long long)(metaspace_max / (1024 * 1024)),
             (unsigned long long)(codecache / (1024 * 1024)),
             (unsigned long long)(gc_overhead / (1024 * 1024)),
             thread_count,
             (unsigned long long)(stack_size / 1024),
             (unsigned long long)(PROFILER_OVERHEAD / (1024 * 1024)),
             containerized ? "true" : "false");
    return Error(err_buf);
}
