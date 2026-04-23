/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "sanityCheck.h"
#include "common.h"
#include "os.h"
#include "hotspot/vmStructs.h"

// Returns the value of a size-typed JVM flag, or default_val if not found.
static size_t getVMSizeFlag(const char* name, size_t default_val) {
    VMFlag* f = VMFlag::find(name, {VMFlag::Type::Uintx, VMFlag::Type::Size_t, VMFlag::Type::Uint64_t});
    if (f != NULL && f->addr() != NULL) {
        return *static_cast<size_t*>(f->addr());
    }
    return default_val;
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

    int effective_cores = logical_cpus;
    if (cgroup_mc > 0) {
        int cgroup_cores = cgroup_mc / 1000;
        if (cgroup_cores < effective_cores) {
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

    size_t heap_max      = getVMSizeFlag("MaxHeapSize",             0);
    size_t metaspace_max = getVMSizeFlag("MaxMetaspaceSize",        DEFAULT_METASPACE);
    size_t codecache     = getVMSizeFlag("ReservedCodeCacheSize",   DEFAULT_CODECACHE);
    size_t stack_size    = getVMSizeFlag("ThreadStackSize",         DEFAULT_STACK_SIZE / 1024) * 1024;

    int thread_count = DEFAULT_THREAD_COUNT;
    ProcessInfo info = {};
    if (OS::getBasicProcessInfo(OS::processId(), &info) && info.threads > 0) {
        thread_count = info.threads;
    }

    u64 gc_overhead = (u64)heap_max * 30 / 100;
    u64 lower = (u64)heap_max + (u64)metaspace_max + (u64)codecache
                + gc_overhead
                + (u64)thread_count * (u64)stack_size
                + PROFILER_OVERHEAD;

    // --- Run checks ---
    bool cpu_fail = (effective_cores < 1);
    bool mem_fail = (upper > 0 && lower > upper);

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
