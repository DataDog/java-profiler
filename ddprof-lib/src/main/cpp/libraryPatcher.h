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

const int MAX_NATIVE_IO_HOOKS = 16;

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

  // Separate tracking for native I/O patches. Each library can contribute one
  // GOT slot per supported I/O hook.
  static PatchEntry  _socket_entries[MAX_NATIVE_IO_HOOKS * MAX_NATIVE_LIBS];
  static int         _socket_size;

  static void patch_library_unlocked(CodeCache* lib);
  static void patch_pthread_create();
  static void patch_pthread_setspecific();
  static void patch_sigaction_in_library(CodeCache* lib);
  static void unpatch_socket_functions_unlocked();
public:
  // True while native I/O hooks are installed; read by dlopen refresh paths
  // before attempting to patch newly loaded libraries.
  static std::atomic<bool> _socket_active;
  static void initialize();
  static void patch_libraries();
  static void unpatch_libraries();
  static void patch_sigaction();
  static bool patch_socket_functions();
  static void unpatch_socket_functions();
  static bool unpatch_socket_functions_if_inactive();
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
  static bool patch_socket_functions() { return false; }
  static void unpatch_socket_functions() { }
  static bool unpatch_socket_functions_if_inactive() {
    return false;
  }
  static void install_socket_hooks() { }
};

#endif

#endif // _LIBRARYPATCHER_H
