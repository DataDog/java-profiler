/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * libFuzzer target for ThreadLocal<T, CREATE_FUNC, CLEAN_FUNC> (threadLocal.h).
 *
 * ThreadLocal wraps pthread TSD to work around pthread_(get/set)specific() not
 * being safe to introduce mid-signal-handling (see the big comment at the top
 * of threadLocal.h). The interesting bug surface is the lazy create/cleanup
 * state machine across a *fresh thread's* full lifecycle — a slot that starts
 * unset, is get()/set()/clear()'d in some order, and is then torn down by the
 * pthread key destructor when the thread exits. Running everything on
 * libFuzzer's persistent driver thread would never exercise the exit-time
 * destructor path, so each input is replayed on a freshly spawned thread that
 * is joined before returning — the destructor for whatever is left in the
 * slot fires synchronously inside that join().
 *
 * Input bytes are consumed as a stream of operations against three static
 * ThreadLocal specializations that live side by side in the same input:
 *   0x00-0x0F -> tracked.get()    (lazy-creates via create_tracked() if empty)
 *   0x10-0x1F -> tracked.clear()  (invokes free_tracked() if non-empty)
 *   0x20-0x2F -> tracked.set(fresh pointer)   (caller frees any old value first,
 *                                              mirroring the documented contract)
 *   0x30-0x3F -> tracked.set(nullptr)         (frees old value; next get() must
 *                                              lazily recreate, per threadLocal.h)
 *   0x40-0x4F -> double.set(next 8 bytes as raw bit pattern)
 *   0x50-0x5F -> double.get()     (verify exact bit round-trip)
 *   0x60-0x6F -> double.clear()
 *   0x70-0x7F -> intptr.set(next 8 bytes as raw bit pattern)
 *   0x80-0x8F -> intptr.get()     (verify exact round-trip)
 *   0x90-0x9F -> intptr.clear()
 *   0xA0-0xFF -> no-op (padding / density filler for the mutator)
 *
 * Invariants verified (violation -> __builtin_trap() -> ASan/fuzzer crash):
 *   I1. get() never returns a stale/mismatched value: the payload behind the
 *       pointer/bits returned always matches what the model last stored.
 *   I2. create_tracked() runs at most once per "empty -> get()" transition and
 *       free_tracked() runs exactly once per value that ever occupied the slot
 *       (via clear(), an overwriting set(), or the pthread key destructor at
 *       thread exit) - checked via the create/free counters delta across the
 *       whole spawned-thread run.
 *   I3. set(nullptr) followed by get() lazily recreates (documented contract).
 *   I4. double/intptr specializations round-trip bit-for-bit, including NaN,
 *       infinities, subnormals and -0.0, which plain == comparison would hide.
 */

#include <stddef.h>
#include <stdint.h>

#include <atomic>
#include <cstring>
#include <system_error>
#include <thread>

#include "threadLocal.h"

