# Profiler Memory Requirements and Limitations

## Overview

The Datadog Java Profiler has inherent memory requirements due to its architecture combining signal-safe stack sampling, JFR event recording, and constant pool management. This document describes all major memory consumers, their costs, limitations, and when the profiler may not be appropriate for certain workloads.

The sizes below are estimates. The profiler's own native allocations are measured at
runtime: `NativeMem` (`ddprof-lib/src/main/cpp/nativeMem.h`) keeps live, average and peak
bytes for each category (`calltrace`, `dictionary`, `line_tables`, `thread_local`,
`jfr_buffers`, `method_map`, `perf`, `ctimer`, ...), and every chunk carries them as
`datadog.ProfilerCounter` events named `native_mem_live_bytes.<category>`,
`native_mem_avg_bytes.<category>`, `native_mem_max_bytes.<category>` and
`native_mem_chunk_overhead_bytes.<category>`. jmethodIDs are allocated by the JVM and are
not part of these figures. The category set is not fixed (`ctimer` is the newest), so
match these counters by prefix rather than by a fixed list. The `ctimer` gauge and the
table part of the `perf` gauge count reserved, mostly untouched tid-indexed tables
(`pid_max` slots each), so they overstate RSS and are upper bounds.

## Memory Requirements

### 1. jmethodID Preallocation

**What it is:**
- AsyncGetCallTrace (AGCT) reports frames as jmethodIDs and runs in a signal handler,
  where it cannot allocate them. The profiler therefore creates them ahead of time by
  calling `GetClassMethods()` for loaded classes (at start, for all loaded classes, and
  from the ClassPrepare callback for new ones).
- How many classes are preloaded depends on `fjmethodid` and the stack walker
  (`JVMSupport::initExecution()`):

| Setting | Preloaded |
|---------|-----------|
| `fjmethodid=true` (default), or any non-HotSpot JVM, or `cstack` other than `vm` | All classes |
| `fjmethodid=false` with `cstack=vm` on HotSpot | Only classes that can be unloaded (not from the system class loader, or hidden/lambda classes); the others are reported as raw `Method*` frames |
| `fjmethodid=lazy` with `cstack=vm` on HotSpot | None; frames are resolved from `Method*` at dump time (falls back to `false` if the needed VM structures are missing) |

**Memory cost (full preload):**
```
Memory = (Number of Classes) × (Average Methods per Class) × (JVM Method Structure Size)

Typical overhead (UNVERIFIABLE: JVM-internal sizes and class/method counts are not derivable from this repository):
- Normal application: 10K-100K classes × 15 methods × 68 bytes = 10-150 MB
- High class churn: 1M+ classes × 15 methods × 68 bytes = 1GB+
```

**JVM internal allocation breakdown:**
- Method structure: ~40-60 bytes (varies by JDK version)
- ConstMethod metadata: variable (includes bytecode)
- Hash table entries for jmethodID lookup
- Memory allocator overhead

**Key constraint:**
- Memory persists until class is unloaded (cannot be freed while class exists)
- Classes with long-lived ClassLoaders never free this memory
- **This is NOT a bug** - it follows from AGCT needing jmethodIDs in the signal handler

### 2. Line Number Tables

**What it is:**
- Maps bytecode index (BCI) to source line numbers for stack traces
- Only allocated for methods that appear in samples (lazy allocation)

**Memory cost:**
```
Memory = (Number of Sampled Methods) × (Average Entries per Method) × (Entry Size)

Typical overhead (method/entry counts UNVERIFIABLE estimates):
- Sampled methods: 1K-10K (subset of all methods)
- Entries per method: 5-20 line number mappings
- Entry size: 16 bytes (sizeof(jvmtiLineNumberEntry): jlocation 8 + jint 4 + padding on LP64)
- Total: 80 KB - 3.2 MB (negligible)
```

**Lifecycle:**
- Allocated during JFR serialization when a method first appears in samples
  (`Lookup::fillJavaMethodInfo()`)
- Held by `SharedLineNumberTable` through a `shared_ptr` in `MethodInfo`
- Tracked by the `LINE_NUMBER_TABLES` counter and the `line_tables` native-memory category
- Freed when the `MethodInfo` is removed (method-map cleanup, see section 8) or the
  recording is destroyed; JVMTI-returned tables go back through `jvmti->Deallocate()`,
  tables decoded from VM metadata through `free()`

