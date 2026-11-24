// Copyright 2026, Datadog, Inc.

#ifndef _PROFILER_RANGE_TEST_SUPPORT_H
#define _PROFILER_RANGE_TEST_SUPPORT_H

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include "profiler.h"
#include "safeAccess.h"

extern "C" int safecopy_impl(void* dst, const void* src, size_t len);

// Installs [lo, hi) widened to the SafeAccess asm stubs. The production library
// range always contains them, and the crash-handler PC prefilter chains faults
// outside the range, so a SafeAccess probe there would otherwise kill the test.
inline void setProfilerRangeWithSafeAccessForTest(uintptr_t& lo, uintptr_t& hi) {
    constexpr uintptr_t kStubMargin = 4096;
    const uintptr_t stubs[] = {
        reinterpret_cast<uintptr_t>(&safefetch32_impl),
        reinterpret_cast<uintptr_t>(&safefetch64_impl),
        reinterpret_cast<uintptr_t>(&safestore32_impl),
        reinterpret_cast<uintptr_t>(&safestore64_impl),
        reinterpret_cast<uintptr_t>(&safecopy_impl),
    };
    for (uintptr_t stub : stubs) {
        lo = std::min(lo, stub - kStubMargin);
        hi = std::max(hi, stub + kStubMargin);
    }
    Profiler::setAddressRangeForTest(lo, hi);
}

#endif // _PROFILER_RANGE_TEST_SUPPORT_H
