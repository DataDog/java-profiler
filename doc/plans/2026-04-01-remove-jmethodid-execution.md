# Remove jmethodID from walkVM Traces — Execution Plan

> **Status:** NOT STARTED
>
> **Companion doc:** [Design Document](2026-04-01-remove-jmethodid-design.md)

**Goal:** Replace `jmethodID` with JFR-derived profiler method IDs in walkVM-based stack traces. Install an inline hook on `ClassLoaderDataGraph::purge()` to resolve method symbols before class unloading frees metadata. Remove all jmethodID usage from the HotSpot stack walking path.

**Tech Stack:** C++ (C++14), HotSpot VMStructs introspection, inline function patching, lock-free data structures.

**Scope:** HotSpot JDK 11+ only. J9/Zing retain existing jmethodID path behind feature gate.

---

## File Map

| File | Change |
|---|---|
| `ddprof-lib/src/main/cpp/hotspot/vmStructs.h` | Add 7 new offset variables, `jfr_method_id()` accessor on VMMethod, `_has_jfr_trace_ids` feature flag, `cp_symbol_at()` helper |
| `ddprof-lib/src/main/cpp/hotspot/vmStructs.cpp` | Register new offsets in `init_offsets_and_addresses()`, resolve `ClassUnloadingContext::_context` and `purge()` symbols, update `verify_offsets()` and `resolveOffsets()` |
| `ddprof-lib/src/main/cpp/methodId.h` | **New file.** `profiler_method_id` typedef, `make_method_id()`, `klass_id_from()`, `method_idnum_from()` |
| `ddprof-lib/src/main/cpp/methodSymbolCache.h` | **New file.** Pre-allocated, lock-free hash map: `profiler_method_id → {class_name, method_name, signature}` |
| `ddprof-lib/src/main/cpp/methodSymbolCache.cpp` | **New file.** Implementation |
| `ddprof-lib/src/main/cpp/classUnloadHook.h` | **New file.** Hook install/uninstall API, trampoline management |
| `ddprof-lib/src/main/cpp/classUnloadHook.cpp` | **New file.** Inline patching of `purge()`, pre-purge callback that walks unloading CLDs and populates MethodSymbolCache |
| `ddprof-lib/src/main/cpp/stackWalker.cpp` | Replace `getMethodId()`/`method->id()` calls with `method->jfr_method_id()` |
| `ddprof-lib/src/main/cpp/flightRecorder.cpp` | Replace `fillJavaMethodInfo()` JVMTI calls with MethodSymbolCache/live-metadata lookup |
| `ddprof-lib/src/main/cpp/flightRecorder.h` | Update MethodMap key type from `jmethodID` to `profiler_method_id` |
| `ddprof-lib/src/main/cpp/profiler.cpp` | Hook lifecycle: install on `start()`, uninstall on `stop()` |
| `ddprof-lib/src/main/cpp/profiler.h` | Remove `_class_unload_hook_trap` (replaced by inline hook), add `ClassUnloadHook*` member |

---

## Task 1: Add methodId.h — Profiler Method ID Type

**Files:**
- Create: `ddprof-lib/src/main/cpp/methodId.h`

- [ ] **Step 1: Create the header with type definition and helpers**

  ```cpp
  #ifndef _METHOD_ID_H
  #define _METHOD_ID_H

  #include <stdint.h>

  typedef uint64_t profiler_method_id;

  static const int METHOD_ID_NUM_BITS = 16;
  static const profiler_method_id METHOD_ID_NUM_MASK = (1ULL << METHOD_ID_NUM_BITS) - 1;

  static inline profiler_method_id make_method_id(uint64_t klass_trace_id, uint16_t method_idnum) {
      // Strip epoch/metadata bits from lower 16 bits of trace_id,
      // then combine with method index
      return (klass_trace_id & ~METHOD_ID_NUM_MASK) | method_idnum;
  }

  static inline uint64_t klass_id_from(profiler_method_id id) {
      return id & ~METHOD_ID_NUM_MASK;
  }

  static inline uint16_t method_idnum_from(profiler_method_id id) {
      return (uint16_t)(id & METHOD_ID_NUM_MASK);
  }

  #endif // _METHOD_ID_H
  ```

  Note: The masking of `klass_trace_id` must be validated against JFR's `TRACE_ID_SHIFT` and epoch bit layout. The exact mask may need adjustment after empirical testing with JFR epoch rotation. The key invariant is: the same masking applied at collection time and resolution time produces identical `klass_id_from()` values.

