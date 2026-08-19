/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CODECACHE_H
#define _CODECACHE_H

#include "common.h"
#include "counters.h"
#include "dwarf.h"
#include "utils.h"

#include <atomic>
#include <jvmti.h>
#include <stddef.h>
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
  im_dup2,
  im_dup3,
  im_pthread_create,
  im_pthread_exit,
  im_pthread_setspecific,
  im_poll,
  im_malloc,
  im_calloc,
  im_realloc,
  im_free,
  im_posix_memalign,
  im_aligned_alloc,
  im_sigaction,
  im_send,
  im_recv,
  im_write,
  im_read,
  im_close,
  im_connect,
  im_accept,
  im_accept4,
  im_recvfrom,
  im_recvmsg,
  im_epoll_wait,
  im_epoll_pwait,
  im_ppoll,
  im_select,
  im_pselect,
  NUM_IMPORTS
};

enum Mark {
    MARK_VM_RUNTIME = 1,
    MARK_INTERPRETER = 2,
    MARK_COMPILER_ENTRY = 3,
    MARK_JAVA_PROFILER = 4, // java-profiler internals such as native hooks.
    MARK_THREAD_ENTRY = 5,   // Thread entry points (thread_native_entry, JavaThread::, etc.)
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

  // Size of the heap allocation backing a name string produced by create().
  // This is the single source of truth for that size: create() allocates
  // exactly allocSize(name) bytes, and memoryUsage() accounts for it. 0 if null.
  static size_t allocSize(const char *name) {
    if (name == nullptr) {
      return 0;
    }
    return align_up(sizeof(NativeFunc) + 1 + strlen(name), sizeof(NativeFunc *));
  }

  static short libIndex(const char *name) {
    if (name == nullptr) {
      return -1;
    }
    NativeFunc* func = from(name);
    if (!is_aligned(func, sizeof(func))) {
      return -1;
    }
    return func->_lib_index;
  }

  static bool is_marked(const char *name) {
    return read_mark(name) != 0;
  }

  static char read_mark(const char* name);

