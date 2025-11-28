#include "arch_dd.h"
#include "lockFree.h"
#include "thread.h"
#include "os_dd.h"
#include "profiler.h"
#include "common.h"
#include "vmStructs.h"
#include "vmEntry.h"
#include <time.h>
#include <cstdlib>
#include <cstring>

// TLS priming signal number
static int g_tls_prime_signal = -1;

// Define ProfiledThread static members for Java thread tracking
LockFreeBitset<ProfiledThread::JAVA_THREAD_BITSET_SIZE> ProfiledThread::_java_thread_bitset;

void ProfiledThread::initJavaThreadBitset() {
  _java_thread_bitset.init();
}

pthread_key_t ProfiledThread::_tls_key;
int ProfiledThread::_buffer_size = 0;
volatile int ProfiledThread::_running_buffer_pos = 0;
ProfiledThread** ProfiledThread::_buffer = nullptr;
volatile int ProfiledThread::_free_stack_top = -1;
int* ProfiledThread::_free_slots = nullptr;

void ProfiledThread::initTLSKey() {
  static pthread_once_t tls_initialized = PTHREAD_ONCE_INIT;
  pthread_once(&tls_initialized, doInitTLSKey);
}

void ProfiledThread::doInitTLSKey() { pthread_key_create(&_tls_key, freeKey); }

