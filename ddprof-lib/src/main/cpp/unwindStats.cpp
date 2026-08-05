/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include "unwindStats.h"

// initialize static members
SpinLock UnwindStats::_lock;
UnwindFailures UnwindStats::_unwind_failures;

UnwindFailures::UnwindFailures() : _nameCount(0) {
    _names = new char[MAX_UNWIND_FAILURE_NAMES][MAX_NAME_LENGTH];
     _counters = new u64[MAX_UNWIND_FAILURE_NAMES][UNWIND_FAILURE_ANY + 1];
     reset();
}

UnwindFailures::~UnwindFailures() {
     delete[] _names;
     delete[] _counters;
}

void UnwindFailures::reset() {
    memset((void*)_names, 0, MAX_UNWIND_FAILURE_NAMES * MAX_NAME_LENGTH);
    memset((void*)_counters, 0, MAX_UNWIND_FAILURE_NAMES * (UNWIND_FAILURE_ANY + 1) * sizeof(u64));
    _nameCount = 0;
}
