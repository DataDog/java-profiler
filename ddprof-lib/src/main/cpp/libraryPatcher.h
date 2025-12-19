#ifndef _LIBRARYPATCHER_H
#define _LIBRARYPATCHER_H

#include "codeCache.h"
#include "spinLock.h"

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

  static void patch_library_unlocked(CodeCache* lib);
  static void patch_pthread_create();
  static void patch_pthread_setspecific();
public:
  static void initialize();
  static void patch_libraries();
  static void unpatch_libraries();
};

#else

class LibraryPatcher {
public:
  static void initialize() { }
  static void patch_libraries() { }
  static void unpatch_libraries() { }
};

#endif

#endif // _LIBRARYPATCHER_H