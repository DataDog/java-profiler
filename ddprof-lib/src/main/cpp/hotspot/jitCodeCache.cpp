/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "jitCodeCache.h"

#include "hotspot/vmStructs.h"

SpinLock JitCodeCache::_stubs_lock;
CodeCache JitCodeCache::_runtime_stubs("[stubs]");
std::atomic<const void *> JitCodeCache::_call_stub_begin = { nullptr };
std::atomic<const void *> JitCodeCache::_call_stub_end = { nullptr };

// CompiledMethodLoad is also needed to enable DebugNonSafepoints info by
// default
void JNICALL JitCodeCache::CompiledMethodLoad(jvmtiEnv *jvmti, jmethodID method,
                                jint code_size, const void *code_addr,
                                jint map_length,
                                const jvmtiAddrLocationMap *map,
                                const void *compile_info) {
  CodeHeap::updateBounds(code_addr, (const char *)code_addr + code_size);
}

void JNICALL JitCodeCache::DynamicCodeGenerated(jvmtiEnv *jvmti, const char *name,
                                  const void *address, jint length) {
  _stubs_lock.lock();
  _runtime_stubs.add(address, length, name, true);
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
