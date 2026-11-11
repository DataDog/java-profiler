/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "jitCodeCache.h"

#include <stdlib.h>
#include <string.h>

#include "counters.h"
#include "hotspot/vmStructs.h"
#include "threadLocalData.h"
#ifdef __aarch64__
#include "hotspot/stubUnwindInfo.h"
#endif

SpinLock JitCodeCache::_stubs_lock;
Mutex JitCodeCache::_stubs_write_lock;
CodeCache JitCodeCache::_runtime_stubs("[stubs]");
std::atomic<const void *> JitCodeCache::_call_stub_begin = { nullptr };
std::atomic<const void *> JitCodeCache::_call_stub_end = { nullptr };

#ifdef __aarch64__
// Registry of precomputed unwind info, sorted by start address so the
// signal-handler lookup is a binary search. Inserts happen under the
// exclusive _stubs_lock and each entry's info pointer is fixed at
// registration time, so a reader holding the shared lock sees a stable
// snapshot. A full array is replaced by a larger copy, allocated and filled
// before the exclusive lock and swapped in under it; the old array is freed
// only after the unlock, when no reader can still hold it. The full-barrier
// CAS in SpinLock publishes the new contents. Published info objects are
// never freed -- a signal handler may still be reading one -- matching the
// lifetime of the stub name strings.
StubUnwindEntry* JitCodeCache::_stub_unwind = nullptr;
int JitCodeCache::_stub_unwind_count = 0;
int JitCodeCache::_stub_unwind_capacity = 0;

// Stubs with dedicated unwinding paths elsewhere; analyzing them would only
// add a redundant (and for call_stub, unsound) phase table.
static bool shouldAnalyzeStub(const char* name) {
    return strcmp(name, "call_stub") != 0 && strcmp(name, "Interpreter") != 0;
}

// A sp-relative restore of x30 switches the return address to the restored
// lr register: the old stack slot lies below the restored sp, and AArch64
// provides no red zone, so signal delivery and the handler may have
// overwritten it before unwindStub() reads it. The lr captured in the
// sampled ucontext is authoritative.
#endif

// CompiledMethodLoad is also needed to enable DebugNonSafepoints info by
// default
void JNICALL JitCodeCache::CompiledMethodLoad(jvmtiEnv *jvmti, jmethodID method,
                                jint code_size, const void *code_addr,
                                jint map_length,
                                const jvmtiAddrLocationMap *map,
                                const void *compile_info) {
  ProfiledThread::initCurrentThreadSignalSafe();
  CodeHeap::updateBounds(code_addr, (const char *)code_addr + code_size);
}

