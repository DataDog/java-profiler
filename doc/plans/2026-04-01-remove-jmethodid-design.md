# Removing jmethodID from walkVM Stack Traces — Design Document

**Date:** 2026-04-01
**Author:** Jaroslav Bachorik
**Status:** DRAFT

---

## Problem Statement

The profiler currently uses `jmethodID` to identify Java methods in collected stack traces. This has several problems:

1. **jmethodID lifecycle is tied to ClassLoaderData.** When a class is unloaded, its jmethodIDs become stale. The profiler must validate them before use, and any collected stack traces referencing unloaded methods lose their method identity.

2. **jmethodID resolution requires JVMTI calls.** Converting a jmethodID to human-readable form (`GetMethodName`, `GetMethodDeclaringClass`, `GetClassSignature`) requires JVMTI calls that cannot run in a signal handler. This forces a two-phase approach: collect opaque IDs during sampling, resolve to strings later during flush.

3. **jmethodID allocation forces JVM work.** Reading `VMMethod::id()` navigates `ConstMethod → ConstantPool → pool_holder (Klass) → _methods_jmethod_ids` array. If the jmethodID hasn't been allocated yet, it's NULL and the frame is lost. The JVM lazily allocates these on first JVMTI/JNI access, so methods that were never touched by JVMTI have no jmethodID.

4. **Stale jmethodID detection is fragile.** `isStaleMethodId()` dereferences the jmethodID and checks validity — this races with GC and class unloading.

## Proposed Solution

Replace `jmethodID` with a **profiler-computed method identifier** derived from the JFR trace ID scheme, and install an **inline function hook** on `ClassLoaderDataGraph::purge()` to resolve method identifiers to symbol strings before class metadata is freed.

### Method Identifier Design

The JFR method ID formula is:

```
method_id = (klass_trace_id << 16) | orig_method_idnum
```

Where:
- `klass_trace_id` is read from `Klass::_trace_id` (8 bytes, JFR-assigned, unique per class)
- `orig_method_idnum` is read from `ConstMethod::_orig_method_idnum` (2 bytes, stable across method redefinition)

This ID is computable in a signal handler with two memory loads and a bitwise OR. No allocation, no locks, no JNI. It's stable across method redefinition (uses `orig_method_idnum`, not `method_idnum`).

**Scope:** HotSpot only. `Klass::_trace_id` is a JFR-specific field not present on J9 or Zing. On those JVMs, the profiler continues to use jmethodID as a fallback.

### Klass Trace ID Epoch Bits

The raw `_trace_id` value contains epoch/metadata bits in addition to the base class identity. The profiler must mask these consistently. The exact mask depends on JFR internals (`TRACE_ID_SHIFT`, epoch bit positions) but the key invariant is: the same mask applied at collection time and at resolution time produces matching IDs. We maintain a mapping from the masked klass trace ID to a Klass pointer, populated incrementally during stack walks, which also serves as the invalidation mechanism during class unloading.

### ConstantPool Symbol Resolution

To resolve a method's name and signature from raw memory, we need to navigate:

```
Method → _constMethod (ConstMethod*) → _name_index, _signature_index (u2 indices)
ConstMethod → _constants (ConstantPool*)
ConstantPool → entry array → Symbol* at given index
```

The ConstantPool entry array is an inline `intptr_t[]` starting immediately after the ConstantPool header:

```cpp
// From constantPool.hpp:139
intptr_t* base() const { return (intptr_t*)(((char*)this) + sizeof(ConstantPool)); }

// symbol_at(index) = *(Symbol**)&base()[index]
```

`sizeof(ConstantPool)` is already available via `VMConstantPool::type_size()` (read from `gHotSpotVMTypes` at agent init). So the resolution is:

```cpp
Symbol* cp_symbol_at(char* cp, int index) {
    intptr_t* base = (intptr_t*)(cp + VMConstantPool::type_size());
    return *(Symbol**)&base[index];
}
```

No new VMStructs offset needed for this — just the existing type size plus the new `_constmethod_name_index_offset` and `_constmethod_signature_index_offset`.

### Hooking ClassLoaderDataGraph::purge()

When classes are unloaded, the metadata (Klass*, Method*, Symbol*) is freed during `ClassLoaderDataGraph::purge()`. We hook this function to resolve any pending method IDs to strings before the memory is reclaimed.

**Why purge()?** The unloading sequence across all GCs is:

```
① SystemDictionary::do_unloading()     → marks CLDs dead, Method*/Klass* still valid
② nmethod unlink + purge + free        → compiled code freed
③ ClassLoaderDataGraph::purge()        → Metaspace freed (Klass*, Method*, Symbol* gone)
```

At purge() entry, nmethod memory is already freed but we don't need it — we have the method IDs from our stack traces. All Klass*/Method*/Symbol* metadata is still in metaspace and readable.

**Hook mechanism:** Inline function patching (trampoline). We overwrite the first bytes of `purge()` with a jump to our hook function. The hook runs on the GC thread at safepoint — no signal handler constraints, but must be fast and avoid JVM locks.

**Symbol availability:**
- Linux: `_ZN20ClassLoaderDataGraph5purgeEb` is dynamically exported (version script `global: *;`)
- macOS: Present in symbol table as local text (`t`), findable via Mach-O parsing (profiler already does this)

