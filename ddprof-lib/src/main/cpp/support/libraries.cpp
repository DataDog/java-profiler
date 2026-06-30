#include "codeCache.h"
#include "common.h"
#include "findLibraryImpl.h"
#include "hotspot/vmStructs.h"
#include "libraries.h"
#include "log.h"
#include "os.h"
#include "symbols.h"
#include "symbols_linux.h"
#include "vmEntry.h"
#include <atomic>

static std::atomic<void (*)(bool)> s_native_thread_names_cb{nullptr};
static std::atomic<void (*)()> s_malloc_tracer_refresh_cb{nullptr};
// Called at the end of refresh() so the profiler lib can run LibraryPatcher
// hooks (patch_sigaction, install_socket_hooks) without the support lib
// depending on LibraryPatcher directly.
static std::atomic<void (*)()> s_library_patch_cb{nullptr};

void Libraries::setNativeThreadNamesCallback(void (*cb)(bool)) {
    s_native_thread_names_cb.store(cb, std::memory_order_release);
}

void Libraries::setMallocTracerRefreshCallback(void (*cb)()) {
    s_malloc_tracer_refresh_cb.store(cb, std::memory_order_release);
}

void Libraries::setLibraryPatchCallback(void (*cb)()) {
    s_library_patch_cb.store(cb, std::memory_order_release);
}

// Cadence for the background refresher thread.  Bounds the window during
// which a library lazily loaded from signal context (and therefore unable
// to call refresh() synchronously) is unresolvable by the stack walker.
// 500 ms is short enough that frame resolution gaps are barely observable
// in typical sampling, and the refresher only wakes once per tick (cheap).
static constexpr u64 REFRESH_INTERVAL_NS = 500ULL * 1'000'000ULL;

// Cadence for native (non-Java) thread-name resolution piggy-backed on the
// refresher thread (PROF-15139).  Each pass enumerates /proc/self/task and
// reads comm for unknown tids, so it is decimated relative to the 500 ms
// library-refresh tick to bound that cost on high-thread-count processes.
// 2 s is well under the lifetime of long-lived JIT/GC threads we want to name.
static constexpr u64 NATIVE_THREAD_NAME_INTERVAL_NS = 2ULL * 1000ULL * 1'000'000ULL;

void Libraries::mangle(const char *name, char *buf, size_t size) {
  char *buf_end = buf + size;
  strcpy(buf, "_ZN");
  buf += 3;

  const char *c;
  while ((c = strstr(name, "::")) != NULL && buf + (c - name) + 4 < buf_end) {
    int n = snprintf(buf, buf_end - buf, "%d", (int)(c - name));
    if (n < 0 || n >= buf_end - buf) {
      if (n < 0) {
        Log::debug("Error in snprintf.");
      }
      goto end;
    }
    buf += n;
    memcpy(buf, name, c - name);
    buf += c - name;
    name = c + 2;
  }
  if (buf < buf_end) {
    snprintf(buf, buf_end - buf, "%d%sE*", (int)strlen(name), name);
  }

end:
  buf_end[-1] = '\0';
}

void Libraries::updateSymbols(bool kernel_symbols) {
  Symbols::parseLibraries(&_native_libs, kernel_symbols);
}

void Libraries::refresh() {
  // Clear the flag before scanning so any concurrent markDirty() between
  // now and the end of this call re-arms us for the next tick.  All
  // downstream operations are idempotent (parseLibraries tracks
  // _parsed_inodes, patch_sigaction checks _sigaction_entries,
  // installHooks uses monotonic _patched_libs, updateBuildIds tracks
  // _build_id_processed), so redundant invocations are cheap.
  _dirty.store(false, std::memory_order_release);
  updateSymbols(false);
  auto patch_cb = s_library_patch_cb.load(std::memory_order_acquire);
  if (patch_cb != nullptr) {
    patch_cb();
  }
  auto malloc_cb = s_malloc_tracer_refresh_cb.load(std::memory_order_acquire);
  if (malloc_cb != nullptr) {
    malloc_cb();
  }
  if (_remote_symbolication) {
    updateBuildIds();
  }
}