inline void ProfiledThread::freeKey(void *key) {
  ProfiledThread *tls_ref = (ProfiledThread *)(key);
  if (tls_ref != NULL) {
    // Check if this is a buffer-allocated thread (has valid buffer_pos)
    bool is_buffer_allocated = (tls_ref->_buffer_pos >= 0);

    if (is_buffer_allocated) {
      // Buffer-allocated: reset and return to buffer for reuse
      tls_ref->releaseFromBuffer();
    } else {
      // Non-buffer (JVMTI-allocated): unregister Java thread and delete the instance
      ProfiledThread::unregisterJavaThread(tls_ref->_tid);
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

  // Register this thread as a Java thread for TLS priming optimization
  ProfiledThread::registerJavaThread(tid);
}

void ProfiledThread::initExistingThreads() {
  if (ddprof::OS::isTlsPrimingAvailable()) {
    doInitExistingThreads();
  }
}

// The lifetime of this vector requires stronger guarantees.
// We need to ensure that the vector is not removed at the end of the process
// while threads are accessing it. This is to silence the sanitizer but should
// not be considered as a fix
__attribute__((no_sanitize("thread"))) void
ProfiledThread::initCurrentThreadWithBuffer() {
  initTLSKey();

  // Early check - if already initialized, return immediately
  if (pthread_getspecific(_tls_key) != NULL) {
    return;
  }

  ProfiledThread *tls_ref = NULL;
  int pos = -1;

  // First try to reuse a freed slot
  pos = popFreeSlot();

  if (pos == -1) {
    // No free slots available, allocate a new one
    // Use atomic fetch-and-add to safely increment position
    pos = __atomic_fetch_add(&_running_buffer_pos, 1, __ATOMIC_RELAXED);
  }

  if (pos < _buffer_size && _buffer != nullptr) {
    tls_ref = _buffer[pos];
    if (tls_ref != nullptr) {
      tls_ref->_tid = OS::threadId();
    }
  }

  if (tls_ref != NULL) {
    // Race condition check: another thread might have set TLS between our first check and here
    // pthread_setspecific is safe to call multiple times, but we want to avoid consuming buffer slots
    if (pthread_getspecific(_tls_key) == NULL) {
      pthread_setspecific(_tls_key, (const void *)tls_ref);
    }
    // If someone else already set it, we "waste" this buffer slot, but that's acceptable
    // since concurrent priming should be rare and buffer is sized generously
  } else {
    TEST_LOG("ProfiledThread TLS buffer too small.");
  }
}

// Fork handler to reset TLS priming state in child process
static void resetTlsPrimingStateInChild() {
  // After fork(), reset signal number to prevent cleanup attempts
  g_tls_prime_signal = -1;

  // Note: The watcher state is reset by os_linux_dd.cpp fork handler
  // This just ensures we don't try to uninstall signals or cleanup resources
}

// Register fork handler on first initialization
static void ensureTlsForkHandlerRegistered() {
  static bool registered = false;
  if (!registered) {
    pthread_atfork(nullptr, nullptr, resetTlsPrimingStateInChild);
    registered = true;
  }
}

void ProfiledThread::doInitExistingThreads() {
  static bool initialized = false;
  if (initialized) {
    return; // Avoid double initialization
  }

  // Initialize Java thread bitset
  initJavaThreadBitset();

  // Register fork handler to prevent issues in forked child processes
  ensureTlsForkHandlerRegistered();

  // Install TLS priming signal handler
  g_tls_prime_signal = ddprof::OS::installTlsPrimeSignalHandler(simpleTlsSignalHandler, 4);
  if (g_tls_prime_signal <= 0) {
    TEST_LOG("Failed to install TLS priming signal handler");
    return;
  }

  TEST_LOG("Successfully installed TLS priming handler on RT signal %d", g_tls_prime_signal);

  // Use a modest buffer size since we're only handling new threads via watcher
  // 256 should be more than enough for concurrent new thread creation
  prepareBuffer(256);

  // Check if watcher is enabled via environment variable or system property
  // Default: disabled (watcher adds per-thread overhead that affects throughput benchmarks)
  // Set DD_PROFILER_TLS_WATCHER=1 to enable for native thread priming
  // Supports both environment variable and system property (for JMH forked JVMs)
  const char* watcher_env = std::getenv("DD_PROFILER_TLS_WATCHER");
  bool watcher_enabled = (watcher_env == nullptr || std::strcmp(watcher_env, "1") == 0);

   // If not set via environment variable, check system property (for JMH compatibility)
   if (watcher_enabled) {
     char* watcher_prop = nullptr;
     jvmtiEnv *jvmti = VM::jvmti();
     if (jvmti != nullptr && jvmti->GetSystemProperty("DD_PROFILER_TLS_WATCHER", &watcher_prop) == 0 && watcher_prop != nullptr) {
       watcher_enabled = (std::strcmp(watcher_prop, "1") != 0);
       jvmti->Deallocate((unsigned char*)watcher_prop);
     }
   }

  if (watcher_enabled) {
    // Start thread directory watcher to prime new threads (no mass-priming of existing threads)
    bool watcher_started = ddprof::OS::startThreadDirectoryWatcher(
      [](int tid) {
        // Prime new thread with TLS signal
        ddprof::OS::signalThread(tid, g_tls_prime_signal);
      },
      [](int tid) {
        // No-op for dead threads - cleanup handled elsewhere
      }
    );

    if (!watcher_started) {
      TEST_LOG("Failed to start thread directory watcher for TLS priming");
    } else {
      TEST_LOG("Started thread directory watcher for TLS priming");
    }
  } else {
    TEST_LOG("TLS watcher enabled (set DD_PROFILER_TLS_WATCHER=0 to enable)");
  }

  initialized = true;
}

void ProfiledThread::cleanupTlsPriming() {
  if (!ddprof::OS::isTlsPrimingAvailable()) {
    return;
  }

  // Stop the thread directory watcher
  ddprof::OS::stopThreadDirectoryWatcher();
  TEST_LOG("Stopped thread directory watcher");

  // Uninstall the TLS priming signal handler
  if (g_tls_prime_signal > 0) {
    ddprof::OS::uninstallTlsPrimeSignalHandler(g_tls_prime_signal);
    TEST_LOG("Uninstalled TLS priming signal handler (signal %d)", g_tls_prime_signal);
    g_tls_prime_signal = -1;
  }

  // Note: We don't clean up the buffer here because threads may still be using it
  // The buffer will be cleaned up when the process exits
}

void ProfiledThread::prepareBuffer(int size) {
  TEST_LOG("Initializing ProfiledThread TLS buffer to %d slots", size);

  _running_buffer_pos = 0;

  // Clean up existing buffer if any
  if (_buffer != nullptr) {
    for (int i = 0; i < _buffer_size; i++) {
      if (_buffer[i] != nullptr) {
        delete _buffer[i];
      }
    }
    free(_buffer);
    _buffer = nullptr;
  }

  if (_free_slots != nullptr) {
    free(_free_slots);
    _free_slots = nullptr;
  }

  _buffer_size = size;
  _running_buffer_pos = 0;
  _free_stack_top = -1;

  // Allocate plain array for ProfiledThread pointers
  _buffer = (ProfiledThread**)calloc(size, sizeof(ProfiledThread*));

  // Allocate array for free slot stack
  _free_slots = (int*)malloc(size * sizeof(int));

  // Initialize buffer with ProfiledThread objects
  for (int i = 0; i < size; i++) {
    _buffer[i] = ProfiledThread::inBuffer(i);
  }
}

void ProfiledThread::release() {
  pthread_key_t key = _tls_key;
  if (key == 0) {
    return;
  }
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
    _span_id = 0;
    _crash_depth = 0;
    _cpu_epoch = 0;
    _wall_epoch = 0;
    _call_trace_id = 0;
    _recording_epoch = 0;
    _filter_slot_id = -1;
    _unwind_failures.clear();

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
  // Signal-safe: never allocate, just return existing TLS or null
  pthread_key_t key = _tls_key;
  return key != 0 ? (ProfiledThread *)pthread_getspecific(key) : nullptr;
}

bool ProfiledThread::isTlsPrimingAvailable() {
  return ddprof::OS::isTlsPrimingAvailable() && g_tls_prime_signal > 0;
}

bool ProfiledThread::wasTlsPrimingAttempted() {
  return ddprof::OS::isTlsPrimingAvailable() && g_tls_prime_signal > 0;
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

void ProfiledThread::simpleTlsSignalHandler(int signo) {
  // Quick check: if TLS already set, return immediately (avoids VMThread lookup)
  if (pthread_getspecific(_tls_key) != nullptr) {
    return;
  }

  // Only prime threads that are not Java threads
  // Java threads are handled by JVMTI ThreadStart events
  if (VMThread::current() == nullptr) {
    initCurrentThreadWithBuffer();
  }
}

void ProfiledThread::registerJavaThread(int tid) {
  _java_thread_bitset.set(static_cast<size_t>(tid));
}

bool ProfiledThread::isLikelyJavaThread(int tid) {
  return _java_thread_bitset.test(static_cast<size_t>(tid));
}

void ProfiledThread::unregisterJavaThread(int tid) {
  _java_thread_bitset.clear(static_cast<size_t>(tid));
}
