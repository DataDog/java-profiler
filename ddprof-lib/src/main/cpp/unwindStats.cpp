/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include "unwindStats.h"
#include "nativeMem.h"

// initialize static members
SpinLock UnwindStats::_lock;
UnwindFailures UnwindStats::_unwind_failures;

// Heap footprint of the two arrays each instance owns. The ctor records it
// under NM_THREAD_LOCAL and the dtor gives it back, so it lives in one constant
// to keep the two sides from drifting.
static constexpr size_t UNWIND_FAILURES_ARRAYS_SIZE =
    MAX_UNWIND_FAILURE_NAMES * MAX_NAME_LENGTH * sizeof(char) +
    MAX_UNWIND_FAILURE_NAMES * (UNWIND_FAILURE_ANY + 1) * sizeof(u64);

UnwindFailures::UnwindFailures() : _nameCount(0) {
    _names = new char[MAX_UNWIND_FAILURE_NAMES][MAX_NAME_LENGTH];
    _counters = new u64[MAX_UNWIND_FAILURE_NAMES][UNWIND_FAILURE_ANY + 1];
    NativeMem::record(NM_THREAD_LOCAL, (long long)UNWIND_FAILURES_ARRAYS_SIZE);
    reset();
}

UnwindFailures::~UnwindFailures() {
     delete[] _names;
     delete[] _counters;
     // ProfiledThread holds one of these by value, so without this the gauge
     // grows by UNWIND_FAILURES_ARRAYS_SIZE for every thread that comes and
     // goes -- forTid()/freeValue() only balance sizeof(ProfiledThread) itself.
     // Recorded after the deletes, matching the other NM_THREAD_LOCAL
     // decrement sites in threadLocalData.cpp.
     NativeMem::record(NM_THREAD_LOCAL, -(long long)UNWIND_FAILURES_ARRAYS_SIZE);
}

void UnwindFailures::reset() {
    memset((void*)_names, 0, MAX_UNWIND_FAILURE_NAMES * MAX_NAME_LENGTH);
    memset((void*)_counters, 0, MAX_UNWIND_FAILURE_NAMES * (UNWIND_FAILURE_ANY + 1) * sizeof(u64));
    _nameCount = 0;
}
