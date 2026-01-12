# Profiler Memory Requirements and Limitations

**Last Updated:** 2026-01-12

## Overview

The Datadog Java Profiler has inherent memory requirements due to its architecture combining signal-safe stack sampling, JFR event recording, and constant pool management. This document describes all major memory consumers, their costs, limitations, and when the profiler may not be appropriate for certain workloads.

## Memory Requirements

### 1. jmethodID Preallocation (Required for AGCT)

**What it is:**
- Every Java method needs a jmethodID allocated before the profiler can identify it in stack traces
- AGCT operates in signal handlers where lock acquisition is forbidden
- Therefore, jmethodIDs must be preallocated when classes are loaded (ClassPrepare callback)

**Memory cost:**
```
Memory = (Number of Classes) × (Average Methods per Class) × (JVM Method Structure Size)

Typical overhead:
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
- **This is NOT a bug** - it's fundamental to AGCT architecture

### 2. Line Number Tables (Optimized)

**What it is:**
- Maps bytecode index (BCI) to source line numbers for stack traces
- Only allocated for methods that appear in samples (lazy allocation)

**Memory cost:**
```
Memory = (Number of Sampled Methods) × (Average Entries per Method) × (Entry Size)

Typical overhead:
- Sampled methods: 1K-10K (subset of all methods)
- Entries per method: 5-20 line number mappings
- Entry size: 8 bytes (jvmtiLineNumberEntry)
- Total: 40 KB - 1.6 MB (negligible)
```

**Lifecycle:**
- Allocated during JFR flush when method first appears in samples
- Stored in SharedLineNumberTable with shared_ptr reference counting
- Deallocated when MethodInfo is destroyed (profiler stop/restart)

### 3. CallTraceStorage and Hash Tables

**What it is:**
- Triple-buffered hash tables storing unique stack traces with lock-free rotation
- Active storage: Accepts new traces from profiling events
- Standby storage: Background storage for JFR serialization
- Scratch storage: Spare table for rotation

**Memory cost:**
```
Per hash table:
- Initial capacity: 65,536 entries
- Entry size: 16 bytes (8-byte key + 8-byte CallTraceSample)
- Initial table: ~1 MB
- Auto-expands at 75% capacity (doubles to 128K, 256K, etc.)
- LinearAllocator chunks: 8 MB per chunk

