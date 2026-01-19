/*
 * Copyright The async-profiler authors
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CODECACHE_H
#define _CODECACHE_H

#include "utils.h"

#include <jvmti.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#define NO_MIN_ADDRESS ((const void *)-1)
#define NO_MAX_ADDRESS ((const void *)0)

typedef bool (*NamePredicate)(const char *name);

const int INITIAL_CODE_CACHE_CAPACITY = 1000;
const int MAX_NATIVE_LIBS = 2048;

enum ImportId {
  im_dlopen,
  im_pthread_create,
  im_pthread_exit,
  im_pthread_setspecific,
  im_poll,
  im_malloc,
  im_calloc,
  im_realloc,
  im_free,
  NUM_IMPORTS
};

enum ImportType {
    PRIMARY,
    SECONDARY,
    NUM_IMPORT_TYPES
};

enum Mark {
    MARK_VM_RUNTIME = 1,
    MARK_INTERPRETER = 2,
    MARK_COMPILER_ENTRY = 3,
    MARK_ASYNC_PROFILER = 4, // async-profiler internals such as native hooks.
};

class NativeFunc {
private:
  short _lib_index;
  char _mark;
  char _reserved;
  char _name[0];

  static NativeFunc *from(const char *name) {
    return (NativeFunc *)(name - sizeof(NativeFunc));
  }

public:
  static char *create(const char *name, short lib_index);
  static void destroy(char *name);

  static short libIndex(const char *name) {
    NativeFunc* func = from(name);
    if (!is_aligned(func, sizeof(func))) {
      return -1;
    }
    return func->_lib_index;
  }

  static bool isMarked(const char *name) { return from(name)->_mark != 0; }

  static char mark(const char* name) {
      return from(name)->_mark;
  }

  static void mark(const char* name, char value) {
      from(name)->_mark = value;
  }
};

class CodeBlob {
public:
  const void *_start;
  const void *_end;
  char *_name;

  static int comparator(const void *c1, const void *c2) {
    CodeBlob *cb1 = (CodeBlob *)c1;
    CodeBlob *cb2 = (CodeBlob *)c2;
    if (cb1->_start < cb2->_start) {
      return -1;
    } else if (cb1->_start > cb2->_start) {
      return 1;
    } else if (cb1->_end == cb2->_end) {
      return 0;
    } else {
      return cb1->_end > cb2->_end ? -1 : 1;
    }
  }
};

class FrameDesc;

class CodeCache {
private:
  char *_name;
  short _lib_index;
  const void *_min_address;
  const void *_max_address;
  const char *_text_base;
  const char* _image_base;

  unsigned int _plt_offset;
  unsigned int _plt_size;

  // Build-ID and load bias for remote symbolication
  char *_build_id;           // GNU build-id (hex string, null if not available)
  size_t _build_id_len;      // Build-id length in bytes (raw, not hex string length)
  uintptr_t _load_bias;      // Load bias (image_base - file_base address)

  void **_imports[NUM_IMPORTS][NUM_IMPORT_TYPES];
  bool _imports_patchable;
  bool _debug_symbols;

  FrameDesc *_dwarf_table;
  int _dwarf_table_length;

  int _capacity;
  int _count;
  CodeBlob *_blobs;

  void expand();
  void makeImportsPatchable();
  void saveImport(ImportId id, void** entry);
  void copyFrom(const CodeCache& other);

public:
  explicit CodeCache(const char *name, short lib_index = -1,
                     const void *min_address = NO_MIN_ADDRESS,
                     const void *max_address = NO_MAX_ADDRESS,
                     const char* image_base = NULL,
                     bool imports_patchable = false);
  // Copy constructor
  CodeCache(const CodeCache &other);
  // Copy assignment operator
  CodeCache &operator=(const CodeCache &other);

  ~CodeCache();

  void dump();

  const char *name() const { return _name; }

  const void *minAddress() const { return _min_address; }

  const void *maxAddress() const { return _max_address; }

  const char* imageBase() const { return _image_base; }

  bool contains(const void *address) const {
    return address >= _min_address && address < _max_address;
  }

  void setTextBase(const char *text_base) { _text_base = text_base; }

  void setPlt(unsigned int plt_offset, unsigned int plt_size) {
    _plt_offset = plt_offset;
    _plt_size = plt_size;
  }

  bool hasDebugSymbols() const { return _debug_symbols; }

  void setDebugSymbols(bool debug_symbols) { _debug_symbols = debug_symbols; }

  // Build-ID and remote symbolication support
  const char* buildId() const { return _build_id; }
  size_t buildIdLen() const { return _build_id_len; }
  bool hasBuildId() const { return _build_id != nullptr; }
  uintptr_t loadBias() const { return _load_bias; }
  short libIndex() const { return _lib_index; }

  // Sets the build-id (hex string) and stores the original byte length
  // build_id: null-terminated hex string (e.g., "abc123..." for 40-char string)
  // build_id_len: original byte length before hex conversion (e.g., 20 bytes)
  void setBuildId(const char* build_id, size_t build_id_len);
  void setLoadBias(uintptr_t load_bias) { _load_bias = load_bias; }

  void add(const void *start, int length, const char *name,
           bool update_bounds = false);
  void updateBounds(const void *start, const void *end);
  void sort();

  /**
   * Mark symbols matching the predicate with the given mark value.
   *
   * This is called during profiler initialization to mark JVM internal functions
   * (MARK_VM_RUNTIME, MARK_INTERPRETER, MARK_COMPILER_ENTRY, MARK_ASYNC_PROFILER).
   */
  template <typename NamePredicate>
  inline void mark(NamePredicate predicate, char value) {
      for (int i = 0; i < _count; i++) {
          const char* blob_name = _blobs[i]._name;
          if (blob_name != NULL && predicate(blob_name)) {
              NativeFunc::mark(blob_name, value);
          }
      }

      if (value == MARK_VM_RUNTIME && _name != NULL) {
          // In case a library has no debug symbols
          NativeFunc::mark(_name, value);
      }
  }

  void addImport(void **entry, const char *name);
  void **findImport(ImportId id);
  void patchImport(ImportId, void *hook_func);

  CodeBlob *findBlob(const char *name);
  CodeBlob *findBlobByAddress(const void *address);
  const void *binarySearch(const void *address, const char **name);
  const void *findSymbol(const char *name);
  const void *findSymbolByPrefix(const char *prefix);
  const void *findSymbolByPrefix(const char *prefix, int prefix_len);
  void findSymbolsByPrefix(std::vector<const char *> &prefixes,
                           std::vector<const void *> &symbols);

  void setDwarfTable(FrameDesc *table, int length);
  FrameDesc findFrameDesc(const void *pc);

  long long memoryUsage() {
    return _capacity * sizeof(CodeBlob *) + _count * sizeof(NativeFunc);
  }

  int count() { return _count; }
  CodeBlob* blob(int idx) {
    return &_blobs[idx];
  }
};

