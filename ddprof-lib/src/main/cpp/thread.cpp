/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "thread.h"
#include "context_api.h"
#include "otel_context.h"
#include "os.h"
#include <cstring>
#include <time.h>

pthread_key_t ProfiledThread::_tls_key;
bool ProfiledThread::_tls_key_initialized = false;
int ProfiledThread::_buffer_size = 0;
volatile int ProfiledThread::_running_buffer_pos = 0;
ProfiledThread** ProfiledThread::_buffer = nullptr;
volatile int ProfiledThread::_free_stack_top = -1;
int* ProfiledThread::_free_slots = nullptr;

void ProfiledThread::initTLSKey() {
  static pthread_once_t tls_initialized = PTHREAD_ONCE_INIT;
  pthread_once(&tls_initialized, doInitTLSKey);
}

void ProfiledThread::doInitTLSKey() {
  pthread_key_create(&_tls_key, freeKey);
  // Must be set AFTER pthread_key_create so signal handlers see a valid key.
  // Store-release pairs with the acquire loads in currentSignalSafe() and release()
  // to prevent hardware load-load reordering on weakly-ordered architectures (aarch64):
  // a plain volatile write is not sufficient there.
  __atomic_store_n(&_tls_key_initialized, true, __ATOMIC_RELEASE);
}

inline void ProfiledThread::freeKey(void *key) {
  ProfiledThread *tls_ref = (ProfiledThread *)(key);
  if (tls_ref != NULL) {
    // Check if this is a buffer-allocated thread (has valid buffer_pos)
    bool is_buffer_allocated = (tls_ref->_buffer_pos >= 0);

    if (is_buffer_allocated) {
      // Buffer-allocated: reset and return to buffer for reuse
      tls_ref->releaseFromBuffer();
    } else {
      // Non-buffer (JVMTI-allocated): delete the instance
      delete tls_ref;
    }
  }
}

void ProfiledThread::initCurrentThread() {
  // JVMTI callback path - does NOT use buffer
  // Allocate dedicated ProfiledThread for Java threads (not from buffer)
  // This MUST happen here to prevent lazy allocation in signal handler
  initTLSKey();

  if (pthread_getspecific(_tls_key) != NULL) {
    return; // Already initialized
  }

  int tid = OS::threadId();
  ProfiledThread *tls = ProfiledThread::forTid(tid);
  pthread_setspecific(_tls_key, (const void *)tls);
}

void ProfiledThread::release() {
  if (!__atomic_load_n(&_tls_key_initialized, __ATOMIC_ACQUIRE)) {
    return;
  }
  pthread_key_t key = _tls_key;
  ProfiledThread *tls = (ProfiledThread *)pthread_getspecific(key);
  if (tls != NULL) {
    pthread_setspecific(key, NULL);

    // Check if this is a buffer-allocated thread (has valid buffer_pos)
    bool is_buffer_allocated = (tls->_buffer_pos >= 0);

    tls->releaseFromBuffer();

    // Only delete non-buffer threads (e.g., created via forTid())
    if (!is_buffer_allocated) {
      pthread_setspecific(key, NULL);
      delete tls;
    }
    // Buffer-allocated threads are kept for reuse and will be deleted in cleanupBuffer()
  }
}