Typical overhead:
- 3 hash tables × 1-4 MB = 3-12 MB (depends on active traces)
- Chunk allocations: 8-32 MB (depends on stack depth and diversity)
- Total: 11-44 MB for typical applications
```

**Growth patterns:**
- Bounded by unique stack trace count (converges after warmup)
- Applications with stable code paths: 10K-100K unique traces
- Applications with dynamic dispatch: 100K-1M unique traces

**Lifecycle:**
- Allocated at profiler start
- Grows during warmup as new traces are discovered
- Converges to stable size once all code paths are sampled
- Cleared and reset during profiler stop/restart

### 4. RefCountSlot Arrays (Thread-Local Reference Counting)

**What it is:**
- Cache-aligned slots for lock-free memory reclamation of hash tables
- Each slot occupies one cache line (64 bytes) to eliminate false sharing

**Memory cost:**
```
Fixed allocation:
- MAX_THREADS = 8192 slots
- Slot size: 64 bytes (cache line aligned)
- Total: 512 KB (fixed, independent of actual thread count)
```

**Lifecycle:**
- Allocated once at profiler initialization
- Never grows or shrinks
- Reused throughout profiler lifetime

### 5. Dictionary Instances (String Deduplication)

**What it is:**
- Four Dictionary instances for JFR constant pools:
  - _class_map: Class name strings
  - _string_label_map: Label strings
  - _context_value_map: Tracer context attribute values
  - _packages (in Lookup): Package name strings
- Multi-level hash table with 128 rows × 3 cells per level

**Memory cost:**
```
Per dictionary:
- Initial table: sizeof(DictTable) = ~3 KB
- Key storage: Variable-length strings (malloc'd)
- Additional levels: 3 KB per level (rare, only on collision)

Typical overhead:
- 4 dictionaries × 3 KB = 12 KB (initial tables)
- String storage: 100 KB - 2 MB (depends on unique strings)
- Context values: Variable (depends on tracer integration)
- Total: 112 KB - 8 MB for typical applications
```

**Growth patterns:**
- Grows with unique class/method names encountered
- Class names: Bounded by loaded class count
- String labels: Bounded by profiling event labels
- Context values: Bounded by unique span/trace attribute values
- Package names: Typically small (< 1000 unique packages)

**Lifecycle:**
- Allocated at profiler start
- Grows during warmup
- Converges once all classes/methods/contexts are sampled
- Cleared during profiler stop/restart

### 6. Recording Buffers (JFR Event Storage)

**What it is:**
- Thread-local buffers for JFR event serialization
- CONCURRENCY_LEVEL = 16 buffers to minimize lock contention

**Memory cost:**
```
Per buffer:
- RecordingBuffer size: 65,536 bytes + 8,192 overflow guard = 73,728 bytes

Total allocation:
- 16 buffers × 73,728 bytes = 1,179,648 bytes (~1.1 MB)
```

**Lifecycle:**
- Allocated at profiler start
- Fixed size, no growth
- Flushed periodically to JFR file
- Deallocated at profiler stop

### 7. ThreadIdTable Arrays

**What it is:**
- Hash tables tracking active thread IDs for JFR thread metadata
- Two dimensions: CONCURRENCY_LEVEL (16) × 2 (double-buffering)

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
- Allocated at profiler start
- Cleared during buffer rotation
- Fixed size, no growth

### 8. MethodMap (MethodInfo Storage)

**What it is:**
- std::map<jmethodID, MethodInfo> storing metadata for sampled methods
- Only methods that appear in stack traces are stored (lazy allocation)
- Implements age-based cleanup to prevent unbounded growth in continuous profiling

**Memory cost:**
```
Per MethodInfo:
- MethodInfo struct: ~56 bytes
- shared_ptr<SharedLineNumberTable>: 16 bytes
- std::map overhead: ~32 bytes per entry
- Total per method: ~104 bytes

Typical overhead:
- Sampled methods: 1K-10K
- Total: 104 KB - 1 MB
```

**Growth patterns:**
- Grows with sampled method diversity during warmup
- Converges once all hot methods are encountered
- Bounded by unique methods in active code paths
- **With cleanup enabled (default):** Methods unused for 3+ chunks are automatically removed
- **Without cleanup:** Would grow unboundedly in applications with high method churn

**Lifecycle:**
- Allocated during JFR flush when methods are first sampled
- Age counter incremented for unreferenced methods at each chunk boundary
- Methods with age >= 3 chunks are removed during switchChunk()
- Line number tables deallocated via shared_ptr when MethodInfo is destroyed
- Cleanup can be disabled with `--no-method-cleanup` flag (not recommended)

**Cleanup behavior:**
- Triggered during switchChunk() (typically every 10-60 seconds)
- Mark phase: Reset all _referenced flags before serialization
- Reference phase: Mark methods in active stack traces during writeStackTraces()
- Sweep phase: Increment age for unreferenced methods, remove if age >= 3
- Conservative strategy: Methods must be unused for 3 consecutive chunks before removal

### 9. Thread-Local Context Storage (Tracer Integration)

**What it is:**
- thread_local Context structures for APM tracer integration
- Each thread has a cache-line aligned Context containing span IDs and tags
- Pointer stored in ProfiledThread for signal-safe access

**Memory cost:**
```
Per thread Context:
- spanId: 8 bytes
- rootSpanId: 8 bytes
- checksum: 8 bytes
- tags array: 10 × 4 bytes = 40 bytes
- Cache line alignment padding: ~0-8 bytes
- Total per thread: 64 bytes (cache-line aligned)

Typical overhead:
- 100-500 threads: 6.4 KB - 32 KB
- 1000+ threads: 64 KB+
```

**Growth patterns:**
- Grows with thread count (one Context per thread)
- Bounded by application thread count
- Context values stored in _context_value_map Dictionary (see section 5)

**Lifecycle:**
- Allocated lazily on first TLS access per thread
- Persists throughout thread lifetime
- Deallocated when thread terminates

### Summary: Total Memory Overhead

**Typical Java Application (10K-100K classes, stable code paths):**
```
Component                          Memory Overhead
─────────────────────────────────────────────────────
jmethodID preallocation            10-150 MB (JVM internal, NMT Internal category)
Line number tables                 40 KB - 1.6 MB
CallTraceStorage hash tables       11-44 MB
RefCountSlot arrays                512 KB (fixed)
Dictionary instances (4x)          112 KB - 8 MB
Recording buffers                  1.1 MB (fixed)
ThreadIdTable arrays               32 KB (fixed)
MethodMap                          104 KB - 1 MB
Thread-local Contexts              6-64 KB (depends on thread count)
─────────────────────────────────────────────────────
TOTAL (excluding jmethodID):       ~14-56 MB
TOTAL (including jmethodID):       24-206 MB
```

**High Class Churn Application (1M+ classes):**
```
Component                          Memory Overhead
─────────────────────────────────────────────────────
jmethodID preallocation            1+ GB (grows with class count)
Line number tables                 1-10 MB
CallTraceStorage hash tables       50-200 MB (more unique traces)
RefCountSlot arrays                512 KB (fixed)
Dictionary instances (4x)          10-50 MB (more unique strings/contexts)
Recording buffers                  1.1 MB (fixed)
ThreadIdTable arrays               32 KB (fixed)
MethodMap                          1-10 MB
Thread-local Contexts              64-256 KB (high thread count)
─────────────────────────────────────────────────────
TOTAL (excluding jmethodID):       ~63-273 MB
TOTAL (including jmethodID):       1+ GB (dominated by jmethodID)
```

**Key observations:**
- For normal applications: Total overhead is 24-206 MB (acceptable)
- For high class churn: jmethodID dominates memory usage (1+ GB)
- Most non-jmethodID memory converges after warmup
- Only jmethodID and CallTraceStorage can grow unbounded (jmethodID requires class unloading)
- MethodMap now bounded by age-based cleanup (enabled by default)
- Tracer context overhead is negligible (< 256 KB even with 1000+ threads)

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
3. If unfixable: Disable profiler in production
   - Profile only in staging with shorter runs
   - Use alternative observability (JFR events, metrics, tracing)
```

### 2. No Per-Method Memory Control

**Limitation:**
- Cannot selectively preallocate jmethodIDs for specific methods
- ClassPrepare callback must allocate for ALL methods in the class
- Cannot free jmethodIDs while profiling (required for signal-safe operation)

**Why:**
- AGCT can encounter any method in any stack trace unpredictably
- Signal handler cannot call JVM to allocate jmethodIDs on-demand (not signal-safe)
- Selective allocation would cause profiler failures (missing method information)

### 3. Memory Persists Until Class Unload

**Limitation:**
- jmethodID memory cannot be freed while class is loaded
- Even if method is never sampled, its jmethodID exists
- Only freed when ClassLoader is GC'd and class is unloaded

**Impact:**
- Long-lived applications with stable classes: Acceptable (one-time cost)
- Applications with high class churn: Unbounded growth

**No workaround exists:**
- This is fundamental to JVM's jmethodID architecture
- All profiling approaches (AGCT, VM stack walker, etc.) require jmethodIDs
- jmethodIDs are the only reliable way to identify methods

## When to Use the Profiler

### ✅ Appropriate Use Cases

**Stable class count applications:**
- Typical web services, microservices
- Batch processing jobs
- Applications with well-defined class sets
- Expected memory overhead: 24-206 MB total
  - jmethodID: 10-150 MB
  - Profiler data structures: 14-56 MB
  - Tracer context: < 64 KB (negligible)

**Moderate class churn:**
- Applications loading 100K-1M classes total
- Expected memory overhead: 100 MB - 1 GB total
  - jmethodID: Dominant component (70-90% of total)
  - Profiler data structures: 63-273 MB
  - Tracer context: < 256 KB (negligible)
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
- Other malloc: Profiler data structures (CallTraceStorage, Dictionary, etc.)

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

**1. jmethodID preallocation:**
- `ddprof-lib/src/main/cpp/vmEntry.cpp:497-531` - `VM::loadMethodIDs()`
- Called from ClassPrepare callback for every loaded class
- Must call `GetClassMethods()` to trigger JVM internal allocation

**2. Line number table management:**
- `ddprof-lib/src/main/cpp/flightRecorder.cpp:46-63` - `SharedLineNumberTable` destructor
- `ddprof-lib/src/main/cpp/flightRecorder.cpp:167-178` - Lazy allocation in `fillJavaMethodInfo()`
- Properly deallocates via `jvmti->Deallocate()` (fixed in commit 8ffdb30e)

**3. CallTraceStorage:**
- `ddprof-lib/src/main/cpp/callTraceStorage.h` - Triple-buffered hash table management
- `ddprof-lib/src/main/cpp/callTraceHashTable.h` - Hash table structure and operations
- `INITIAL_CAPACITY = 65536` entries, expands at 75% capacity
- `CALL_TRACE_CHUNK = 8 MB` per LinearAllocator chunk

**4. RefCountSlot arrays:**
- `ddprof-lib/src/main/cpp/callTraceStorage.h:43-53` - RefCountSlot structure (64 bytes)
- `MAX_THREADS = 8192` slots, cache-line aligned to eliminate false sharing
- Used for lock-free memory reclamation of hash tables

**5. Dictionary instances:**
- `ddprof-lib/src/main/cpp/dictionary.h` - Multi-level hash table for string deduplication
- `ROWS = 128`, `CELLS = 3` per row
- Four instances: _class_map, _string_label_map, _context_value_map, _packages

**6. Recording buffers:**
- `ddprof-lib/src/main/cpp/buffers.h` - RecordingBuffer implementation
- `RECORDING_BUFFER_SIZE = 65536` bytes + `RECORDING_BUFFER_OVERFLOW = 8192` guard
- `CONCURRENCY_LEVEL = 16` buffers for thread-local event storage

**7. ThreadIdTable:**
- `ddprof-lib/src/main/cpp/threadIdTable.h` - Thread ID tracking for JFR metadata
- `TABLE_SIZE = 256` entries per table
- 16 concurrency levels × 2 tables (double-buffering) = 32 tables total

**8. MethodMap:**
- `ddprof-lib/src/main/cpp/flightRecorder.h:107-110` - MethodMap (std::map<jmethodID, MethodInfo>)
- `ddprof-lib/src/main/cpp/flightRecorder.h:68-105` - MethodInfo structure (_referenced, _age fields)
- `ddprof-lib/src/main/cpp/flightRecorder.cpp:601-640` - cleanupUnreferencedMethods() implementation
- `ddprof-lib/src/main/cpp/flightRecorder.cpp:517-563` - switchChunk() calls cleanup after finishChunk()
- `ddprof-lib/src/main/cpp/flightRecorder.cpp:1196-1242` - writeStackTraces() marks referenced methods
- `ddprof-lib/src/main/cpp/arguments.h:191` - _enable_method_cleanup flag (default: true)
- `ddprof-lib/src/main/cpp/arguments.cpp` - --method-cleanup / --no-method-cleanup parsing
- Stores metadata for sampled methods with lazy allocation
- Age-based cleanup removes methods unused for 3+ consecutive chunks

**9. Thread-local Context storage:**
- `ddprof-lib/src/main/cpp/context.h:32-40` - Context structure (cache-line aligned, 64 bytes)
- `ddprof-lib/src/main/cpp/context.h:57` - thread_local context_tls_v1 declaration
- `DD_TAGS_CAPACITY = 10` tags per context
- Context values stored in _context_value_map Dictionary (profiler.h:122)

### Known Issues Fixed

**GetLineNumberTable leak (Fixed):**
- SharedLineNumberTable destructor was not properly deallocating JVMTI memory
- Impact: 1.2 GB leak for applications sampling 3.8M methods
- Fix: Added null checks and error handling in destructor
- Test: `GetLineNumberTableLeakTest` validates memory plateaus during steady state

**MethodMap unbounded growth (Fixed):**
- Recording._method_map accumulated ALL methods forever in long-running applications
- Impact: 3.8M methods × ~300 bytes = 1.2 GB over days in production
- Root cause: Recording objects live for entire app lifetime, never freed methods
- Fix: Age-based cleanup removes methods unused for 3+ consecutive chunks
- Implementation: Mark-and-sweep during switchChunk(), enabled by default
- Test: `GetLineNumberTableLeakTest.testMethodMapCleanupDuringContinuousProfile()` validates bounded growth
- Feature flag: `--method-cleanup` (default: enabled), `--no-method-cleanup` to disable

**Previous investigation findings:**
- See git history for detailed investigation (commits 8ffdb30e, a9fa649c, 2ab1d263)
- Investigation confirmed jmethodID preallocation is required, not a bug
