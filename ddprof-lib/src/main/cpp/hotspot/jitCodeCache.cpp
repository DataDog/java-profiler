/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "jitCodeCache.h"

#include <stdlib.h>
#include <string.h>

#include "hotspot/vmStructs.h"
#include "threadLocalData.h"
#ifdef __aarch64__
#include "hotspot/stubUnwindInfo.h"
#endif

SpinLock JitCodeCache::_stubs_lock;
CodeCache JitCodeCache::_runtime_stubs("[stubs]");
std::atomic<const void *> JitCodeCache::_call_stub_begin = { nullptr };
std::atomic<const void *> JitCodeCache::_call_stub_end = { nullptr };

#ifdef __aarch64__
// Registry of precomputed unwind info, sorted by start address so the
// signal-handler lookup is a binary search. Inserts happen under the
// exclusive _stubs_lock and each entry's info pointer is fixed at
// registration time, so a reader holding the shared lock sees a stable
// snapshot: the same lock serializes the growing realloc with the scan, and
// the full-barrier CAS in SpinLock publishes the new contents. Info objects
// are malloc'ed once at DynamicCodeGenerated time and never freed -- a signal
// handler may still be reading one -- matching the lifetime of the stub name
// strings.
StubUnwindEntry* JitCodeCache::_stub_unwind = nullptr;
int JitCodeCache::_stub_unwind_count = 0;
int JitCodeCache::_stub_unwind_capacity = 0;

// Stubs with dedicated unwinding paths elsewhere; analyzing them would only
// add a redundant (and for call_stub, unsound) phase table.
static bool shouldAnalyzeStub(const char* name) {
    return strcmp(name, "call_stub") != 0 && strcmp(name, "Interpreter") != 0;
}

// With epilogue modeling off, a sp-relative restore of x30 keeps the return
// address attributed to its stack slot (which stays exact through the
// canonical epilogues) instead of switching to the restored lr register. The
// model_epilogue=true scan paths are exercised by stubUnwindInfo_ut, so the
// toggle is ready to flip.
static const bool MODEL_STUB_EPILOGUE = false;
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
  // Analyze before taking the lock: the classifier decodes every instruction
  // and allocates, which must not happen while sampling threads spin on the
  // shared lock. Publication is ordered by the exclusive lock below -- a
  // reader that finds the stub always finds its info.
  StubUnwindInfo* stub_info = nullptr;
  if (shouldAnalyzeStub(name)) {
    stub_info = analyzeStubUnwind(address, length, MODEL_STUB_EPILOGUE);
    Counters::increment(stub_info != nullptr && stub_info->_classified
                            ? WALKVM_STUB_INFO_CLASSIFIED
                            : WALKVM_STUB_INFO_UNCLASSIFIED);
  }
#endif
  _stubs_lock.lock();
  _runtime_stubs.add(address, length, name, true);
#ifdef __aarch64__
  // A re-registration of the same range (never observed for HotSpot runtime
  // stubs, but DynamicCodeGenerated makes no promises) keeps the previously
  // registered info: the old object cannot be freed because a signal handler
  // may still hold a pointer to it.
  bool duplicate = false;
  int lo = 0, hi = _stub_unwind_count;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (_stub_unwind[mid]._start < address) {
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }
  if (lo < _stub_unwind_count && _stub_unwind[lo]._start == address) {
    duplicate = true;
  }
  if (!duplicate && _stub_unwind_count == _stub_unwind_capacity) {
    int new_capacity = _stub_unwind_capacity == 0 ? 64 : _stub_unwind_capacity * 2;
    StubUnwindEntry* grown =
        (StubUnwindEntry*)realloc(_stub_unwind, new_capacity * sizeof(StubUnwindEntry));
    if (grown != nullptr) {
      _stub_unwind = grown;
      _stub_unwind_capacity = new_capacity;
    }
  }
  if (!duplicate && _stub_unwind_count < _stub_unwind_capacity) {
    // Sorted insert: shift the tail right to keep the lookup binary-searchable.
    memmove(&_stub_unwind[lo + 1], &_stub_unwind[lo],
            (_stub_unwind_count - lo) * sizeof(StubUnwindEntry));
    _stub_unwind[lo]._start = address;
    _stub_unwind[lo]._info = stub_info;
    _stub_unwind_count++;
  } else {
    if (duplicate) {
      // The freshly analyzed info is redundant; the registered one stays.
      free(stub_info);
    } else {
      // Capacity could not be grown: this stub (and every later one) loses
      // precomputed unwinding silently unless the outcome is counted.
      Counters::increment(WALKVM_STUB_INFO_REGISTRATION_FAILED);
    }
    stub_info = nullptr;
  }
#endif
  _stubs_lock.unlock();

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

CodeBlob* JitCodeCache::findRuntimeStub(const void *address) {
  CodeBlob *stub = nullptr;
  _stubs_lock.lockShared();
  if (_runtime_stubs.contains(address)) {
    stub = _runtime_stubs.findBlobByAddress(address);
  }
  _stubs_lock.unlockShared();
  return stub;
}

#ifdef __aarch64__
bool JitCodeCache::findRuntimeStubInfo(const void* address, const void** start,
                                       const char** name, const StubUnwindInfo** info) {
  bool found = false;
  *info = nullptr;
  _stubs_lock.lockShared();
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
  _stubs_lock.unlockShared();
  return found;
}
#endif

long long JitCodeCache::runtimeStubsMemoryUsage() {
  _stubs_lock.lockShared();
  long long usage = _runtime_stubs.memoryUsage();
  _stubs_lock.unlockShared();
  return usage;
}
