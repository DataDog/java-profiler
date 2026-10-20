/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nativeAllocationUsdt.h"

#include <cmath>
#include <limits.h>

#if defined(__linux__)
#define USDT_ARG_CONSTRAINT r
#include "vendor/libbpf/usdt.h"

alignas(2) USDT_DEFINE_SEMA(ddheap_alloc);

bool isNativeAllocationUsdtEnabled() noexcept {
    return __atomic_load_n(&USDT_SEMA(ddheap_alloc).active,
                           __ATOMIC_RELAXED) != 0;
}

#if defined(__GNUC__) && !defined(__clang__)
__attribute__((noinline, noclone, used))
#else
__attribute__((noinline, used))
#endif
void emitNativeAllocationUsdt(void* address, uint64_t size,
                              uint64_t weighted_bytes) noexcept {
#if defined(__x86_64__)
    register void* probe_address asm("rdi") = address;
    register uint64_t probe_size asm("rsi") = size;
    register uint64_t probe_weight asm("rdx") = weighted_bytes;
#elif defined(__aarch64__)
    register void* probe_address asm("x0") = address;
    register uint64_t probe_size asm("x1") = size;
    register uint64_t probe_weight asm("x2") = weighted_bytes;
#else
#error "Native allocation USDT supports only Linux x86-64 and AArch64"
#endif
    USDT_WITH_EXPLICIT_SEMA(ddheap_alloc, ddheap, alloc,
                            probe_address, probe_size, probe_weight);
}

#ifdef UNIT_TEST
void setNativeAllocationUsdtSemaphoreForTest(uint16_t value) noexcept {
    __atomic_store_n(&USDT_SEMA(ddheap_alloc).active, value,
                     __ATOMIC_RELAXED);
}
#endif

#else

bool isNativeAllocationUsdtEnabled() noexcept {
    return false;
}

void emitNativeAllocationUsdt(void*, uint64_t, uint64_t) noexcept {
}

#ifdef UNIT_TEST
void setNativeAllocationUsdtSemaphoreForTest(uint16_t) noexcept {
}
#endif

#endif

uint64_t nativeAllocationUsdtWeight(size_t size, uint64_t interval) noexcept {
    if (size == 0 || interval <= 1) {
        return size;
    }

    double probability = -expm1(-(double)size / (double)interval);
    double weighted_bytes = (double)size / probability;
    if (!std::isfinite(weighted_bytes) || weighted_bytes >= (double)INT64_MAX) {
        return (uint64_t)INT64_MAX;
    }
    if (weighted_bytes <= 1.0) {
        return 1;
    }
    return (uint64_t)llround(weighted_bytes);
}
