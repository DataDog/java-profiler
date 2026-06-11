/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * libFuzzer target for CallTraceStorage / CallTraceHashTable.
 *
 * Input bytes are consumed as a stream of operations:
 *   op byte < 0x80  → put(1 frame): next byte is bci (0-127); method_id derived
 *                     from a monotone counter so every call produces a unique trace,
 *                     letting the corpus naturally drive past the 49152-entry
 *                     expansion threshold and create a multi-node _prev chain.
 *   0x80 ≤ op < 0xC0 → processTraces()
 *   op ≥ 0xC0       → clear()
 *
 * Invariants verified (violation → __builtin_trap() → ASan/fuzzer crash):
 *   I1. Every trace successfully returned by put() since the last processTraces()
 *       or clear() must appear in the next processTraces() callback.
 *   I2. Immediately after clear(), processTraces() must see exactly 1 trace
 *       (the static DROPPED_TRACE_ID sentinel).
 *
 * ASan+UBSan are enabled by the fuzzer build config; heap-use-after-free from
 * a dangling _prev pointer (defect C) and non-atomic _table accesses (defect B)
 * will be caught automatically if regressions are introduced.
 */

#include <stddef.h>
#include <stdint.h>
#include <unordered_set>

#include "callTraceStorage.h"

// Reuse the storage across fuzz calls to amortise the mmap cost of the initial
// 65536-slot LongHashTable allocation.  clear() resets logical state without
// releasing the underlying allocator pages, so subsequent runs recycle memory
// and exercise the reuse path that is most likely to surface UAF bugs.
static CallTraceStorage* g_storage = nullptr;

extern "C" int LLVMFuzzerInitialize(int* /*argc*/, char*** /*argv*/) {
    g_storage = new CallTraceStorage();
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (size < 2) return 0;

    g_storage->clear();

    // Shadow set: trace IDs put() successfully since the last processTraces()/clear().
    std::unordered_set<u64> pending;
    bool just_cleared = true;  // true immediately after clear() or at start
    int  put_seq      = 0;     // monotone counter → unique method_id per call

    size_t pos = 0;
    while (pos < size) {
        uint8_t op = data[pos++];

        if (op < 0x80) {
            // put() — consume one bci byte
            if (pos >= size) break;
            int bci = (int)(data[pos++] & 0x7F);

            ASGCT_CallFrame frame;
            frame.bci       = bci;
            // Derive a unique method_id from the sequential counter so repeated
            // bci bytes still produce distinct traces and eventually cross the
            // 49152-entry expansion threshold.
            frame.method_id = reinterpret_cast<jmethodID>(
                static_cast<uintptr_t>(0x10000ULL + (u64)(put_seq & 0xFFFF)));
            put_seq++;

            u64 id = g_storage->put(1, &frame, false, 1);
            if (id > 0 && id != CallTraceStorage::DROPPED_TRACE_ID) {
                pending.insert(id);
                just_cleared = false;
            }

        } else if (op < 0xC0) {
            // processTraces() — verify I1 and I2
            std::unordered_set<u64> seen;
            g_storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
                for (CallTrace* t : traces) {
                    if (t) seen.insert(t->trace_id);
                }
            });

            if (just_cleared) {
                // I2: after clear() only the sentinel should be present.
                // pending is empty; seen should contain exactly DROPPED_TRACE_ID.
                if (seen.size() != 1 ||
                    seen.find(CallTraceStorage::DROPPED_TRACE_ID) == seen.end()) {
                    __builtin_trap();
                }
            } else {
                // I1: every successfully put trace must appear in the snapshot.
                for (u64 id : pending) {
                    if (seen.find(id) == seen.end()) {
                        __builtin_trap();
                    }
                }
            }
            pending.clear();
            just_cleared = false;

        } else {
            // clear()
            g_storage->clear();
            pending.clear();
            put_seq     = 0;
            just_cleared = true;
        }
    }

    return 0;
}