---

## Task 2: Add New VMStructs Offsets

**Files:**
- Modify: `ddprof-lib/src/main/cpp/hotspot/vmStructs.h`
- Modify: `ddprof-lib/src/main/cpp/hotspot/vmStructs.cpp`

- [ ] **Step 1: Declare new offset variables in vmStructs.h**

  Add to the `DECLARE_TYPE_FIELD_DO` macros, in the appropriate type sections:

  In the `VMKlass` section (near line 195-198, after `_class_loader_data_offset`):
  ```cpp
  field(_klass_next_link_offset, offset, MATCH_SYMBOLS("_next_link"))
  field(_klass_trace_id_offset, offset, MATCH_SYMBOLS("_trace_id"))
  ```

  In the `VMConstMethod` section (near line 188-189, after `_constmethod_idnum_offset`):
  ```cpp
  field(_constmethod_orig_idnum_offset, offset, MATCH_SYMBOLS("_orig_method_idnum"))
  field(_constmethod_name_index_offset, offset, MATCH_SYMBOLS("_name_index"))
  field(_constmethod_signature_index_offset, offset, MATCH_SYMBOLS("_signature_index"))
  ```

  In the `VMClassLoaderData` section (near line 201, after `_class_loader_data_next_offset`):
  ```cpp
  field(_cld_klasses_offset, offset, MATCH_SYMBOLS("_klasses"))
  field(_cld_unloading_next_offset, offset, MATCH_SYMBOLS("_unloading_next"))
  ```

- [ ] **Step 2: Add feature flag**

  In vmStructs.h, near the other feature flags (around line 362):
  ```cpp
  static bool _has_jfr_trace_ids;
  ```

  In vmStructs.cpp `resolveOffsets()`, set it:
  ```cpp
  _has_jfr_trace_ids = (_klass_trace_id_offset >= 0)
                    && (_constmethod_orig_idnum_offset >= 0);
  ```

- [ ] **Step 3: Add symbol resolution for ClassUnloadingContext and purge()**

  In vmStructs.cpp, add static variables:
  ```cpp
  static void** _class_unloading_context_addr;  // &ClassUnloadingContext::_context
  static void*  _purge_entry;                   // address of ClassLoaderDataGraph::purge(bool)
  ```

  In `initJvmFunctions()` or a new `initHookTargets()`:
  ```cpp
  _class_unloading_context_addr = (void**)_libjvm->findSymbol(
      "_ZN21ClassUnloadingContext8_contextE");
  _purge_entry = _libjvm->findSymbol(
      "_ZN20ClassLoaderDataGraph5purgeEb");
  ```

  Note: Mangled names are for GCC/Clang on Linux/macOS. On macOS, symbols have a leading underscore: `__ZN21ClassUnloadingContext8_contextE`. The profiler's existing symbol resolution handles this.

- [ ] **Step 4: Add jfr_method_id() to VMMethod**

  In vmStructs.h, inside the `VMMethod` declaration (DECLARE block):
  ```cpp
  profiler_method_id jfr_method_id() {
      if (!_has_jfr_trace_ids) return 0;

      const char* const_method = (const char*)SafeAccess::load(
          (void**)at(_method_constmethod_offset));
      if (!goodPtr(const_method)) return 0;

      uint16_t idnum = (uint16_t)SafeAccess::load16(
          (int16_t*)(const_method + _constmethod_orig_idnum_offset));

      const char* cpool = (const char*)SafeAccess::loadPtr(
          (void**)(const_method + _constmethod_constants_offset), nullptr);
      if (!goodPtr(cpool)) return 0;

      const char* holder = (const char*)SafeAccess::loadPtr(
          (void**)(cpool + _pool_holder_offset), nullptr);
      if (!goodPtr(holder)) return 0;

      uint64_t trace_id = *(uint64_t*)(holder + _klass_trace_id_offset);

      return make_method_id(trace_id, idnum);
  }
  ```

