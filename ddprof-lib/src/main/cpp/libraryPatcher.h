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
  // Each library can contribute up to 4 GOT slots (send/recv/write/read).
  static PatchEntry  _socket_entries[4 * MAX_NATIVE_LIBS];
  static int         _socket_size;

  static void patch_library_unlocked(CodeCache* lib);
  static void patch_pthread_create();
  static void patch_pthread_setspecific();
  static void patch_sigaction_in_library(CodeCache* lib);
public:
  // True while socket hooks are installed; read by Profiler::dlopen_hook
  // to decide whether to re-patch after a new library is loaded.
  // Set to true after the first batch of libraries is patched in patch_socket_functions().
  // Libraries loaded after profiler start are picked up on the next dlopen_hook call,
  // which calls install_socket_hooks() to patch them if _socket_active is true.
  // Low-probability race: stop() is called only on JVM exit; atomic<bool> is zero-cost insurance.
  static std::atomic<bool> _socket_active;
  static void initialize();
  static void patch_libraries();
  static void unpatch_libraries();
  static void patch_sigaction();
  static bool patch_socket_functions();
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
  static bool patch_socket_functions() { return false; }
  static void unpatch_socket_functions() { }
  static void install_socket_hooks() { }
};

#endif

#endif // _LIBRARYPATCHER_H