### 3. CallTraceStorage and Hash Tables

**What it is:**
- Three `CallTraceHashTable` instances (active, standby, scratch) storing unique stack
  traces; see [CallTraceStorage](../architecture/CallTraceStorage.md)
- Each table's hash arrays and trace records are bump-allocated from its own
  `LinearAllocator` (8 MB chunks)

**Memory cost:**
```
Per hash table:
- Initial capacity: 65,536 slots
- Slot size: 16 bytes (8-byte key + 8-byte CallTraceSample pointer)
- Initial table: ~1 MB
- Expands at 75% load by chaining a table of double capacity (128K, 256K slots);
  expansion stops once the next table would not fit in one 8 MB chunk
- Trace records: variable, depend on stack depth and diversity

Typical overhead (UNVERIFIABLE estimate; depends on workload):
- 3 hash tables × 1-7 MB of slot arrays
- Trace records: 8-32 MB (depends on stack depth and diversity)
- Total: 11-44 MB for typical applications
```

`NM_CALLTRACE` counts the bytes actually bump-allocated, not the reserved chunk capacity.

**Growth patterns:**
- Bounded by unique stack trace count per cycle; tables are reset at every
  `processTraces()` rotation, keeping only traces a liveness checker preserves
- Applications with stable code paths: 10K-100K unique traces
- Applications with dynamic dispatch: 100K-1M unique traces

**Lifecycle:**
- Allocated with the `Profiler` singleton
- Rotated and partly reset on every JFR chunk
- Cleared on profiler restart

### 4. RefCountSlot Arrays (Thread-Local Reference Counting)

**What it is:**
- Cache-aligned slots used by [`RefCountGuard`](../architecture/RefCountGuard.md) for
  lock-free reclamation of call-trace tables and string-dictionary buffers
- Each slot occupies one cache line (64 bytes) to eliminate false sharing

**Memory cost:**
```
Fixed allocation (static arrays):
- MAX_THREADS = 8192 slots × 64 bytes = 512 KB (refcount_slots)
- 8192 × 4 bytes = 32 KB (slot_owners)
```

**Lifecycle:**
- Static storage; never grows or shrinks

### 5. String Dictionaries (Constant-Pool Deduplication)

**What it is:**
- Three `StringDictionary` instances in `Profiler`: `_class_map` (class names),
  `_string_label_map` (labels such as endpoints) and `_context_value_map` (tracer
  context attribute values); see [StringDictionary](../architecture/StringDictionary.md)
- Each is triple-buffered. Each buffer has a 128-row × 3-cell root `SBTable` (~6 KB),
  heap-allocated overflow tables, and a `StringArena` of 512 KB chunks for the key strings
- Two plain `Dictionary` instances (`_packages`, `_symbols`) live in the per-dump `Lookup`
  and are freed after each dump

**Memory cost:**
```
Fixed per StringDictionary:
- 3 buffers × (~6 KB root table + one 512 KB arena chunk) ≈ 1.5 MB
- 3 dictionaries ≈ 4.6 MB

Growth:
- Further 512 KB arena chunks and overflow tables as unique strings accumulate
- Bounded by callers' limits (e.g. the class-name cap in profiler.h)
```

**Growth patterns:**
- Class names: Bounded by loaded class count
- String labels: Bounded by profiling event labels
- Context values: Bounded by unique span/trace attribute values

**Lifecycle:**
- Allocated with the `Profiler` singleton
- Buffers rotate with each dump; a rotated-out buffer is cleared (keeping its root
  table and first arena chunk)
- `clearAll()` on a fresh profiler start resets all buffers

### 6. Recording Buffers (JFR Event Storage)

**What it is:**
- Per-stripe buffers for JFR event serialization in `Recording`
- `CONCURRENCY_LEVEL` = 16 buffers to minimize lock contention

**Memory cost:**
```
Per buffer:
- RecordingBuffer size: 65,536 bytes + 8,192 overflow guard = 73,728 bytes

Total allocation:
- 16 buffers × 73,728 bytes = 1,179,648 bytes (~1.1 MB)
```

