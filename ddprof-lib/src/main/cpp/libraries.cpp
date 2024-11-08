#include "codeCache.h"
#include "libraries.h"
#include "log.h"
#include "symbols.h"
#include "vmEntry.h"
#include "vmStructs.h"

Libraries* Libraries::_instance = new Libraries();

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
      const void *address = _native_libs[i]->findSymbolByPrefix(name, len - 1);
      if (address != NULL) {
        return address;
      }
    }
  } else {
    for (int i = 0; i < native_lib_count; i++) {
      const void *address = _native_libs[i]->findSymbol(name);
      if (address != NULL) {
        return address;
      }
    }
  }

  return NULL;
}

CodeCache *Libraries::findJvmLibrary(const char *lib_name) {
  return VM::isOpenJ9() ? findLibraryByName(lib_name) : VMStructs::libjvm();
}

CodeCache *Libraries::findLibraryByName(const char *lib_name) {
  const size_t lib_name_len = strlen(lib_name);
  const int native_lib_count = _native_libs.count();
  for (int i = 0; i < native_lib_count; i++) {
    const char *s = _native_libs[i]->name();
    if (s != NULL) {
      const char *p = strrchr(s, '/');
      if (p != NULL && strncmp(p + 1, lib_name, lib_name_len) == 0) {
        return _native_libs[i];
      }
    }
  }
  return NULL;
}

CodeCache *Libraries::findLibraryByAddress(const void *address) {
  const int native_lib_count = _native_libs.count();
  for (int i = 0; i < native_lib_count; i++) {
    if (_native_libs[i]->contains(address)) {
      return _native_libs[i];
    }
  }
  return NULL;
}