/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SCOPED_PRESERVATION_COPY_FAILURE_H
#define _SCOPED_PRESERVATION_COPY_FAILURE_H

#include "callTraceHashTable.h"

// Native fixtures run this override on normal threads, with no concurrent copy.
class ScopedPreservationCopyFailure {
    u64 _previous;

public:
    explicit ScopedPreservationCopyFailure(u64 id)
        : _previous(CallTraceHashTable::failedPreservationIdForTest) {
        CallTraceHashTable::failedPreservationIdForTest = id;
    }
    ~ScopedPreservationCopyFailure() {
        CallTraceHashTable::failedPreservationIdForTest = _previous;
    }
    ScopedPreservationCopyFailure(const ScopedPreservationCopyFailure&) = delete;
    ScopedPreservationCopyFailure& operator=(const ScopedPreservationCopyFailure&) = delete;
};

#endif // _SCOPED_PRESERVATION_COPY_FAILURE_H