**Lifecycle:**
- Part of the `Recording` object, created at recording start
- Fixed size, no growth
- Flushed to the JFR file when they fill and at chunk end
- Freed when the recording is destroyed

### 7. ThreadIdTable Arrays

**What it is:**
- Hash tables tracking active thread IDs for JFR thread metadata
- `ThreadIdTable _thread_ids[CONCURRENCY_LEVEL][2]` in `Recording` (double-buffered)

**Memory cost:**
```
Per table:
- TABLE_SIZE = 256 entries
- Entry size: 4 bytes (atomic<int>)
- Table size: 1,024 bytes

Total allocation:
- 16 concurrency levels × 2 tables × 1,024 bytes = 32 KB
```

**Lifecycle:**
- Part of the `Recording` object
- Cleared during buffer rotation
- Fixed size, no growth

### 8. MethodMap (MethodInfo Storage)

**What it is:**
- `MethodMap` is a `std::map<unsigned long, MethodInfo>`; the key is a jmethodID, a raw
  `Method*` plus frame tag, a native symbol address, packed remote-frame data, or a
  vtable-receiver class id (see the key-encoding comment above `MethodMap`)
- Only methods that appear in stack traces are stored (lazy allocation)
- Implements age-based cleanup to prevent unbounded growth in continuous profiling

**Memory cost:**
```
Per entry (approximate):
- MethodInfo: ~56 bytes (including the shared_ptr to its line number table)
- std::map node overhead: ~32-48 bytes
- Total per method: ~100 bytes

Typical overhead (sampled-method count is an UNVERIFIABLE estimate):
- Sampled methods: 1K-10K
- Total: 100 KB - 1 MB
```

**Growth patterns:**
- Grows with sampled method diversity during warmup
- Converges once all hot methods are encountered
- **With cleanup enabled (default):** Methods unused for 3 consecutive chunks are removed
- **Without cleanup:** Would grow unboundedly in applications with high method churn

**Lifecycle:**
- Entries are added during JFR serialization when methods are first sampled
- `writeStackTraces()` marks the methods it writes as referenced
- `Recording::cleanupUnreferencedMethods()` runs in `finishChunk()` on the
  `switchChunk()` path: it increments the age of unreferenced methods and removes those
  with age >= 3 (`AGE_THRESHOLD`)
- Line number tables are freed with their `MethodInfo` (via `shared_ptr`)
- Cleanup can be disabled with `mcleanup=false` (not recommended; default is `mcleanup=true`)

### 9. Per-Thread Context Storage (Tracer Integration)

**What it is:**
- Each `ProfiledThread` embeds the OTEP thread-context record and the profiler's sidecar
  fields; see [TLSContext](../architecture/TLSContext.md)

**Memory cost:**
```
Per thread (inside ProfiledThread):
- OtelThreadContextRecord: 640 bytes (header + attribute data)
- Tag encodings: 10 × 4 bytes = 40 bytes (DD_TAGS_CAPACITY = 10)
- Local root span ID: 8 bytes
- Total: ~688 bytes per thread, plus the rest of ProfiledThread

Typical overhead:
- 100-500 threads: ~70-350 KB
- 1000+ threads: ~700 KB+
```

**Growth patterns:**
- One record per thread with a `ProfiledThread`
- Context values are deduplicated in `_context_value_map` (section 5)

**Lifecycle:**
- Lives as long as the thread's `ProfiledThread`
- Counted in the `thread_local` native-memory category

### Summary: Total Memory Overhead

The totals are rough estimates (UNVERIFIABLE from code: they depend on workload and JVM
internals); use the `native_mem_*` counters for actual values. Only the rows marked
"(fixed)" follow directly from code constants.

**Typical Java Application (10K-100K classes, stable code paths):**
```
Component                          Memory Overhead
─────────────────────────────────────────────────────
jmethodID preallocation            10-150 MB (JVM internal, NMT Internal category)
Line number tables                 80 KB - 3.2 MB
CallTraceStorage hash tables       11-44 MB
RefCountGuard slot arrays          544 KB (fixed)
String dictionaries (3x)           ~4.6 MB - 10 MB
Recording buffers                  1.1 MB (fixed)
ThreadIdTable arrays               32 KB (fixed)
MethodMap                          100 KB - 1 MB
Per-thread context                 70-700 KB (depends on thread count)
─────────────────────────────────────────────────────
TOTAL (excluding jmethodID):       ~18-60 MB
TOTAL (including jmethodID):       ~28-210 MB
```