class CodeCacheArray {
private:
  CodeCache *_libs[MAX_NATIVE_LIBS];
  volatile int _count;
  volatile size_t _used_memory;

public:
  CodeCacheArray() : _count(0), _used_memory(0) {
    memset(_libs, 0, MAX_NATIVE_LIBS * sizeof(CodeCache *));
  }

  CodeCache *operator[](int index) const { return __atomic_load_n(&_libs[index], __ATOMIC_ACQUIRE); }

  int count() const { return __atomic_load_n(&_count, __ATOMIC_RELAXED); }

  void add(CodeCache *lib) {
    int index = __atomic_fetch_add(&_count, 1, __ATOMIC_RELAXED);
    if (index < MAX_NATIVE_LIBS) {
      __atomic_fetch_add(&_used_memory, lib->memoryUsage(), __ATOMIC_RELAXED);
       __atomic_store_n(&_libs[index], lib, __ATOMIC_RELEASE);
    }
  }

  CodeCache* at(int index) const {
    if (index >= MAX_NATIVE_LIBS) {
        return nullptr;
    }
    CodeCache* lib = nullptr;
    while ((lib = __atomic_load_n(&_libs[index], __ATOMIC_ACQUIRE)) == nullptr);

    return lib;
  }

  size_t memoryUsage() const {
    return __atomic_load_n(&_used_memory, __ATOMIC_RELAXED);
  }
};

#endif // _CODECACHE_H
