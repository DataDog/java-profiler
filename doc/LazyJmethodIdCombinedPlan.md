# Combining #864 and #867: plan

> **Working notes. Remove before the PR lands.**
> Branch: `investigate/lazy-jmethodid-vm-resolution`, off #864's `investigate/lazy-jmethodid-resolution`.
> Co-authors: Roman Kennke, Zhengyu Gu (#867). Started 2026-10-16.

Keep #864's safety model (class registry, trace-ID frame tags, redefinition marks) and add #867's
two strong ideas: resolving frames from VM memory, and keeping names of classes that get unloaded.
Leave out #867's one-chunk-per-GC writing.

## Goal

- Memory savings for **all** classes, ideally with **no jmethodIDs at all** for raw frames, not even
  for sampled classes.
- No extra GC-pause time and no recording-size growth.
- Names even for classes unloaded before the dump (`method_resolve_lazy_unloaded` close to 0).
- No JNI/JVMTI when naming raw frames.

## What to take from #867, and what to leave

| Take | Leave out |
|---|---|
| `ResolvedMethod` / `readMethod()`: names, signatures, Thread.run detection from VM memory | One JFR chunk per GC (pause and size cost) |
| Line-number decoding (`VMLineNumberStream`, `compressedLineNumberTable()`, `codeSize()`) | Rotating dictionaries inside the GC callback (likely cause of the mixed-up names) |
| `fillJavaMethodNames()` / `fillJavaMethodInfo(mi, ResolvedMethod)` refactor | Flipping the default without an opt-in (separate rollout decision) |
| `ContextClassLoaderUnloadTest`, plus its gtest additions where they still apply | The code-coverage commits and `.bak` files (their own PR) |
| The "capture names before classes unload" idea, made incremental and file-free | |

## Phase 1: resolve raw frames from VM memory instead of allocating jmethodIDs

1. Bring over #867's `ResolvedMethod`, `readMethod()`, `VMLineNumberStream`, the new vmStructs
   fields (`_constmethod_code_size`, `_constmethod_flags`, `_klass_super`, the version-dependent
   "has line-number table" constant) and `fillJavaMethodNames()`. Zhengyu as author or co-author.
2. `resolveViaRegistry()`: after `pin()`, the trace-ID check and `containsMethod()`, call
   `readMethod()` under crash protection while the class is still pinned. Return a `ResolvedMethod`
   instead of a jmethodID. Drop the dump-time `GetClassMethods`.
3. Key raw frames in Lookup's method table by (untagged `Method*`, trace-ID tag), so resolved rows
   can be reused across dumps without being mistaken for a later class at the same address. The
   per-dump cache (`_raw_method_cache`) becomes unnecessary or holds the row. Open: whether rows
   reused across dumps need a redefinition check through the registry mark (probably yes).
4. Partial mode (`fjmethodid=false`, and lazy's fallback without JFR): replace the `FindClass`
   lookup with `readMethod()`. It keeps today's redefinition gap for system-loader classes; note it,
   or cover it with the registry marks.
5. Bonus: lazy mode no longer needs dereferenceable jmethodIDs, so it could run on JDK 26+. Check
   that nothing else in its path depends on `_can_dereference_jmethod_id`.
6. Validation: sweep the OpenJDK GA tags for what `readMethod()` and the line decoding rely on (the
   compressed line-table format and its UNSIGNED5 change in JDK 20, the "has line-number table"
   flag that moved between 20 and 21, `Klass::_super`); compare decoded line tables with JVMTI
   `GetLineNumberTable` on real JVMs in a CI test; rerun NMT (expected: jmethodID memory ≈ 0 even
   for sampled classes).

## Phase 2: keep names of classes that unload before the dump, cheaply

1. Capture only methods whose frames are still unresolved **and** whose class can be unloaded.
   Record "unloadable" in the registry entry at registration, from the class loader (boot,
   platform and application loaders never unload).
2. Know what's pending without scanning every trace during a pause. Prototype and measure both:
   (a) a bounded lock-free "first seen" set the sampler fills and the hook drains; (b) walking only
   the traces created since the last capture (trace IDs grow monotonically within a storage
   instance).
3. In `GarbageCollectionStart` (VM stopped), copy names and line tables with `readMethod()` into a
   pre-resolved cache keyed by (`Method*`, tag). No JNI, no JVMTI, no file writes, no dictionary
   rotation. Incremental: only methods first seen since the last GC.
4. Skip when nothing unloadable is pending; also skip young-only pauses if they can be told apart
   (open question: GC cause through VM state?).
5. Do the same capture in the pre-redefinition hook for that class's pending frames, so frames
   refused after a redefinition keep their names too.
6. At dump time, when `pin()` reports the class gone, use the pre-resolved name instead of
   "unknown"; drop cache entries once written.
7. Validation: the GC-pause benchmark from the #867 review must show safepoint times unchanged
   compared with `fjmethodid=true`, recording size unchanged, and `ContextClassLoaderUnloadTest`
   must find names for frames of unloaded classes.

## Tests

- Everything in #864.
- #867's class-unload test.
- A JVMTI-against-VM line-table comparison test.
- The GC-pause and recording-size benchmark as a nightly or slow test, with thresholds.
- `LazyRedefinitionStressTest` extended to check that frames refused after a redefinition still
  have names (phase 2, step 5).

## Order and PR structure

1. #864 first, roughly as it is: opt-in, reviewed twice, tested across the LTS releases.
2. PR A, phase 1 (this branch): VM-memory resolution with no jmethodIDs, co-authored with Zhengyu.
3. PR B, phase 2: names for unloaded classes; Zhengyu might want to lead it.
4. Default flip after a nightly soak, watching the counters.

## Risks and open questions

- More parsing of HotSpot internals for names and line tables; the phase 1 sweep is meant to
  contain that.
- Pending-frame tracking in phase 2 must keep signal-handler work and memory bounded.
- Whether young pauses can be told apart without GC-specific internals.
- Whether partial mode gets the registry's redefinition marks, or stays as today.

## Measurements to compare against (from the #867 review)

macOS arm64, JDK 25, G1, ~650–950 young GCs/s, 15 s: safepoint time per young GC 0.34 ms (no
profiler), 0.35 ms (`fjmethodid=true`), 0.36 ms (#864), 0.84 ms (#867). NMT, 1M methods in
custom-loader classes: preloading ~15.8 MiB; #864 ~1 MiB. Harness: `/tmp/gcbench` and
`/tmp/jmbench` on the Mac (not in the repo).