**High Class Churn Application (1M+ classes):**
```
Component                          Memory Overhead
─────────────────────────────────────────────────────
jmethodID preallocation            1+ GB (grows with class count)
Line number tables                 1-10 MB
CallTraceStorage hash tables       50-200 MB (more unique traces)
RefCountGuard slot arrays          544 KB (fixed)
String dictionaries (3x)           10-50 MB (more unique strings/contexts)
Recording buffers                  1.1 MB (fixed)
ThreadIdTable arrays               32 KB (fixed)
MethodMap                          1-10 MB
Per-thread context                 0.7-3 MB (high thread count)
─────────────────────────────────────────────────────
TOTAL (excluding jmethodID):       ~65-275 MB
TOTAL (including jmethodID):       1+ GB (dominated by jmethodID)
```

**Key observations:**
- For normal applications: Total overhead is roughly 28-210 MB
- For high class churn: jmethodID dominates memory usage (1+ GB) unless
  `fjmethodid=lazy` (or `false`) with `cstack=vm` avoids most of the preloading
- Most non-jmethodID memory converges after warmup
- MethodMap is bounded by age-based cleanup (enabled by default)

## Limitations and Restrictions

### 1. High Class Churn Applications

**Symptom:**
- Native memory (NMT Internal category) grows continuously
- Growth proportional to class loading rate
- Memory does not decrease even if classes are GC'd (requires ClassLoader unload)

**Root cause:**
- Application continuously generates new classes without unloading
- Common culprits:
  - Groovy scripts evaluated without caching
  - Dynamic proxies created per-request
  - CGLIB/Javassist code generation without caching
  - ClassLoader leaks preventing class unloading

**Impact:**
- 1M classes = ~1 GB overhead (acceptable in some cases)
- 10M classes = ~10 GB overhead (likely unacceptable)

**When profiler is NOT appropriate:**
- Applications that generate millions of classes
- Unbounded class growth patterns
- ClassLoader leaks that prevent class unloading

**Recommendation:**
```
If NMT Internal category grows beyond acceptable limits:
1. Diagnose class explosion (see diagnosis section below)
2. Fix application-level class leak or caching issue
3. On HotSpot, try fjmethodid=lazy (or fjmethodid=false) with cstack=vm,
   which skips most or all jmethodID preloading
4. If unfixable: Disable profiler in production
   - Profile only in staging with shorter runs
   - Use alternative observability (JFR events, metrics, tracing)
```

### 2. No Per-Method Memory Control

**Limitation:**
- Cannot selectively preallocate jmethodIDs for specific methods
- When a class is preloaded, `GetClassMethods()` allocates for ALL methods in the class
- Cannot free jmethodIDs while profiling (required for signal-safe operation)

**Why:**
- AGCT can encounter any method in any stack trace unpredictably
- Signal handler cannot call JVM to allocate jmethodIDs on-demand (not signal-safe)
- Selective allocation would cause profiler failures (missing method information)

The per-class choice is only available with `cstack=vm` on HotSpot, where the VM stack
walker can record raw `Method*` frames instead of jmethodIDs (see section 1 of Memory
Requirements).

### 3. Memory Persists Until Class Unload

**Limitation:**
- jmethodID memory cannot be freed while class is loaded
- Even if method is never sampled, its jmethodID exists
- Only freed when ClassLoader is GC'd and class is unloaded

**Impact:**
- Long-lived applications with stable classes: Acceptable (one-time cost)
- Applications with high class churn: Unbounded growth

**Workaround:**
- AGCT (`cstack` other than `vm`) and non-HotSpot JVMs always need preloaded jmethodIDs
- On HotSpot with `cstack=vm`, `fjmethodid=false` preloads only classes that can be
  unloaded, and `fjmethodid=lazy` preloads none

## When to Use the Profiler

### ✅ Appropriate Use Cases

**Stable class count applications:**
- Typical web services, microservices
- Batch processing jobs
- Applications with well-defined class sets
- Expected memory overhead: ~28-210 MB total
  - jmethodID: 10-150 MB
  - Profiler data structures: ~18-60 MB
  - Per-thread context: < 1 MB