void ProfiledThread::releaseFromBuffer() {
  if (_buffer_pos >= 0 && _buffer != nullptr && _buffer_pos < _buffer_size) {
    // Reset the thread object for reuse (clear thread-specific data)
    _tid = 0;
    _pc = 0;
    _sp = 0;
    _span_id = 0;
    _crash_depth = 0;
    _cpu_epoch = 0;
    _wall_epoch = 0;
    _call_trace_id = 0;
    _recording_epoch = 0;
    __atomic_fetch_and(&_misc_flags, ~FLAG_PARKED, __ATOMIC_RELEASE);
    _park_start_ticks = 0;
    memset(&_park_context, 0, sizeof(_park_context));
    _filter_slot_id = -1;
    _init_window = 0;
    _unwind_failures.clear();

    // Null the TLS pointer so external profilers that dereference the pointer
    // (rather than just checking the valid flag) don't access a recycled record.
    // This is distinct from the valid flag: valid guards the OTEP write protocol
    // between the Java writer and native reader, but does not protect recycling.
    __atomic_store_n(&otel_thread_ctx_v1, (OtelThreadContextRecord*)nullptr, __ATOMIC_RELEASE);
    // Mark uninitialized BEFORE zeroing the record, so that our own signal handlers
    // short-circuit before reading partially-zeroed data during the memset below.
    // (The valid flag is zeroed by memset too, but _otel_ctx_initialized guards
    // the isContextInitialized() check which runs before any record access.)
    // Use __ATOMIC_RELEASE so the compiler cannot reorder this store after the
    // memset on ARM with aggressive optimizations.
    __atomic_store_n(&_otel_ctx_initialized, false, __ATOMIC_RELEASE);
    clearOtelSidecar();
    memset(&_otel_ctx_record, 0, sizeof(_otel_ctx_record));

    // Put this ProfiledThread object back in the buffer for reuse
    _buffer[_buffer_pos] = this;

    // Push this slot back to the free list for reuse
    pushFreeSlot(_buffer_pos);

    _buffer_pos = -1;
  }
}

int ProfiledThread::currentTid() {
  ProfiledThread *tls = current();
  if (tls != NULL) {
    return tls->tid();
  }
  return OS::threadId();
}

ProfiledThread *ProfiledThread::current() {
  initTLSKey();

  ProfiledThread *tls = (ProfiledThread *)pthread_getspecific(_tls_key);
  if (tls == NULL) {
    // Lazy allocation - safe since current() is never called from signal handlers
    int tid = OS::threadId();
    tls = ProfiledThread::forTid(tid);
    pthread_setspecific(_tls_key, (const void *)tls);
  }
  return tls;
}

ProfiledThread *ProfiledThread::currentSignalSafe() {
  // Signal-safe: never allocate, just return existing TLS or null.
  // Use _tls_key_initialized instead of key != 0 because pthread_key_create
  // can legitimately return key 0 (common on musl where keys start at 0).
  return __atomic_load_n(&_tls_key_initialized, __ATOMIC_ACQUIRE) ? (ProfiledThread *)pthread_getspecific(_tls_key) : nullptr;
}

int ProfiledThread::popFreeSlot() {
  int current_top;
  int new_top;

  do {
    current_top = __atomic_load_n(&_free_stack_top, __ATOMIC_ACQUIRE);
    if (current_top == -1) {
      return -1; // Stack is empty
    }
    new_top = _free_slots[current_top];
  } while (!__atomic_compare_exchange_n(&_free_stack_top, &current_top, new_top,
                                         true, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE));

  return current_top;
}

void ProfiledThread::pushFreeSlot(int slot_index) {
  if (slot_index < 0 || slot_index >= _buffer_size || _free_slots == nullptr) {
    return; // Invalid slot index
  }

  int current_top;
  do {
    current_top = __atomic_load_n(&_free_stack_top, __ATOMIC_ACQUIRE);
    _free_slots[slot_index] = current_top;
  } while (!__atomic_compare_exchange_n(&_free_stack_top, &current_top, slot_index,
                                         true, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE));
}

void ProfiledThread::cleanupBuffer() {
  if (_buffer != nullptr) {
    for (int i = 0; i < _buffer_size; i++) {
      if (_buffer[i] != nullptr) {
        delete _buffer[i];
        _buffer[i] = nullptr;
      }
    }
    free(_buffer);
    _buffer = nullptr;
  }

  if (_free_slots != nullptr) {
    free(_free_slots);
    _free_slots = nullptr;
  }

  _buffer_size = 0;
  _running_buffer_pos = 0;
  _free_stack_top = -1;
}

Context ProfiledThread::snapshotContext(size_t numAttrs) {
  Context ctx = {};
  u64 span_id = 0, root_span_id = 0;
  if (ContextApi::get(span_id, root_span_id)) {
    ctx.spanId = span_id;
    ctx.rootSpanId = root_span_id;
    size_t count = numAttrs < DD_TAGS_CAPACITY ? numAttrs : DD_TAGS_CAPACITY;
    for (size_t i = 0; i < count; i++) {
      ctx.tags[i].value = _otel_tag_encodings[i];
    }
  }
  return ctx;
}
