#ifndef _LIBRARIES_H
#define _LIBRARIES_H

#include "codeCache.h"

class Libraries {
 private:
  static Libraries * _instance;

  CodeCacheArray _native_libs;
  CodeCache _runtime_stubs;

  static void mangle(const char *name, char *buf, size_t size);
 public:
  Libraries() : _native_libs(), _runtime_stubs("runtime stubs") {}
  void updateSymbols(bool kernel_symbols);
  const void *resolveSymbol(const char *name);
  // In J9 the 'libjvm' functionality is spread across multiple libraries
  // This function will return the 'libjvm' on non-J9 VMs and the library with the given name on J9 VMs
  CodeCache *findJvmLibrary(const char *j9_lib_name);
  CodeCache *findLibraryByName(const char *lib_name);
  CodeCache *findLibraryByAddress(const void *address);

  static Libraries *instance() { return _instance; }
};

#endif // _LIBRARIES_H