**Moderate class churn:**
- Applications loading 100K-1M classes total
- Expected memory overhead: 100 MB - 1 GB total
  - jmethodID: Dominant component (70-90% of total)
  - Profiler data structures: 65-275 MB
  - Per-thread context: < 3 MB
- Monitor NMT Internal category to ensure convergence

### ⚠️ Caution Required

**Dynamic scripting with caching:**
- Groovy, JavaScript engines IF scripts are cached
- Code generation frameworks IF classes are cached
- Monitor NMT Internal category growth closely

**Microservices with hot reloading:**
- Frequent redeployments cause class reloading
- Acceptable if reloads are infrequent (hourly/daily)
- Problematic if reloads are continuous

### ❌ NOT Appropriate

**Unbounded class generation:**
- Groovy scripts evaluated per-request without caching
- Dynamic proxies generated per-request
- Code generation without caching
- Expected memory: Unbounded growth (9+ GB observed in production)
- Root cause: Application generates millions of classes (class explosion bug)

**Known ClassLoader leaks:**
- Applications that leak ClassLoaders
- Classes never get unloaded
- Memory grows without bound
- Example: 9.1M classes = ~9.2 GB jmethodID overhead alone

**Extreme class counts:**
- Applications requiring 10M+ classes
- Expected memory: 10+ GB total overhead
  - jmethodID: 9-10 GB
  - Profiler data structures: 1-2 GB
- **This is unacceptable** - disable profiler and fix application class explosion bug first

## Diagnosing Class Explosion

If NMT Internal category shows unbounded growth:

### Step 1: Enable Class Loading Logging

```bash
# JDK 9+
-Xlog:class+load=info,class+unload=info:file=/tmp/class-load.log

# JDK 8
-XX:+TraceClassLoading -XX:+TraceClassUnloading
```

### Step 2: Monitor Class Counts

```bash
# Count loaded classes
jcmd <pid> VM.classloader_stats

# Show class histogram (top 100)
jcmd <pid> GC.class_histogram | head -100

# Count total methods
jcmd <pid> VM.class_hierarchy | grep -c "method"

# Examine metaspace
jcmd <pid> VM.metaspace statistics
```

### Step 3: Identify Patterns

**Look for:**
- Repeated class name patterns (e.g., `Script123`, `$$Lambda$456`, `EnhancerByCGLIB$$abc`)
- ClassLoaders with high class counts that never get GC'd
- Libraries known for code generation (Groovy, CGLIB, Javassist, ASM)
- Method count per class (if unusually high, indicates code complexity)

**Expected findings for problematic applications:**
- Class names show sequential numbering (leak/no caching)
- ClassLoaders persist with growing class counts (ClassLoader leak)
- Class load rate is constant over time (not converging)

### Step 4: Fix Root Cause

**Common fixes:**

1. **Cache compiled scripts:**
   ```java
   // BAD: New class per evaluation
   new GroovyShell().evaluate(script);

   // GOOD: Cache compiled classes
   scriptCache.computeIfAbsent(scriptHash,
       k -> new GroovyShell().parse(script));
   ```

2. **Reuse dynamic proxies:**
   ```java
   // BAD: New proxy class per instance
   Proxy.newProxyInstance(loader, interfaces, handler);

   // GOOD: Cache proxy classes or use interfaces
   ```

3. **Configure framework caching:**
   - CGLIB: `Enhancer.setUseCache(true)`
   - Javassist: Reuse `ClassPool` instances
   - Groovy: Configure `CompilerConfiguration` with caching

4. **Fix ClassLoader leaks:**
   - Properly dispose of ClassLoaders
   - Use weak references for dynamic class caches
   - Monitor ClassLoader lifecycle

### Step 5: Verify Fix

After fixing application:
```bash
# Class count should stabilize after warmup
watch -n 10 'jcmd <pid> GC.class_histogram | head -5'

# NMT Internal should plateau
watch -n 10 'jcmd <pid> VM.native_memory summary | grep Internal'
```