void *Libraries::refresherLoop(void *arg) {
  Libraries *self = static_cast<Libraries *>(arg);

  // Block profiling signals BEFORE publishing our TID.  Otherwise a
  // SIGPROF / SIGVTALRM armed for this thread (e.g. a stale per-thread
  // timer from a previous lifecycle, or an in-flight signal queued during
  // pthread_create) could fire on us between TID-publish and sigmask, and
  // run the full stack-walk path here — pure overhead, and in debug
  // builds with DDPROF_FORCE_STACKWALK_CRASH it inflates the SIGSEGV
  // recovery count enough to starve the test work thread and break
  // vmStackwalkerCrashRecoveryTest.  SIGIO (WAKEUP_SIGNAL) is left
  // unmasked because stopRefresher() relies on it to interrupt sleep.
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGPROF);
  sigaddset(&mask, SIGVTALRM);
  pthread_sigmask(SIG_BLOCK, &mask, nullptr);

  // Publish our TID so sampler thread-list enumerations can skip us.
  self->_refresher_tid.store(OS::threadId(), std::memory_order_release);

  // Timestamp of the last native-thread-name pass; 0 makes the first eligible
  // tick run it.  Tracked with a monotonic clock so it is robust to early
  // wakeups from stopRefresher()'s SIGIO.
  u64 last_native_name_ns = 0;

  while (self->_refresher_running.load(std::memory_order_acquire)) {
    // Absolute-deadline sleep that resumes across EINTR (SIGCHLD, debugger
    // SIGSTOP/SIGCONT, etc.) and wakes early when stopRefresher() flips
    // _refresher_running false and sends SIGIO.  See OS::sleepWhile.
    OS::sleepWhile(REFRESH_INTERVAL_NS, self->_refresher_running);
    if (!self->_refresher_running.load(std::memory_order_acquire)) {
      break;
    }
    if (self->_dirty.load(std::memory_order_acquire)) {
      self->refresh();
    }
    // Name native (non-Java) threads while they are still alive. JIT/GC and
    // other non-Java threads get no JVMTI ThreadStart, so they are otherwise
    // named only at dump time; transient ones that exit before the dump fall
    // back to "[tid=N]" (PROF-15139).  Gated on isRunning() so we do no work
    // before the profiler reaches RUNNING (startRefresher precedes that), and
    // decimated to NATIVE_THREAD_NAME_INTERVAL_NS to bound the /proc scan cost.
    u64 now = OS::nanotime();
    auto names_cb = s_native_thread_names_cb.load(std::memory_order_acquire);
    if (names_cb != nullptr &&
        now - last_native_name_ns >= NATIVE_THREAD_NAME_INTERVAL_NS) {
      last_native_name_ns = now;
      // Defer threads still showing the inherited process name; the dump-time
      // pass (which does not defer) records any that never set a real name.
      names_cb(true);
    }
  }
  return nullptr;
}

void Libraries::startRefresher() {
  if (_refresher_running.exchange(true, std::memory_order_acq_rel)) {
    return;  // already running
  }
  if (pthread_create(&_refresher_thread, nullptr, refresherLoop, this) != 0) {
    _refresher_running.store(false, std::memory_order_release);
    Log::warn("Unable to start Libraries refresher thread");
  }
}

void Libraries::stopRefresher() {
  if (!_refresher_running.exchange(false, std::memory_order_acq_rel)) {
    return;  // not running
  }
  // Clear callbacks before joining the thread to avoid races where the
  // thread fires them after the profiler has started tearing down.
  s_native_thread_names_cb.store(nullptr, std::memory_order_release);
  s_malloc_tracer_refresh_cb.store(nullptr, std::memory_order_release);
  s_library_patch_cb.store(nullptr, std::memory_order_release);
  pthread_kill(_refresher_thread, WAKEUP_SIGNAL);
  pthread_join(_refresher_thread, nullptr);
  // Clear the published TID so a later sampler doesn't skip an unrelated
  // thread that may have inherited the same TID after we exited.
  _refresher_tid.store(-1, std::memory_order_release);
}

// Platform-specific implementation of updateBuildIds() is in libraries_linux.cpp (Linux)
// or stub implementation for other platforms

const void *Libraries::resolveSymbol(const char *name) {
  char mangled_name[256];
  if (strstr(name, "::") != NULL) {
    mangle(name, mangled_name, sizeof(mangled_name));
    name = mangled_name;
  }

  size_t len = strlen(name);
  int native_lib_count = _native_libs.count();
  if (len > 0 && name[len - 1] == '*') {
    for (int i = 0; i < native_lib_count; i++) {
      CodeCache *lib = _native_libs[i];
      if (lib != NULL) {
        const void *address = lib->findSymbolByPrefix(name, len - 1);
        if (address != NULL) {
          return address;
        }
      }
    }
  } else {
    for (int i = 0; i < native_lib_count; i++) {
      CodeCache *lib = _native_libs[i];
      if (lib != NULL) {
        const void *address = lib->findSymbol(name);
        if (address != NULL) {
          return address;
        }
      }
    }
  }

  return NULL;
}

CodeCache *Libraries::findJvmLibrary(const char *j9_lib_name) {
  return VM::isOpenJ9() ? findLibraryByName(j9_lib_name) : VMStructs::libjvm();
}

CodeCache *Libraries::findLibraryByName(const char *lib_name) {
  const size_t lib_name_len = strlen(lib_name);
  const int native_lib_count = _native_libs.count();
  for (int i = 0; i < native_lib_count; i++) {
    CodeCache *lib = _native_libs[i];
    if (lib != NULL) {
      const char *s = lib->name();
      if (s != NULL) {
        const char *p = strrchr(s, '/');
        if (p != NULL && strncmp(p + 1, lib_name, lib_name_len) == 0) {
          return lib;
        }
      }
    }
  }
  return NULL;
}

CodeCache *Libraries::findLibraryByAddress(const void *address) const {
  return findLibraryByAddressImpl<CodeCache>(_native_libs, address);
}