- [ ] **Step 5: Add cp_symbol_at() helper**

  In vmStructs.h, add a static helper:
  ```cpp
  static Symbol* cp_symbol_at(const char* cp, int index) {
      intptr_t* base = (intptr_t*)(cp + VMConstantPool::type_size());
      return *(Symbol**)&base[index];
  }
  ```

  This works because ConstantPool entries are an inline `intptr_t[]` array starting at offset `sizeof(ConstantPool)` from the ConstantPool pointer. Each entry is 8 bytes (pointer-sized). The `name_index` and `signature_index` from ConstMethod index directly into this array, where UTF-8 entries hold `Symbol*` values.

- [ ] **Step 6: Update verify_offsets()**

  Add assertions for new offsets. Gate `_klass_trace_id_offset` on JFR availability (don't assert on non-JFR builds or J9). All other offsets should be present on any HotSpot JDK 11+.

**Testing gate:** Build and run existing tests. Verify new offsets resolve correctly on JDK 11, 17, 21, 25 by adding a debug log at init time.

---

## Task 3: Implement MethodSymbolCache

**Files:**
- Create: `ddprof-lib/src/main/cpp/methodSymbolCache.h`
- Create: `ddprof-lib/src/main/cpp/methodSymbolCache.cpp`

- [ ] **Step 1: Design the cache data structure**

  Requirements:
  - Pre-allocated (no malloc during purge() hook — runs at safepoint)
  - Supports concurrent insert (from purge hook on GC thread) and read (from flush on profiler thread) — but in practice these don't overlap since purge runs at safepoint
  - Open-addressing hash map keyed by `profiler_method_id`
  - String storage in a pre-allocated arena (bump allocator)

  ```cpp
  struct MethodSymbolEntry {
      profiler_method_id id;           // 0 = empty slot
      const char* class_name;          // pointer into string arena
      uint16_t class_name_len;
      const char* method_name;
      uint16_t method_name_len;
      const char* signature;
      uint16_t signature_len;
  };

  class MethodSymbolCache {
      MethodSymbolEntry* _table;
      size_t _capacity;                // power of 2
      std::atomic<size_t> _size;

      char* _string_arena;             // pre-allocated string storage
      std::atomic<size_t> _arena_pos;
      size_t _arena_capacity;

  public:
      MethodSymbolCache(size_t capacity, size_t arena_bytes);
      ~MethodSymbolCache();

      // Copy symbol bytes into arena and store entry.
      // Safe to call from safepoint (no malloc).
      bool put(profiler_method_id id,
               const char* cls, int cls_len,
               const char* name, int name_len,
               const char* sig, int sig_len);

      const MethodSymbolEntry* get(profiler_method_id id) const;
      void clear();  // reset for next recording
  };
  ```

- [ ] **Step 2: Implement put/get with open addressing**

  Use linear probing. Key = `profiler_method_id`, hash = mix64(id). Empty slot sentinel = id == 0 (valid method IDs are never 0 since klass_trace_id > 0). On collision, linear probe. On arena exhaustion, stop inserting (best-effort — log a counter).

- [ ] **Step 3: Implement string arena**

  Simple bump allocator: `_arena_pos` advances atomically. `put()` copies symbol bytes from HotSpot Symbol objects into the arena. Returns pointer into the arena for the entry.

**Testing gate:** Unit test: create cache, insert entries, look up, verify strings match. Test capacity limits and arena exhaustion.

---

## Task 4: Implement Class Unload Hook

**Files:**
- Create: `ddprof-lib/src/main/cpp/classUnloadHook.h`
- Create: `ddprof-lib/src/main/cpp/classUnloadHook.cpp`

- [ ] **Step 1: Implement inline function patching**

  On install:
  1. `mprotect()` the page containing `purge()` entry to `PROT_READ | PROT_WRITE | PROT_EXEC` (or `PROT_READ | PROT_WRITE` on W^X systems)
  2. Save original bytes (enough for the trampoline jump — 12-14 bytes on x86_64, 16 bytes on aarch64)
  3. Write unconditional jump to `pre_purge_hook`:
     - x86_64: `mov rax, <addr>; jmp rax` (10 bytes) or `jmp rel32` if within ±2GB
     - aarch64: `ldr x16, .+8; br x16; .quad <addr>` (16 bytes)
  4. Flush instruction cache (`__builtin___clear_cache` on aarch64)
  5. Restore page protection

  On uninstall: reverse — write back saved bytes, flush cache.

  Note: The profiler's existing `Trap` class handles `mprotect` and cache flush. Reuse the `Trap::patch()` infrastructure for page protection management. The actual patching differs (multi-byte trampoline vs single-instruction breakpoint) but the memory protection logic is identical.

- [ ] **Step 2: Implement pre_purge_hook()**

  ```cpp
  static void pre_purge_hook(bool at_safepoint) {
      if (_class_unloading_context_addr != nullptr) {
          void* ctx = *_class_unloading_context_addr;
          if (ctx != nullptr) {
              // _cld_head is at offset 0 in ClassUnloadingContext
              char* cld = (char*)SafeAccess::loadPtr((void**)ctx, nullptr);

              while (cld != nullptr) {
                  resolve_cld_methods(cld);
                  cld = (char*)SafeAccess::loadPtr(
                      (void**)(cld + _cld_unloading_next_offset), nullptr);
              }
          }
      }

      // Call original purge()
      _original_purge(at_safepoint);
  }
  ```

- [ ] **Step 3: Implement resolve_cld_methods()**

  Walk each CLD's Klass chain, and for each InstanceKlass walk the methods array:

  ```cpp
  static void resolve_cld_methods(char* cld) {
      char* klass = (char*)SafeAccess::loadPtr(
          (void**)(cld + _cld_klasses_offset), nullptr);

      while (klass != nullptr) {
          // Read klass trace_id
          uint64_t trace_id = *(uint64_t*)(klass + _klass_trace_id_offset);

          // Read class name from Klass._name (Symbol*)
          char* klass_name_sym = (char*)SafeAccess::loadPtr(
              (void**)(klass + _klass_name_offset), nullptr);
          uint16_t cls_len = *(uint16_t*)(klass_name_sym + _symbol_length_offset);
          const char* cls_body = klass_name_sym + _symbol_body_offset;

          // Read _methods array (Array<Method*>*)
          char* methods_arr = (char*)SafeAccess::loadPtr(
              (void**)(klass + _methods_offset), nullptr);
          if (methods_arr != nullptr) {
              int num_methods = *(int*)methods_arr;  // Array._length at offset 0
              // Array._data starts after _length + alignment padding
              // Use GrowableArray _array_data_offset or compute: sizeof(int) padded to 8
              char** method_ptrs = (char**)(methods_arr + sizeof(intptr_t));

              for (int i = 0; i < num_methods; i++) {
                  char* method = method_ptrs[i];
                  if (method == nullptr) continue;

                  // Navigate Method → ConstMethod
                  char* cm = (char*)SafeAccess::loadPtr(
                      (void**)(method + _method_constmethod_offset), nullptr);
                  if (cm == nullptr) continue;

                  uint16_t idnum = *(uint16_t*)(cm + _constmethod_orig_idnum_offset);
                  profiler_method_id mid = make_method_id(trace_id, idnum);

                  // Read name and signature via constant pool
                  uint16_t name_idx = *(uint16_t*)(cm + _constmethod_name_index_offset);
                  uint16_t sig_idx = *(uint16_t*)(cm + _constmethod_signature_index_offset);
                  char* cpool = (char*)SafeAccess::loadPtr(
                      (void**)(cm + _constmethod_constants_offset), nullptr);
                  if (cpool == nullptr) continue;

                  // ConstantPool entry array at offset sizeof(ConstantPool)
                  char* name_sym = (char*)cp_symbol_at(cpool, name_idx);
                  char* sig_sym = (char*)cp_symbol_at(cpool, sig_idx);
                  if (name_sym == nullptr || sig_sym == nullptr) continue;

                  uint16_t name_len = *(uint16_t*)(name_sym + _symbol_length_offset);
                  const char* name_body = name_sym + _symbol_body_offset;
                  uint16_t sig_len = *(uint16_t*)(sig_sym + _symbol_length_offset);
                  const char* sig_body = sig_sym + _symbol_body_offset;

                  _cache->put(mid, cls_body, cls_len, name_body, name_len, sig_body, sig_len);
              }
          }

          // Next klass in CLD chain
          klass = (char*)SafeAccess::loadPtr(
              (void**)(klass + _klass_next_link_offset), nullptr);
      }
  }
  ```

- [ ] **Step 4: Add trampoline saved-prologue execution**

  The trampoline must execute the original prologue bytes that were overwritten, then jump back into `purge()` past the patch point. Two approaches:

  **Approach A (simpler):** Allocate an executable trampoline buffer. Copy saved prologue bytes into it, followed by a jump to `purge + patch_size`. On call: `pre_purge_hook()` runs the notification logic, then calls the trampoline which executes the original prologue and continues into purge().

  **Approach B (patch/unpatch):** Before calling original, uninstall the hook (restore original bytes), call `purge()` directly, then reinstall the hook. This is simpler but not thread-safe if multiple GC threads could call purge() concurrently. In practice, purge() is called from a single GC thread at a time, so this is safe.

  Recommend **Approach B** for simplicity. The hook is short-lived (active only during profiling) and purge() is called serially.

**Testing gate:** Unit test hook install/uninstall. Integration test: run profiler with class-unloading workload (custom ClassLoader that loads + discards classes in a loop), verify no crash and symbols resolve for unloaded methods.

---

## Task 5: Replace jmethodID in walkVM

**Files:**
- Modify: `ddprof-lib/src/main/cpp/stackWalker.cpp`

- [ ] **Step 1: Add JFR method ID path for interpreted frames**

  In `walkVM()`, the interpreted frame path (around lines 512-533):

  Current code:
  ```cpp
  VMMethod* method = ((VMMethod**)fp)[InterpreterFrame::method_offset];
  jmethodID method_id = getMethodId(method);
  // ...
  fillFrame(frames[depth++], FRAME_INTERPRETED, bci, method_id);
  ```

  Replace with:
  ```cpp
  VMMethod* method = ((VMMethod**)fp)[InterpreterFrame::method_offset];
  if (VMStructs::hasJfrTraceIds()) {
      profiler_method_id mid = method->jfr_method_id();
      if (mid != 0) {
          fillFrame(frames[depth++], FRAME_INTERPRETED, bci, (jmethodID)(uintptr_t)mid);
      }
  } else {
      // J9/Zing fallback
      jmethodID method_id = getMethodId(method);
      if (method_id != NULL) {
          fillFrame(frames[depth++], FRAME_INTERPRETED, bci, method_id);
      }
  }
  ```

  Note: Storing `profiler_method_id` in the `jmethodID` union field via cast. Both are 8 bytes. The frame type or a global flag distinguishes the two formats downstream.

- [ ] **Step 2: Add JFR method ID path for compiled frames**

  In the compiled frame path (around lines 569, 586):

  Current code:
  ```cpp
  fillFrame(frames[depth++], type, 0, nm->method()->id());
  ```

  Replace with:
  ```cpp
  if (VMStructs::hasJfrTraceIds()) {
      profiler_method_id mid = nm->method()->jfr_method_id();
      fillFrame(frames[depth++], type, 0, (jmethodID)(uintptr_t)mid);
  } else {
      fillFrame(frames[depth++], type, 0, nm->method()->id());
  }
  ```

  Apply the same pattern for inlined frames (around line 586):
  ```cpp
  fillFrame(frames[depth++], type, scope.bci(), scope.method()->jfr_method_id());
  ```

- [ ] **Step 3: Apply same pattern to all other getMethodId() call sites**

  There are 4 call sites for `getMethodId()` in stackWalker.cpp (lines 513, 530, 739, 897). Apply the same conditional pattern to each.

- [ ] **Step 4: Add hasJfrTraceIds() to VMStructs**

  In vmStructs.h:
  ```cpp
  static bool hasJfrTraceIds() { return _has_jfr_trace_ids; }
  ```

**Testing gate:** Run profiler on a Java application. Compare collected stack traces against baseline (jmethodID path). Verify all methods are captured. Run with both HotSpot and J9 to verify fallback.

---

## Task 6: Replace JVMTI Symbol Resolution in FlightRecorder

**Files:**
- Modify: `ddprof-lib/src/main/cpp/flightRecorder.cpp`
- Modify: `ddprof-lib/src/main/cpp/flightRecorder.h`

- [ ] **Step 1: Update MethodMap key handling**

  In `flightRecorder.h`, the `MethodMap` class uses `jmethodID` as key. When JFR trace IDs are active, the key becomes a `profiler_method_id` stored in the same `unsigned long` slot. No structural change needed — just ensure the key generation in `makeKey()` handles both formats:

  ```cpp
  static unsigned long makeKey(jmethodID method) {
      return (unsigned long)method;  // works for both jmethodID and profiler_method_id
  }
  ```

- [ ] **Step 2: Add JFR-based fillJavaMethodInfo()**

  Create a new resolution path that does NOT use JVMTI:

  ```cpp
  void Lookup::fillJavaMethodInfoFromCache(profiler_method_id mid, MethodInfo* mi) {
      // 1. Check MethodSymbolCache (populated by purge hook for unloaded classes)
      const MethodSymbolEntry* cached = _method_symbol_cache->get(mid);
      if (cached != nullptr) {
          // Copy cached strings into MethodInfo
          mi->_class = copyString(cached->class_name, cached->class_name_len);
          mi->_name = copyString(cached->method_name, cached->method_name_len);
          mi->_sig = copyString(cached->signature, cached->signature_len);
          mi->_modifiers = 0;
          return;
      }

      // 2. Class still loaded — resolve from live metadata
      //    Use the klass_trace_id → Klass* mapping built during stack walks,
      //    or walk ClassLoaderDataGraph to find the Klass.
      //    Then: Klass → _methods → Method[idnum] → ConstMethod → CP → Symbol
      resolveFromLiveMetadata(mid, mi);
  }
  ```

- [ ] **Step 3: Wire into resolveMethod()**

  In `Lookup::resolveMethod()`, add a branch before the existing JVMTI path:

  ```cpp
  if (VMStructs::hasJfrTraceIds() && bci != BCI_NATIVE_FRAME && ...) {
      profiler_method_id mid = (profiler_method_id)(uintptr_t)method;
      fillJavaMethodInfoFromCache(mid, mi);
  } else {
      // Existing JVMTI path for J9/Zing or native frames
      fillJavaMethodInfo(method, mi);
  }
  ```

- [ ] **Step 4: Implement resolveFromLiveMetadata()**

  For classes that are still loaded (not yet unloaded), resolve directly:
  - Decompose `mid` into `klass_id` and `method_idnum`
  - Look up Klass* from a `klass_id → Klass*` map (populated during stack walks — see Task 7)
  - Validate the Klass* is still alive (read `_class_loader_data`, check CLD is not unloading)
  - Navigate: `Klass → _name → Symbol` for class name
  - Navigate: `Klass → _methods → Method[idnum] → ConstMethod → {_name_index, _signature_index} → ConstantPool → Symbol` for method name and signature
  - Use the same `cp_symbol_at()` helper from VMStructs

**Testing gate:** Run profiler, produce JFR recording. Compare method names against baseline recording produced with jmethodID path. They must be identical.

---

## Task 7: Add Klass Trace ID → Klass* Live Map

**Files:**
- Create or extend: `ddprof-lib/src/main/cpp/klassMap.h` (or add to existing structures)
- Modify: `ddprof-lib/src/main/cpp/stackWalker.cpp`

- [ ] **Step 1: Create a lock-free map from masked klass_trace_id to Klass***

  Requirements:
  - Written from signal handler (during stack walks) — must be async-signal-safe
  - Read from flush thread (during symbol resolution) — must handle concurrent access
  - Entries invalidated by purge() hook when class is unloaded

  Use the same open-addressing pattern as MethodSymbolCache, pre-allocated.

- [ ] **Step 2: Populate during stack walks**

  After computing `jfr_method_id()`, register the Klass* in the map:

  ```cpp
  profiler_method_id mid = method->jfr_method_id();
  if (mid != 0) {
      uint64_t kid = klass_id_from(mid);
      const char* holder = /* already loaded in jfr_method_id() — refactor to return it */;
      _klass_map->put_if_absent(kid, holder);
  }
  ```

  This means `jfr_method_id()` should be refactored to also expose the Klass* it traversed, to avoid re-navigating the pointer chain.

- [ ] **Step 3: Invalidate entries in purge() hook**

  In `pre_purge_hook()`, after walking unloading CLDs:
  ```cpp
  // Remove entries for unloaded classes from the klass map
  _klass_map->remove(klass_id_from(make_method_id(trace_id, 0)));
  ```

**Testing gate:** Verify live map correctly tracks and invalidates entries across class load/unload cycles.

---

## Task 8: Hook Lifecycle and Integration

**Files:**
- Modify: `ddprof-lib/src/main/cpp/profiler.cpp`
- Modify: `ddprof-lib/src/main/cpp/profiler.h`

- [ ] **Step 1: Add ClassUnloadHook to Profiler**

  In `profiler.h`:
  ```cpp
  ClassUnloadHook* _class_unload_hook;
  MethodSymbolCache* _method_symbol_cache;
  ```

  Remove: `Trap _class_unload_hook_trap;` and `NotifyClassUnloadedFunc`.

- [ ] **Step 2: Install hook on profiler start**

  In `Profiler::start()`, after VMStructs is ready:
  ```cpp
  if (VMStructs::hasJfrTraceIds() && VMStructs::purgeEntry() != nullptr) {
      _method_symbol_cache = new MethodSymbolCache(64 * 1024, 4 * 1024 * 1024);
      _class_unload_hook = new ClassUnloadHook(
          VMStructs::purgeEntry(),
          VMStructs::classUnloadingContextAddr(),
          _method_symbol_cache);
      _class_unload_hook->install();
  }
  ```

- [ ] **Step 3: Uninstall hook on profiler stop**

  In `Profiler::stop()`:
  ```cpp
  if (_class_unload_hook != nullptr) {
      _class_unload_hook->uninstall();
      delete _class_unload_hook;
      _class_unload_hook = nullptr;
  }
  // Flush remaining cache entries to output before clearing
  // ... (during final recording flush)
  if (_method_symbol_cache != nullptr) {
      delete _method_symbol_cache;
      _method_symbol_cache = nullptr;
  }
  ```

**Testing gate:** Start/stop profiler multiple times. Verify no crash, no leaked trampolines, no stale hooks.

---

## Task 9: Clean Up Dead Code

**Files:**
- Modify: `ddprof-lib/src/main/cpp/stackWalker.cpp`
- Modify: `ddprof-lib/src/main/cpp/hotspot/vmStructs.h`
- Modify: `ddprof-lib/src/main/cpp/hotspot/vmStructs.cpp`
- Modify: `ddprof-lib/src/main/cpp/flightRecorder.cpp`

- [ ] **Step 1: Remove jmethodID validation code (HotSpot path only)**

  After confirming all tests pass with the new path:

  - Remove `getMethodId()` from stackWalker.cpp (lines 74-80)
  - Remove `VMMethod::id()` and `VMMethod::validatedId()` from vmStructs.h
  - Remove `check_jmethodID_hotspot()` from vmStructs.cpp
  - Remove `_can_dereference_jmethod_id` flag
  - Remove `isStaleMethodId()` from vmStructs.h

  Keep all of the above for the J9/Zing fallback path, gated behind `!hasJfrTraceIds()`.

- [ ] **Step 2: Remove JVMTI symbol resolution (HotSpot path only)**

  - Remove `GetMethodName` / `GetMethodDeclaringClass` / `GetClassSignature` calls from the HotSpot code path in `fillJavaMethodInfo()`
  - Keep for J9/Zing fallback

- [ ] **Step 3: Remove _jmethod_ids_offset from VMStructs**

  If no remaining code references `_jmethod_ids_offset` on the HotSpot path, remove it. Keep if needed for J9 fallback.

**Testing gate:** Full test suite. Verify no jmethodID usage remains in HotSpot code paths. Verify J9 fallback still works.

---

## Execution Order

| Phase | Tasks | Risk | Gate |
|---|---|---|---|
| **1 — Foundation** | Tasks 1, 2 | Low | Offsets resolve on JDK 11/17/21/25; `jfr_method_id()` returns nonzero values |
| **2 — Cache** | Task 3 | Low | Unit tests pass for cache operations |
| **3 — Hook** | Task 4 | High | Stress test with classloader churn; no crashes; symbols resolve for unloaded methods |
| **4 — Collection** | Tasks 5, 7 | Medium | Stack traces captured with profiler_method_id; compare against jmethodID baseline |
| **5 — Resolution** | Task 6 | Medium | Output recordings identical to jmethodID-based output |
| **6 — Integration** | Task 8 | Medium | Start/stop cycles clean; no resource leaks |
| **7 — Cleanup** | Task 9 | Low | Full test suite; J9 fallback verified |