  static void set_mark(const char* name, char value) {
    if (name == nullptr) {
      return;
    }
    NativeFunc* func = from(name);
    if (!is_aligned(func, sizeof(func))) {
      return;
    }
    func->_mark = value;
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

class CodeCache {
private:
  static_assert(NUM_IMPORTS <= 64, "import completeness mask must cover every import");

  struct ImportLocation {
    ImportId _id;
    void** _location;
  };

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

  std::vector<ImportLocation> _imports;
  size_t _import_offsets[NUM_IMPORTS + 1];
  u64 _incomplete_imports;
  bool _imports_finalized;
  bool _imports_patchable;
  bool _debug_symbols;

  FrameDesc *_dwarf_table;
  int _dwarf_table_length;
  const FrameDesc *_default_frame;

  int _capacity;
  int _count;
  CodeBlob *_blobs;

  // Set once the cache is registered into a CodeCacheArray (see markPublished()).
  // After that, memoryUsage() may be read lock-free from another thread (dump),
  // so the mutators that touch the fields it reads (add()/expand()/
  // setDwarfTable()) must not run — asserted in debug. Standalone caches that
  // are never registered (e.g. JitCodeCache::_runtime_stubs, which is instead
  // guarded by its own JitCodeCache::_stubs_lock) stay unpublished, so the
  // asserts never fire for them. Atomic with release/acquire so the flag is
  // observably true on any thread that reaches a published cache — the store is
  // sequenced before CodeCacheArray::add()'s RELEASE publish of the pointer, and
  // the assert loads it with acquire — without a formal data race.
  std::atomic<bool> _published;

  void expand();
  void finalizeImports();
  bool makeImportsPatchable();
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

  // Mark this cache as published into a CodeCacheArray. Call before the array
  // makes the pointer visible to readers; afterwards add()/expand()/
  // setDwarfTable() must not be called (see _published).
  void markPublished() { _published.store(true, std::memory_order_release); }

  void add(const void *start, int length, const char *name,
           bool update_bounds = false);
  void updateBounds(const void *start, const void *end);
  void sort();

  /**
   * Mark symbols matching the predicate with the given mark value.
   *
   * This is called during profiler initialization to mark JVM internal functions
   * (MARK_VM_RUNTIME, MARK_INTERPRETER, MARK_COMPILER_ENTRY, MARK_JAVA_PROFILER).
   */
  template <typename NamePredicate>
  inline void mark(NamePredicate predicate, char value) {
      for (int i = 0; i < _count; i++) {
          const char* blob_name = _blobs[i]._name;
          if (blob_name != NULL && predicate(blob_name)) {
              NativeFunc::set_mark(blob_name, value);
          }
      }

      if (value == MARK_VM_RUNTIME && _name != NULL) {
          // In case a library has no debug symbols
          NativeFunc::set_mark(_name, value);
      }
  }

  void addImport(void **entry, const char *name);
  size_t importCount(ImportId id);
  bool importsComplete(ImportId id) const;
  bool prepareImportsForPatch();
  void **findImport(ImportId id, size_t index = 0);
  bool patchImport(ImportId, void *hook_func);

  CodeBlob *findBlob(const char *name);
  CodeBlob *findBlobByAddress(const void *address);
  const void *binarySearch(const void *address, const char **name);
  const void *findSymbol(const char *name);
  const void *findSymbolByPrefix(const char *prefix);
  const void *findSymbolByPrefix(const char *prefix, int prefix_len);
  void findSymbolsByPrefix(std::vector<const char *> &prefixes,
                           std::vector<const void *> &symbols);

  void setDwarfTable(FrameDesc *table, int length, const FrameDesc &default_frame = FrameDesc::default_frame);
  FrameDesc findFrameDesc(const void *pc);

  // Live size of what this CodeCache owns on the heap: the blob array, the
  // per-symbol name strings (variable length), this cache's own name, and the
  // DWARF unwind table. Recomputed on demand (called only at dump time), so it
  // reflects the current contents. The build-id string is deliberately excluded
  // — it is mutated by the background refresher and negligible in size (see the
  // definition). Const and lock-free: reads only fields that are stable once the
  // library is published.
  long long memoryUsage() const;

  int count() { return _count; }
  CodeBlob* blob(int idx) {
    return &_blobs[idx];
  }
};

class CodeCacheArray {
private:
  CodeCache *_libs[MAX_NATIVE_LIBS];
  volatile int _reserved;       // next slot to reserve (CAS by writers)
  volatile int _count;          // published count (all indices < _count have non-NULL pointers)
  bool _overflow_reported;

public:
  CodeCacheArray() : _reserved(0), _count(0), _overflow_reported(false) {
    memset(_libs, 0, MAX_NATIVE_LIBS * sizeof(CodeCache *));
  }

  CodeCache *operator[](int index) const { return __atomic_load_n(&_libs[index], __ATOMIC_ACQUIRE); }

  // All indices < count() are guaranteed to have a non-NULL pointer.
  int count() const { return __atomic_load_n(&_count, __ATOMIC_ACQUIRE); }

  // Pointer-first add: reserve a slot via CAS on _reserved, store the
  // pointer with RELEASE, then advance _count. Readers see count() grow
  // only after the pointer is visible, so indices < count() never yield NULL.
  bool add(CodeCache *lib) {
    int slot = __atomic_load_n(&_reserved, __ATOMIC_RELAXED);
    do {
      if (slot >= MAX_NATIVE_LIBS) {
        Counters::increment(NATIVE_LIBS_DROPPED);
        if (!_overflow_reported) {
          _overflow_reported = true;
          LOG_WARN("Native library limit reached (%d). Additional libraries will not be tracked.", MAX_NATIVE_LIBS);
        }
        return false;
      }
    } while (!__atomic_compare_exchange_n(&_reserved, &slot, slot + 1,
                                          true, __ATOMIC_RELAXED, __ATOMIC_RELAXED));
    assert(__atomic_load_n(&_libs[slot], __ATOMIC_RELAXED) == nullptr);
    // Mark published before the RELEASE store makes the pointer visible, so any
    // later add()/expand()/setDwarfTable() on this cache trips the assert (its
    // _blobs would then be read lock-free by memoryUsage() at dump time).
    lib->markPublished();
    // Store pointer before publishing count. The RELEASE here pairs with
    // the ACQUIRE load in operator[]/at() and count().
    __atomic_store_n(&_libs[slot], lib, __ATOMIC_RELEASE);
    // Advance _count to publish the new slot. Spin until our slot is next
    // in line, preserving contiguous ordering when multiple adds race.
    while (__atomic_load_n(&_count, __ATOMIC_RELAXED) != slot) {
      // wait for preceding slots to publish
    }
    __atomic_store_n(&_count, slot + 1, __ATOMIC_RELEASE);
    return true;
  }

  CodeCache* at(int index) const {
    if (index >= MAX_NATIVE_LIBS) {
      return nullptr;
    }
    return __atomic_load_n(&_libs[index], __ATOMIC_ACQUIRE);
  }

  // Sum the live memory of all registered libraries. Recomputed on demand
  // (called only at dump time) so it reflects each library's fully-populated
  // state at that point — the accurate per-library formula rather than a value
  // cached at add() time. (Libraries are populated before being registered and
  // not grown afterwards.) The array is append-only, so iterating the published
  // prefix is safe alongside concurrent add()s.
  size_t memoryUsage() const {
    size_t total = 0;
    int n = count();
    for (int i = 0; i < n; i++) {
      CodeCache *lib = at(i);
      if (lib != nullptr) {
        total += (size_t)lib->memoryUsage();
      }
    }
    return total;
  }
};

#endif // _CODECACHE_H