**Expected result:**
- Class count converges to stable number (10K-100K for typical apps)
- Method count stabilizes (150K-1.5M methods for typical apps)
- NMT Internal growth stops after warmup
- Overhead: 10-150 MB (acceptable)

## Monitoring Recommendations

### NMT Metrics to Track

**Note on RSS (Resident Set Size) Measurements:**
RSS measurements are unreliable for tracking profiler memory usage:
- GraalVM JVMCI: Can show negative RSS growth due to aggressive GC shrinking heap
- Zing JDK: Large divergence between NMT and RSS measurements (3.6% vs 82.5%)
- Recommendation: **Use NMT Internal category** to track JVM-side cost (jmethodIDs,
  JVMTI-allocated buffers), and the profiler's `native_mem_*` counters for its own
  structures: those are allocated with libc `malloc`/`calloc` or raw `mmap`
  (`OS::safeAlloc()` in `linearAllocator.cpp`), which NMT does not track

```bash
# Enable NMT in production (minimal overhead)
-XX:NativeMemoryTracking=summary

# Collect baseline after warmup
jcmd <pid> VM.native_memory baseline

# Check growth periodically
jcmd <pid> VM.native_memory summary.diff
```

**Alert thresholds for NMT Internal category:**
- Growth > 500 MB after warmup: Investigate class loading patterns
- Growth > 2 GB: Likely class explosion (check jmethodID allocations)
- Growth > 10 GB: **Unacceptable** - disable profiler immediately
- Continuous growth (not converging): Application bug requiring fix

**Breakdown analysis:**
- Use `jcmd <pid> VM.native_memory detail` to see allocation sites
- GetClassMethods: jmethodID allocations (should converge)
- GetLineNumberTable: Line number tables (should converge)
- Profiler data structures (CallTraceStorage, StringDictionary, etc.) are not visible
  to NMT (libc `malloc`/raw `mmap`); the `native_mem_*` counters break these down by category

### Class Count Metrics

```bash
# Track loaded classes over time
jcmd <pid> GC.class_histogram | head -1

# Expected pattern:
# - Rapid growth during warmup (first few minutes)
# - Convergence to stable count
# - No growth during steady state
```

## References

### Why jmethodID Preallocation is Required

**AsyncGetCallTrace (AGCT):**
- Signal-safe stack walking (operates in SIGPROF handler)
- Cannot acquire locks or call most JVM functions
- Must have all jmethodIDs allocated before profiling
- The VM stack walker (`cstack=vm`) on HotSpot can avoid this; see section 1 of Memory
  Requirements

