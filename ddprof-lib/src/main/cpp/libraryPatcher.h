#ifndef _LIBRARYPATCHER_H
#define _LIBRARYPATCHER_H

#include "codeCache.h"
#include "spinLock.h"
#include <atomic>

#ifdef __linux__

// Patch libraries' @plt entries
typedef struct _patchEntry {
  CodeCache* _lib;
  // library's @plt location
  void** _location;
  // original function
  void*  _func;
} PatchEntry;


class LibraryPatcher {
private:
  static SpinLock    _lock;
  static const char* _profiler_name;
  static PatchEntry  _patched_entries[MAX_NATIVE_LIBS];
  static int         _size;
  static bool        _patch_pthread_create;

  // Separate tracking for sigaction patches
  static PatchEntry  _sigaction_entries[MAX_NATIVE_LIBS];
  static int         _sigaction_size;

  // Separate tracking for socket (send/recv/write/read) patches.
  static PatchEntry  _socket_entries[MAX_NATIVE_LIBS];
  static int         _socket_size;

  static void patch_library_unlocked(CodeCache* lib);
  static void patch_pthread_create();
  static void patch_pthread_setspecific();
  static void patch_sigaction_in_library(CodeCache* lib);
public:
  // True while socket hooks are installed; read by Profiler::dlopen_hook
  // to decide whether to re-patch after a new library is loaded.
  // Low-probability race: stop() is called only on JVM exit; atomic<bool> is zero-cost insurance.
  static std::atomic<bool> _socket_active;
  static void initialize();
  static void patch_libraries();
  static void unpatch_libraries();
  static void patch_sigaction();
  static void patch_socket_functions();
  static void unpatch_socket_functions();
  // Called from Profiler::dlopen_hook after a new library is loaded.
  // No-op when socket hooks are not active.
  static inline void install_socket_hooks() {
    if (_socket_active.load(std::memory_order_acquire)) {
      patch_socket_functions();
    }
  }
};

#else

class LibraryPatcher {
public:
  static void initialize() { }
  static void patch_libraries() { }
  static void unpatch_libraries() { }
  static void patch_sigaction() { }
  static void patch_socket_functions() { }
  static void unpatch_socket_functions() { }
  static void install_socket_hooks() { }
};

#endif

#endif // _LIBRARYPATCHER_H
