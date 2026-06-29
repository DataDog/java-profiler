#ifndef _LIBRARIES_H
#define _LIBRARIES_H

#include <atomic>
#include <pthread.h>

#include "codeCache.h"

class Libraries {
 private:
  CodeCacheArray _native_libs;
  CodeCache _runtime_stubs;
  bool _remote_symbolication;  // set via setRemoteSymbolication()

  // Pending-refresh flag set by dlopen_hook when it cannot call refresh()
  // synchronously (signal context).  Polled by the refresher thread.
  std::atomic<bool> _dirty;

  // Background refresher thread: periodically (every REFRESH_INTERVAL_NS)
  // checks _dirty and runs refresh() outside signal context, narrowing the
  // window during which newly-loaded libraries are unresolvable.
  pthread_t _refresher_thread;
  std::atomic<bool> _refresher_running;
  std::atomic<int> _refresher_tid;  // captured from OS::threadId() on entry
  static void *refresherLoop(void *arg);

  static void mangle(const char *name, char *buf, size_t size);
 public:
  Libraries() : _native_libs(), _runtime_stubs("runtime stubs"),
                _remote_symbolication(false), _dirty(false),
                _refresher_thread(), _refresher_running(false),
                _refresher_tid(-1) {}

  void setRemoteSymbolication(bool enabled) { _remote_symbolication = enabled; }

  // Refresh symbol tables and reinstall hooks/patches for any libraries
  // loaded since the last refresh.  Idempotent and cheap when no new
  // libraries have been loaded (parseLibraries tracks _parsed_inodes).
  // Clears the dirty flag.  Must be called from non-signal context:
  // updateSymbols acquires a Mutex and reads /proc/self/maps.
  void refresh();

  // Async-signal-safe: just sets a flag.  The refresher thread will pick
  // up the change on its next tick.
  void markDirty() { _dirty.store(true, std::memory_order_release); }

  // Start/stop the background refresher thread.  Called from
  // Profiler::start/stop.
  void startRefresher();
  void stopRefresher();

  // Register a callback invoked by the refresher thread to update native thread
  // names.  The callback is set by the profiler at start and cleared at stop.
  static void setNativeThreadNamesCallback(void (*cb)(bool));

  // Register a callback invoked by refresh() to install malloc hooks when the
  // malloc tracer is running.  Set by the profiler at start, cleared at stop.
  static void setMallocTracerRefreshCallback(void (*cb)());

  // TID of the refresher thread once it has captured its own ID, or -1 if
  // the thread is not currently running.  Used by sampler thread-list
  // enumeration to skip this profiler-internal thread.
  int refresherTid() const { return _refresher_tid.load(std::memory_order_acquire); }

  void updateSymbols(bool kernel_symbols);
  void updateBuildIds();  // Extract build-ids for all loaded libraries
  const void *resolveSymbol(const char *name);
  // In J9 the 'libjvm' functionality is spread across multiple libraries
  // This function will return the 'libjvm' on non-J9 VMs and the library with the given name on J9 VMs
  CodeCache *findJvmLibrary(const char *j9_lib_name);
  CodeCache *findLibraryByName(const char *lib_name);
  CodeCache *findLibraryByAddress(const void *address) const;

  // Get library by index (used for remote symbolication unpacking)
  // Note: Parameter is uint32_t to match lib_index packing (17 bits = max 131K libraries)
  CodeCache *getLibraryByIndex(uint32_t index) const {
    assert(_native_libs.count() >= 0);
    if (index < static_cast<uint32_t>(_native_libs.count())) {
      return _native_libs[index];
    }
    return nullptr;
  }

  static Libraries *instance() {
    static Libraries instance;
    return &instance;
  }

  const CodeCacheArray& native_libs() const {
    return _native_libs;
  }

  // Delete copy constructor and assignment operator to prevent copies
  Libraries(const Libraries&) = delete;
  Libraries& operator=(const Libraries&) = delete;
};

#endif // _LIBRARIES_H