**Detailed explanation:**
- [jmethodIDs in Profiling: A Tale of Nightmares](https://mostlynerdless.de/blog/2023/07/17/jmethodids-in-profiling-a-tale-of-nightmares/)

**Key quote:**
> "Profilers must ensure every method has an allocated jmethodID before profiling starts. Without preallocation, profilers risk encountering unallocated jmethodIDs in stack traces, making it impossible to identify methods safely."

### JVM Internals

**Method structure allocation:**
- [JDK-8062116](https://bugs.openjdk.org/browse/JDK-8062116) - GetClassMethods performance (JDK 8 specific)
- [JDK-8268406](https://www.mail-archive.com/serviceability-dev@openjdk.org/msg22686.html) - jmethodID memory management

**JVMTI specification:**
- [JVMTI 1.2 Specification](https://docs.oracle.com/javase/8/docs/platform/jvmti/jvmti.html)

## Implementation Details

### Code Locations

Paths are relative to `ddprof-lib/src/main/cpp/`.

**1. jmethodID preallocation:**
- `jvmSupport.cpp` - `JVMSupport::initExecution()` picks the preload mode;
  `loadAllMethodIDsIfNeeded()` / `loadMethodIDsIfNeeded()` run at start and from the
  ClassPrepare callback; `loadMethodIDsImpl()` calls `GetClassMethods()`
- `hotspot/hotspotSupport.{h,cpp}` - `shouldPreloadJmethodIDs()`,
  `loadMethodIDsIfNeededImpl()` (partial mode), lazy resolution
- `arguments.cpp` - `fjmethodid=true|false|lazy` parsing

**2. Line number table management:**
- `flightRecorder.h` / `flightRecorder.cpp` - `SharedLineNumberTable` and its destructor
- `flightRecorder.cpp` - `Lookup::fillJavaMethodInfo()` allocates tables lazily
- `counters.h` - `LINE_NUMBER_TABLES` counter

**3. CallTraceStorage:**
- `callTraceStorage.{h,cpp}` - triple-buffered table management
- `callTraceHashTable.{h,cpp}` - hash table; `INITIAL_CAPACITY = 65536`, `LOAD_RATIO = 0.75`,
  `CALL_TRACE_CHUNK = 8 MB`

**4. RefCountGuard slot arrays:**
- `refCountGuard.h` - `RefCountSlot` (64 bytes), `MAX_THREADS = 8192`

**5. String dictionaries:**
- `stringDictionary.h` - `StringDictionary`, `SBTable`, `StringArena` (`CHUNK_SIZE = 512 KB`)
- `profiler.h` - `_class_map`, `_string_label_map`, `_context_value_map`
- `dictionary.h` - `Dictionary` (`ROWS = 128`, `CELLS = 3`), used for `Lookup::_packages`
  and `Lookup::_symbols`

**6. Recording buffers:**
- `buffers.h` - `RECORDING_BUFFER_SIZE = 65536`, `RECORDING_BUFFER_OVERFLOW = 8192`
- `flightRecorder.h` - `RecordingBuffer _buf[CONCURRENCY_LEVEL]`, `CONCURRENCY_LEVEL = 16`

**7. ThreadIdTable:**
- `threadIdTable.h` - `TABLE_SIZE = 256`
- `flightRecorder.h` - `ThreadIdTable _thread_ids[CONCURRENCY_LEVEL][2]`

**8. MethodMap:**
- `flightRecorder.h` - `MethodMap`, `MethodInfo` (`_referenced`, `_age`)
- `flightRecorder.cpp` - `Recording::cleanupUnreferencedMethods()`, called from
  `finishChunk()` when `switchChunk()` requests cleanup; `writeStackTraces()` marks
  referenced methods
- `arguments.h` / `arguments.cpp` - `_enable_method_cleanup` (default `true`), `mcleanup`

**9. Per-thread context storage:**
- `threadLocalData.h` - `_otel_ctx_record`, `_otel_tag_encodings`, `_otel_local_root_span_id`
- `otel_context.h` - `OtelThreadContextRecord` (`OTEL_MAX_RECORD_SIZE = 640`)
- `context.h` - `DD_TAGS_CAPACITY = 10`

**Native-memory accounting:**
- `nativeMem.h` - categories and live/avg/max tracking
- `flightRecorder.cpp` - `Recording::writeNativeMem()` emits the per-category counters

### Known Issues Fixed

**GetLineNumberTable leak (Fixed):**
- SharedLineNumberTable destructor was not properly deallocating JVMTI memory
- Impact: 1.2 GB leak for applications sampling 3.8M methods
- Fix: Added null checks and error handling in destructor (commit 8ffdb30e)
- Tracking: LINE_NUMBER_TABLES counter provides observable lifecycle tracking (commit 257d982d)
- Test: `GetLineNumberTableLeakTest` validates cleanup via TEST_LOG output (RSS unreliable across JVMs)

**MethodMap unbounded growth (Fixed):**
- Recording._method_map accumulated ALL methods forever in long-running applications
- Impact: 3.8M methods × ~300 bytes = 1.2 GB over days in production
- Root cause: Recording objects live for entire app lifetime, never freed methods
- Fix: Age-based cleanup removes methods unused for 3+ consecutive chunks
- Implementation: Mark-and-sweep during switchChunk(), enabled by default
- Test: `GetLineNumberTableLeakTest.testCleanupEffectivenessComparison()` compares growth with and without cleanup
- Feature flag: `mcleanup=true` (default: enabled), `mcleanup=false` to disable

**Test validation approach:**
- Test uses TEST_LOG output for validation (commits 7ed1e7eb, 257d982d)
- RSS measurements removed due to unreliability across JVMs (commits 33f6c5c0, 4bbfcfe8)
- Counter infrastructure provides observable line number table lifecycle tracking

**Previous investigation findings:**
- See git history for detailed investigation (commits 8ffdb30e, a9fa649c, 2ab1d263)
- Investigation confirmed jmethodID preallocation is required, not a bug