namespace {

std::atomic<uint64_t> g_create_count{0};
std::atomic<uint64_t> g_free_count{0};

void *create_tracked() {
  g_create_count.fetch_add(1, std::memory_order_relaxed);
  return new int(1234);
}

void free_tracked(void *p) {
  g_free_count.fetch_add(1, std::memory_order_relaxed);
  delete static_cast<int *>(p);
}

ThreadLocal<int *, create_tracked, free_tracked> g_tracked_tl;
ThreadLocal<double> g_double_tl;
ThreadLocal<intptr_t> g_intptr_tl;

u64 take8(const uint8_t *data, size_t pos) {
  u64 v = 0;
  for (int i = 0; i < 8; i++) {
    v = (v << 8) | data[pos + i];
  }
  return v;
}

// Runs the whole decoded op sequence on the calling thread. Executed inside a
// freshly spawned std::thread so the tracked slot starts empty and whatever
// is left occupying it is torn down by the pthread key destructor at thread
// exit (join() below), exercising the path a persistent fuzzer-driver thread
// never would.
void runOnWorkerThread(const uint8_t *data, size_t size, int *expected_creates,
                        int *expected_frees) {
  bool tracked_present = false;
  int *tracked_ptr = nullptr;
  int tracked_expected = 0;
  int manual_marker_seq = 1;

  bool double_present = false;
  u64 double_expected_bits = 0;

  bool intptr_present = false;
  intptr_t intptr_expected = 0;

  size_t pos = 0;
  while (pos < size) {
    uint8_t op = data[pos++];

    if (op < 0x10) {
      // tracked.get()
      int *p = g_tracked_tl.get();
      if (!tracked_present) {
        // Empty slot with a non-null CREATE_FUNC must lazily create.
        if (p == nullptr) __builtin_trap();
        tracked_present = true;
        tracked_ptr = p;
        tracked_expected = 1234;
        (*expected_creates)++;
      } else if (p != tracked_ptr) {
        __builtin_trap();  // pointer identity must be stable across get()s
      }
      if (*p != tracked_expected) __builtin_trap();  // I1: payload corruption

    } else if (op < 0x20) {
      // tracked.clear()
      g_tracked_tl.clear();
      if (tracked_present) {
        (*expected_frees)++;
        tracked_present = false;
        tracked_ptr = nullptr;
      }

    } else if (op < 0x30) {
      // tracked.set(fresh manually-owned pointer). Per the documented
      // contract the caller frees any prior value itself before overwriting.
      if (tracked_present) {
        free_tracked(tracked_ptr);
        (*expected_frees)++;
        tracked_present = false;
      }
      // Use a negative, monotonically distinct marker so it can never be
      // confused with create_tracked()'s 1234 sentinel.
      int marker = -(manual_marker_seq++);
      int *fresh = new int(marker);
      g_tracked_tl.set(fresh);
      tracked_present = true;
      tracked_ptr = fresh;
      tracked_expected = marker;

    } else if (op < 0x40) {
      // tracked.set(nullptr): caller frees any prior value, then the next
      // get() must lazily recreate (I3).
      if (tracked_present) {
        free_tracked(tracked_ptr);
        (*expected_frees)++;
      }
      g_tracked_tl.set(nullptr);
      tracked_present = false;
      tracked_ptr = nullptr;

    } else if (op < 0x50) {
      // double.set(next 8 bytes as raw bits)
      if (pos + 7 >= size) break;
      u64 bits = take8(data, pos);
      pos += 8;
      double v;
      memcpy(&v, &bits, sizeof(v));
      g_double_tl.set(v);
      double_present = true;
      double_expected_bits = bits;

    } else if (op < 0x60) {
      // double.get() - verify exact bit pattern, not value equality (NaN-safe)
      double v = g_double_tl.get();
      u64 bits;
      memcpy(&bits, &v, sizeof(bits));
      u64 expected = double_present ? double_expected_bits : 0;
      if (bits != expected) __builtin_trap();  // I4

    } else if (op < 0x70) {
      // double.clear()
      g_double_tl.clear();
      double_present = false;

    } else if (op < 0x80) {
      // intptr.set(next 8 bytes as raw bits)
      if (pos + 7 >= size) break;
      u64 bits = take8(data, pos);
      pos += 8;
      intptr_t v = static_cast<intptr_t>(bits);
      g_intptr_tl.set(v);
      intptr_present = true;
      intptr_expected = v;

    } else if (op < 0x90) {
      // intptr.get()
      intptr_t v = g_intptr_tl.get();
      intptr_t expected = intptr_present ? intptr_expected : 0;
      if (v != expected) __builtin_trap();  // I4

    } else if (op < 0xA0) {
      // intptr.clear()
      g_intptr_tl.clear();
      intptr_present = false;

    }
    // 0xA0-0xFF: no-op padding, left for the mutator to grow/shrink sequences.
  }

  // Whatever is left in the tracked slot when this thread exits is torn down
  // by the pthread key destructor, synchronized-with by the caller's join().
  if (tracked_present) {
    (*expected_frees)++;
  }
}

}  // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) return 0;

  int expected_creates = 0;
  int expected_frees = 0;
  uint64_t create_before = g_create_count.load(std::memory_order_relaxed);
  uint64_t free_before = g_free_count.load(std::memory_order_relaxed);

  try {
    std::thread worker(runOnWorkerThread, data, size, &expected_creates,
                        &expected_frees);
    worker.join();
  } catch (const std::system_error &) {
    // Transient thread-creation failure (e.g. resource exhaustion under a
    // heavily parallel fuzzer run) - not a bug in ThreadLocal itself.
    return 0;
  }

  uint64_t create_after = g_create_count.load(std::memory_order_relaxed);
  uint64_t free_after = g_free_count.load(std::memory_order_relaxed);

  if (create_after - create_before != static_cast<uint64_t>(expected_creates)) {
    __builtin_trap();  // I2: create_tracked() ran the wrong number of times
  }
  if (free_after - free_before != static_cast<uint64_t>(expected_frees)) {
    __builtin_trap();  // I2: free_tracked() ran the wrong number of times
                        // (double free / leak from the TSD destructor path)
  }

  return 0;
}