**Walking the unloading list:** At purge() entry, `ClassUnloadingContext::_context->_cld_head` points to the linked list of ClassLoaderData being unloaded. Each CLD has `_klasses` (head of Klass chain via `_next_link`). Each InstanceKlass has `_methods` (Array\<Method*\>). The `_cld_head` field is at offset 0 in ClassUnloadingContext (CHeapObj has no vtable, _cld_head is the first instance field).

### Safepoint Duration Impact

The hook runs at a GC safepoint, extending pause time. For typical workloads (few classes unloaded per GC), the overhead is microseconds. For scripting-heavy workloads (Groovy, Clojure) that generate thousands of classes, the cost scales with the number of methods in unloaded classes. We accept this tradeoff and will instrument the hook duration for monitoring.

### Data Flow Overview

```
  ┌──────────────────────────────────────────────────┐
  │ Signal Handler (sampling)                        │
  │                                                  │
  │ nmethod → Method* → {klass_trace_id,             │
  │                       orig_method_idnum}         │
  │ Store profiler_method_id in ASGCT_CallFrame      │
  │ Register klass_trace_id → Klass* in live map     │
  └──────────────┬───────────────────────────────────┘
                 │
                 │  profiler_method_id stored in traces
                 ▼
  ┌──────────────────────────────────────────────────┐
  │ Flush / Recording Output                         │
  │                                                  │
  │ For each frame:                                  │
  │   Check MethodSymbolCache (for unloaded classes) │
  │   Or resolve from live Klass* (for live classes) │
  │   → {class_name, method_name, signature}         │
  └──────────────────────────────────────────────────┘
                 ▲
                 │  cache populated before metadata freed
                 │
  ┌──────────────────────────────────────────────────┐
  │ purge() Hook (GC safepoint)                      │
  │                                                  │
  │ Walk ClassUnloadingContext._cld_head chain:       │
  │   CLD → _klasses → each InstanceKlass:           │
  │     Read _trace_id, _methods array               │
  │     For each Method*:                            │
  │       Compute profiler_method_id                 │
  │       Read name/signature via ConstantPool       │
  │       Store in MethodSymbolCache                 │
  │ Call original purge()                            │
  └──────────────────────────────────────────────────┘
```

### New VMStructs Offsets Required

All discoverable from `gHotSpotVMStructs` (exported by HotSpot):

| Variable | HotSpot Type.Field | Purpose |
|---|---|---|
| `_klass_next_link_offset` | `Klass._next_link` | Walk CLD's Klass chain |
| `_klass_trace_id_offset` | `Klass._trace_id` | JFR klass trace ID |
| `_constmethod_orig_idnum_offset` | `ConstMethod._orig_method_idnum` | Stable method index |
| `_constmethod_name_index_offset` | `ConstMethod._name_index` | CP index for name |
| `_constmethod_signature_index_offset` | `ConstMethod._signature_index` | CP index for signature |
| `_cld_klasses_offset` | `ClassLoaderData._klasses` | Head of Klass chain |
| `_cld_unloading_next_offset` | `ClassLoaderData._unloading_next` | Unloading CLD list |

Symbols resolved via `libjvm` symbol table lookup (not gHotSpotVMStructs):

| Symbol | Mangled Name | Purpose |
|---|---|---|
| `ClassUnloadingContext::_context` | `_ZN21ClassUnloadingContext8_contextE` | Singleton pointer |
| `ClassLoaderDataGraph::purge` | `_ZN20ClassLoaderDataGraph5purgeEb` | Hook target |

### Scope of Change

| Component | What Changes |
|---|---|
| `vmStructs.h/cpp` | New offset variables, `jfr_method_id()` on VMMethod, feature flag |
| `stackWalker.cpp` | Replace `method->id()` / `getMethodId()` with `method->jfr_method_id()` |
| `methodId.h` (new) | `profiler_method_id` type, pack/unpack helpers |
| `methodSymbolCache.h/cpp` (new) | Lock-free cache: method_id → {class, method, sig} |
| `classUnloadHook.h/cpp` (new) | purge() hook install/uninstall, pre-purge callback |
| `flightRecorder.cpp` | Replace JVMTI-based `fillJavaMethodInfo()` with cache/live lookup |
| `profiler.cpp` | Hook lifecycle (install on start, uninstall on stop) |

### What Gets Removed

- `getMethodId()` function in stackWalker.cpp
- `VMMethod::id()` and `VMMethod::validatedId()`
- `_jmethod_ids_offset` from VMStructs
- `_can_dereference_jmethod_id` flag and `isStaleMethodId()` check
- `check_jmethodID_hotspot()` / `check_jmethodID_J9()` validation functions
- JVMTI `GetMethodName` / `GetMethodDeclaringClass` / `GetClassSignature` calls in `fillJavaMethodInfo()`

### Risks and Mitigations

| Risk | Mitigation |
|---|---|
| J9/Zing has no `_trace_id` | Feature-gated: use jmethodID fallback when `_klass_trace_id_offset == -1` |
| Epoch bits in `_trace_id` change | Apply consistent masking at collection and resolution; documented separately |
| Safepoint pause extension | Instrument hook duration; profile with scripting workloads before ship |
| Version-specific struct offsets | All offsets from gHotSpotVMStructs — auto-adapts across JDK versions |
| Concurrent class unloading (ZGC/Shenandoah) | purge() is the convergence point for all GCs; hook is GC-agnostic |