void JNICALL JitCodeCache::DynamicCodeGenerated(jvmtiEnv *jvmti, const char *name,
                                  const void *address, jint length) {
  ProfiledThread::initCurrentThreadSignalSafe();
#ifdef __aarch64__
  // Analyze before taking either lock: the classifier decodes every
  // instruction and allocates, but reads only the stub code. Publication is
  // ordered by the exclusive lock below -- a reader that finds the stub always
  // finds its info.
  StubUnwindInfo* stub_info = nullptr;
  if (shouldAnalyzeStub(name)) {
    // Only the adapters blob is known to pack several entry points behind
    // a mid-stub br (see analyzeStubUnwind()).
    bool multi_entry = name != nullptr && strcmp(name, "I2C/C2I adapters") == 0;
    stub_info = analyzeStubUnwind(address, length, multi_entry);
    Counters::increment(stub_info != nullptr && stub_info->_classified
                            ? WALKVM_STUB_INFO_CLASSIFIED
                            : WALKVM_STUB_INFO_UNCLASSIFIED);
  }
#endif
  // Registrations can arrive concurrently from several threads. The writer
  // mutex orders them, so the state read while preparing below stays valid
  // until the commit. Signal handlers never take it.
  MutexLocker writer(_stubs_write_lock);
  // Every heap allocation and free happens outside the exclusive lock. The
  // bounded readers already prevent a deadlock: while the lock is held
  // exclusively, a stub lookup returns false and the stack walk uses its
  // fallback unwind. Keeping the allocator out of the exclusive section keeps
  // that window short: the registering thread cannot block in the allocator
  // while it holds _stubs_lock.
  CodeCache::PreparedAdd prepared;
  _runtime_stubs.prepareAdd(name, prepared);
#ifdef __aarch64__
  // A re-registration of the same range (never observed for HotSpot runtime
  // stubs, but DynamicCodeGenerated makes no promises) keeps the previously
  // registered info: the old object cannot be freed because a signal handler
  // may still hold a pointer to it.
  int lo = 0, hi = _stub_unwind_count;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (_stub_unwind[mid]._start < address) {
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }
  bool insert = !(lo < _stub_unwind_count && _stub_unwind[lo]._start == address);
  StubUnwindEntry* grown_unwind = nullptr;
  int grown_capacity = 0;
  if (insert && _stub_unwind_count == _stub_unwind_capacity) {
    grown_capacity = _stub_unwind_capacity == 0 ? 64 : _stub_unwind_capacity * 2;
    grown_unwind = (StubUnwindEntry*)malloc(grown_capacity * sizeof(StubUnwindEntry));
    if (grown_unwind != nullptr) {
      // _stub_unwind is null with zero count on the first growth; memcpy
      // requires a valid source even for zero bytes.
      if (_stub_unwind_count > 0) {
        memcpy(grown_unwind, _stub_unwind, _stub_unwind_count * sizeof(StubUnwindEntry));
      }
    } else {
      // Capacity could not be grown: this stub (and every later one) loses
      // precomputed unwinding silently unless the outcome is counted.
      Counters::increment(WALKVM_STUB_INFO_REGISTRATION_FAILED);
      insert = false;
    }
  }
  if (!insert) {
    // Either a duplicate (the registered info stays) or a failed growth. The
    // info was never published, so no reader can hold it.
    free(stub_info);
    stub_info = nullptr;
  }
  StubUnwindEntry* retired_unwind = nullptr;
#endif

  CodeBlob* retired_blobs;
  {
    // The scope ends before the frees below: nothing in it allocates or frees.
    ExclusiveLockGuard publish(&_stubs_lock);
    retired_blobs = _runtime_stubs.commitAdd(address, length, prepared, true);
#ifdef __aarch64__
    if (grown_unwind != nullptr) {
      retired_unwind = _stub_unwind;
      _stub_unwind = grown_unwind;
      _stub_unwind_capacity = grown_capacity;
    }
    if (insert) {
      // Sorted insert: shift the tail right to keep the lookup binary-searchable.
      memmove(&_stub_unwind[lo + 1], &_stub_unwind[lo],
              (_stub_unwind_count - lo) * sizeof(StubUnwindEntry));
      _stub_unwind[lo]._start = address;
      _stub_unwind[lo]._info = stub_info;
      _stub_unwind_count++;
    }
#endif
  }

  // Readers take the shared lock for every access, so after the unlock no
  // reader can still use the replaced arrays.
  delete[] retired_blobs;
#ifdef __aarch64__
  free(retired_unwind);
#endif

  if (name[0] == 'I' && strcmp(name, "Interpreter") == 0) {
    CodeHeap::setInterpreterStart(address);
  } else if (strcmp(name, "call_stub") == 0) {
    _call_stub_begin.store(address, std::memory_order_relaxed);
    // This fence ensures that _call_stub_begin is visible before _call_stub_end, so that isCallStub() works correctly
    std::atomic_thread_fence(std::memory_order_release);
    _call_stub_end.store((const char *)address + length, std::memory_order_relaxed);
  }

  CodeHeap::updateBounds(address, (const char *)address + length);
}

bool JitCodeCache::findRuntimeStub(const void *address, const void **start,
                                   const char **name) {
  // Fails only while a writer holds the lock: the caller is a signal handler,
  // and the writer may be the interrupted thread itself. Competing readers do
  // not make it fail, because each failed CAS means another reader got in.
  OptionalSharedLockGuard guard(&_stubs_lock, SpinLock::NO_SPIN_BUDGET);
  if (!guard.ownsLock()) {
    Counters::increment(STUB_LOOKUP_LOCK_UNAVAILABLE);
    return false;
  }
  if (!_runtime_stubs.contains(address)) {
    return false;
  }
  CodeBlob *blob = _runtime_stubs.findBlobByAddress(address);
  if (blob == nullptr) {
    return false;
  }
  // Copy out under the lock: a registration may replace the blob array as
  // soon as the lock is released.
  *start = blob->_start;
  *name = blob->_name;
  return true;
}

#ifdef __aarch64__
bool JitCodeCache::findRuntimeStubInfo(const void* address, const void** start,
                                       const char** name, const StubUnwindInfo** info) {
  *info = nullptr;
  // Same lock acquisition as findRuntimeStub().
  OptionalSharedLockGuard guard(&_stubs_lock, SpinLock::NO_SPIN_BUDGET);
  if (!guard.ownsLock()) {
    Counters::increment(STUB_LOOKUP_LOCK_UNAVAILABLE);
    return false;
  }
  bool found = false;
  if (_runtime_stubs.contains(address)) {
    CodeBlob* blob = _runtime_stubs.findBlobByAddress(address);
    if (blob != nullptr) {
      *start = blob->_start;
      *name = blob->_name;
      found = true;
      // Registry is sorted by start address: binary search. A miss leaves
      // info null and the caller falls back to the legacy heuristics.
      int lo = 0, hi = _stub_unwind_count;
      while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (_stub_unwind[mid]._start < blob->_start) {
          lo = mid + 1;
        } else {
          hi = mid;
        }
      }
      if (lo < _stub_unwind_count && _stub_unwind[lo]._start == blob->_start) {
        *info = _stub_unwind[lo]._info;
      }
    }
  }
  return found;
}
#endif

long long JitCodeCache::runtimeStubsMemoryUsage() {
  SharedLockGuard guard(&_stubs_lock);
  return _runtime_stubs.memoryUsage();
}
