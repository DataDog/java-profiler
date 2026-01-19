# Thread-Local Context Architecture

## Overview

The Thread-Local Context (TLS Context) system provides a high-performance, signal-handler-safe mechanism for capturing distributed tracing context (span IDs, root span IDs, and custom tags) during profiling events. This design enables the profiler to correlate performance samples with active traces, providing rich contextual information for distributed system debugging.

The system uses a shared-memory architecture where Java code writes tracing context into thread-local direct ByteBuffers, and native signal handlers (SIGPROF) safely read this context without locks or blocking operations. Memory ordering guarantees protect against torn reads and ensure consistency even when signal handlers interrupt context writes mid-sequence.

## Core Design Principles

1. **Zero-Copy Shared Memory**: Java writes to direct ByteBuffers mapped to native thread-local storage
2. **Signal Handler Safety**: All reads from signal handlers use lock-free atomic operations
3. **Memory Ordering Guarantees**: Explicit release/acquire semantics prevent torn reads
4. **Checksum Validation**: Knuth multiplicative hash detects inconsistent reads
5. **Platform Independence**: Correct behavior on both strong (x86) and weak (ARM) memory models
6. **Low Overhead**: Typical write ~10-20ns, read ~5-10ns (no syscalls, no locks)

## Architecture Overview

### High-Level Data Flow

```
┌──────────────────────────────────────────────────────────────────┐
│                      Application Thread                          │
├──────────────────────────────────────────────────────────────────┤
│                                                                  │
│  Tracer Updates Context                                          │
│         ↓                                                        │
│  ThreadContext.put(spanId, rootSpanId)                           │
│         ↓                                                        │
│  BufferWriter (ordered writes with memory barriers)              │
│         ↓                                                        │
│  ┌────────────────────────────────────────────┐                  │
│  │  Direct ByteBuffer (thread_local)          │                  │
│  │  ┌──────────────┬──────────────┬─────────┐ │                  │
│  │  │ spanId (u64) │rootSpanId(64)│checksum │ │                  │
│  │  │              │              │  (u64)  │ │                  │
│  │  └──────────────┴──────────────┴─────────┘ │                  │
│  └────────────────────────────────────────────┘                  │
│         ↕ (mapped to same memory)                                │
│  ┌────────────────────────────────────────────┐                  │
│  │  Native Context struct (thread_local)      │                  │
│  │  volatile u64 spanId;                      │                  │
│  │  volatile u64 rootSpanId;                  │                  │
│  │  volatile u64 checksum;                    │                  │
│  │  Tag tags[10];                             │                  │
│  └────────────────────────────────────────────┘                  │
│         ↑                                                        │
│  Signal Handler Reads (SIGPROF)                                  │
│         ↓                                                        │
│  Recording::writeContext()                                       │
│         ↓                                                        │
│  JFR Event with Trace Context                                    │
└──────────────────────────────────────────────────────────────────┘
```

### Component Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                        Java Layer                               │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  ThreadContext (per thread)                                     │
│    │                                                            │
│    ├─ ByteBuffer buffer (direct, maps to native Context)        │
│    ├─ BufferWriter (version-agnostic ordered writes)            │
│    └─ put(spanId, rootSpanId) / putCustom(offset, value)        │
│         │                                                       │
│         └─ Java 17+: JNI call → setContext0()                   │
│         └─ Java 8-16: Pure Java → putContextJava()              │
│                                                                 │
│  BufferWriter (memory ordering abstraction)                     │
│    │                                                            │
│    ├─ BufferWriter8 (Java 8: Unsafe)                            │
│    │    └─ putOrderedLong() / putLongVolatile()                 │
│    │                                                            │
│    └─ BufferWriter9 (Java 9+: VarHandle)                        │
│         └─ setRelease() / setVolatile()                         │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────┐
│                       Native Layer                              │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  Context struct (thread_local, cache-aligned)                   │
│    ├─ volatile u64 spanId                                       │
│    ├─ volatile u64 rootSpanId                                   │
│    ├─ volatile u64 checksum                                     │
│    └─ Tag tags[10]                                              │
│                                                                 │
│  Contexts class (static access)                                 │
│    ├─ initializeContextTls() → creates and maps Context         │
│    ├─ get() → signal-safe TLS access via ProfiledThread         │
│    └─ checksum(spanId, rootSpanId) → validation                 │
│                                                                 │
│  Recording::writeContext() (signal handler)                     │
│    └─ Reads context with checksum validation                    │
└─────────────────────────────────────────────────────────────────┘
```

## Memory Layout

### Context Structure

```
Offset  Size   Field           Description
──────────────────────────────────────────────────────────────────
0x00    8      spanId          Current trace span ID
0x08    8      rootSpanId      Root span ID for trace
0x10    8      checksum        Knuth hash of spanId ^ rootSpanId
0x18    4      tags[0]         Custom tag slot 0
0x1C    4      tags[1]         Custom tag slot 1
...
0x3C    4      tags[9]         Custom tag slot 9
──────────────────────────────────────────────────────────────────
Total: 64 bytes (cache-aligned)
```

The structure is cache-aligned (64 bytes on most platforms) to:
- Avoid false sharing between threads
- Maximize cache locality for hot fields (spanId, rootSpanId, checksum)
- Ensure atomic visibility on architectures with split cache lines

## The Write Protocol

### Signal Handler Race Condition

The fundamental challenge: **signal handlers interrupt the writing thread mid-sequence**

```
Thread Timeline:
─────────────────────────────────────────────────────────────────
Time 0:  write(checksum = 0)         ← Mark in-progress
Time 1:  write(spanId = 123)
Time 2:  write(rootSpanId = 456)
         ⚡ SIGNAL (SIGPROF) ARRIVES  ← Signal handler interrupts!
                                      ← Handler MUST see consistent state
Time 3:  write(checksum = valid)     ← Never executed yet
─────────────────────────────────────────────────────────────────
```

### Write Sequence with Memory Ordering

```java
public long putContextJava(long spanId, long rootSpanId) {
    long checksum = computeContextChecksum(spanId, rootSpanId);

    // Step 1: Mark in-progress (RELEASE semantics)
    //   - Prevents reordering with prior operations
    //   - Visible before subsequent data writes
    BUFFER_WRITER.writeOrderedLong(buffer, CHECKSUM_OFFSET, 0);

    // Step 2: Write data fields (RELEASE semantics)
    //   - Prevents reordering with prior writes
    //   - Must complete before final checksum
    BUFFER_WRITER.writeOrderedLong(buffer, SPAN_ID_OFFSET, spanId);
    BUFFER_WRITER.writeOrderedLong(buffer, ROOT_SPAN_ID_OFFSET, rootSpanId);

    // Step 3: Signal completion (VOLATILE semantics)
    //   - Full memory barrier
    //   - Prevents reordering with BOTH prior and subsequent operations
    //   - Ensures all prior writes are visible before this write
    BUFFER_WRITER.writeVolatileLong(buffer, CHECKSUM_OFFSET, checksum);

    return checksum;
}
```

### Read Sequence in Signal Handler

```cpp
void Recording::writeContext(Buffer *buf, Context &context) {
    // Step 1: Read checksum FIRST
    u64 stored = context.checksum;

    // Step 2: Check if write is in-progress or complete
    if (stored == 0) {
        // Write in-progress or no context set
        // Safe: emit zeros
        buf->putVar64(0);  // spanId
        buf->putVar64(0);  // rootSpanId
        return;
    }

    // Step 3: Read data fields
    // Memory ordering guarantees these are valid if checksum != 0
    u64 spanId = context.spanId;
    u64 rootSpanId = context.rootSpanId;

    // Step 4: Validate checksum
    u64 computed = Contexts::checksum(spanId, rootSpanId);
    if (stored != computed) {
        // Torn read detected! (race condition caught)
        TEST_LOG("Invalid context checksum: ctx=%p, tid=%d", &context, OS::threadId());
        spanId = 0;
        rootSpanId = 0;
    }

    // Step 5: Emit validated context
    buf->putVar64(spanId);
    buf->putVar64(rootSpanId);
}
```

## Memory Ordering Requirements

### Why Same-Thread Needs Memory Barriers

Even though the writer and reader execute on the **same thread**, memory barriers are essential because:

#### 1. Compiler Reordering
Without barriers, the JIT compiler can reorder:
```java
// Source code order:
write(checksum=0);
write(spanId=123);
write(checksum=valid);

// Compiler could reorder to:
write(spanId=123);
write(checksum=valid);  ← Checksum set BEFORE in-progress marker!
write(checksum=0);
```

#### 2. CPU Store Buffer Reordering (Weak Memory Models)
On ARM (weakly-ordered architecture):
- Stores may be buffered and reordered by the CPU
- Signal handler executes in different execution context (interrupt frame)
- Store buffer contents may not be visible to interrupt context without barriers

On x86 (strongly-ordered architecture):
- Stores naturally ordered (FIFO store buffer)
- BUT compiler can still reorder without barriers
- Release/acquire semantics provide compiler barriers

#### 3. Signal Handler Execution Context
Signal handlers are special:
- Interrupt the current execution asynchronously
- Execute in a different stack frame
- May have different cache/store buffer visibility
- Require explicit memory ordering guarantees

### Memory Ordering Semantics

#### Release Semantics (Ordered Writes)
Used for: `writeOrderedLong()`, `writeOrderedInt()`

**Guarantees:**
- All prior memory operations complete before this write
- This write is visible before subsequent operations begin
- Prevents reordering with prior operations
- One-way barrier: prior → this (but subsequent can move up)

**Implementation:**
- Java 8: `Unsafe.putOrderedLong()` → Store-Release
- Java 9+: `VarHandle.setRelease()` → Store-Release
- ARM: Translates to `STR` + `DMB ISH` (Data Memory Barrier, Inner Shareable)
- x86: Translates to `MOV` + compiler barrier (x86 stores are naturally ordered)

#### Volatile Semantics (Full Barrier)
Used for: `writeVolatileLong()`, `writeVolatileInt()`

**Guarantees:**
- All prior memory operations complete before this write
- This write completes before any subsequent operations begin
- Prevents reordering with BOTH prior and subsequent operations
- Two-way barrier: prior → this → subsequent

**Implementation:**
- Java 8: `Unsafe.putLongVolatile()` → Store-Release + Full Fence
- Java 9+: `VarHandle.setVolatile()` → Sequential Consistency
- ARM: Translates to `DMB ISH; STR; DMB ISH` (barriers on both sides)
- x86: Translates to `LOCK MOV` or `MFENCE` (locked operation or memory fence)

### Platform-Specific Behavior

#### x86/x64 (Strong Memory Model)
**Hardware Guarantees:**
- Store-Store ordering: Stores execute in program order (FIFO store buffer)
- Store-Load reordering: Stores can be reordered after subsequent loads
- Atomic visibility: Naturally aligned 64-bit stores are atomic

**What We Still Need:**
- Compiler barriers to prevent JIT reordering
- MFENCE for volatile writes to prevent Store-Load reordering
- Memory model is strong, but not sequentially consistent

**Performance:**
- Release writes: ~1-2 cycles (MOV + compiler barrier)
- Volatile writes: ~30-100 cycles (MFENCE is expensive)

#### ARM/AArch64 (Weak Memory Model)
**Hardware Guarantees:**
- Almost none! ARM can reorder stores arbitrarily
- No guarantee that other cores see stores in program order
- Even same-thread observers (like signal handlers) may see reordering

**What We Need:**
- DMB ISH (Data Memory Barrier, Inner Shareable) for release semantics
- Full barriers (DMB ISH before and after) for volatile semantics
- Explicit memory ordering for everything

**Performance:**
- Release writes: ~10-20 cycles (STR + DMB ISH)
- Volatile writes: ~40-80 cycles (DMB + STR + DMB)
- DMB is relatively cheaper on modern ARM than MFENCE on x86

### C++ Volatile Keyword (Insufficient)

The C++ `Context` struct uses `volatile`:
```cpp
volatile u64 spanId;
volatile u64 rootSpanId;
volatile u64 checksum;
```

**What C++ volatile provides:**
- Prevents compiler from optimizing away reads/writes
- Forces memory access (no register caching)
- Prevents reordering of accesses to the SAME volatile variable

**What C++ volatile DOES NOT provide:**
- No CPU memory barriers
- No ordering guarantees between DIFFERENT volatile variables
- No atomic guarantees (reads/writes can tear on 32-bit platforms)
- **Signal handler sees checksum != 0 does NOT guarantee spanId/rootSpanId visible!**

**Result:** Java-side memory barriers are ESSENTIAL for correctness.

## Checksum Algorithm

### Knuth Multiplicative Hash

The checksum uses Knuth's multiplicative hash with XOR for collision resistance:

```java
public static long computeContextChecksum(long spanId, long rootSpanId) {
    // Knuth's golden ratio constant for 64-bit values
    // φ = (1 + √5) / 2, constant = 2^64 / φ
    final long KNUTH_CONSTANT = 0x9E3779B97F4A7C15L;

    // Hash spanId
    long hashSpanId = spanId * KNUTH_CONSTANT;

    // Swap rootSpanId halves to maximize avalanche effect
    long swappedRootSpanId = ((rootSpanId & 0xFFFFFFFFL) << 32)
                            | (rootSpanId >>> 32);
    long hashRootSpanId = swappedRootSpanId * KNUTH_CONSTANT;

    // XOR for combining (prevents simple bit correlation)
    long computed = hashSpanId ^ hashRootSpanId;

    // Ensure checksum is never 0 (0 is reserved for "in-progress")
    return computed == 0 ? 0xffffffffffffffffL : computed;
}
```

**Design Rationale:**

1. **Multiplicative Hash**: Provides excellent avalanche effect (changing one bit changes ~50% of output bits)
2. **Half-Swap**: Maximizes bit mixing between high and low halves of rootSpanId
3. **XOR Combination**: Symmetric, fast, prevents simple bit-level correlations
4. **Zero Avoidance**: 0 is reserved for "write in-progress" marker

**Collision Probability:**
- For 64-bit hash output: ~2^-64 per pair (effectively zero)
- Torn reads: Detected with high probability (requires matching hash of corrupted data)

## Performance Characteristics

### Write Path Performance

**Pure Java Path** (Java 8-16):
```
writeOrderedLong(checksum=0)      ~5-10ns   (release barrier)
writeOrderedLong(spanId)          ~5-10ns   (release barrier)
writeOrderedLong(rootSpanId)      ~5-10ns   (release barrier)
writeVolatileLong(checksum)       ~20-50ns  (full barrier)
────────────────────────────────────────────
Total: ~35-80ns per context update
```

**JNI Path** (Java 17+):
```
JNI transition overhead          ~5-10ns   (modern JVMs, @CriticalNative-like)
Direct struct writes             ~2-5ns    (compiler optimizes to MOV)
────────────────────────────────────────────
Total: ~10-20ns per context update
```

**Comparison:** JNI path is 2-4x faster on Java 17+ due to:
- Elimination of BufferWriter indirection
- Direct native code generation (no JIT warm-up needed)
- Optimized JNI calling conventions in modern JVMs

### Read Path Performance (Signal Handler)

```
ProfiledThread::getContextTlsPtr()  ~2ns    (cached pointer read)
context.checksum read               ~2-5ns  (volatile read)
context.spanId read                 ~2-5ns  (volatile read, likely cached)
context.rootSpanId read             ~2-5ns  (volatile read, likely cached)
Checksum computation                ~3-8ns  (2 multiply, 1 XOR, 1 shift)
────────────────────────────────────────────
Total: ~11-25ns per context read
```

**Signal Handler Budget:**
- Target: <500ns per sample (including stack walking)
- Context read: ~15ns (~3% of budget)
- Acceptable overhead for rich trace context

## Signal Handler Safety

### TLS Access Safety

**Problem:** Direct TLS access (`thread_local context_tls_v1`) can deadlock:
```cpp
// DANGEROUS - DO NOT USE IN SIGNAL HANDLER
Context& ctx = context_tls_v1;  // May trigger TLS lazy initialization
                                // Lazy init calls malloc()
                                // malloc() may hold lock
                                // → DEADLOCK
```

**Solution:** Pre-initialized pointer via `ProfiledThread`:
```cpp
// SAFE - Pre-initialized pointer, no TLS access
Context& Contexts::get() {
    ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
    if (thrd == nullptr || !thrd->isContextTlsInitialized()) {
        return DD_EMPTY_CONTEXT;  // Safe fallback
    }
    // Return via cached pointer - no TLS lazy initialization
    return *thrd->getContextTlsPtr();
}
```

### Initialization Protocol

```cpp
// During thread initialization (NOT in signal handler):
Context& Contexts::initializeContextTls() {
    // First access to TLS - may trigger lazy initialization
    Context& ctx = context_tls_v1;

    // Store pointer in ProfiledThread for signal-safe access
    ProfiledThread::current()->markContextTlsInitialized(&ctx);

    return ctx;
}
```

Java side:
```java
// Called during JavaProfiler initialization for each thread
ByteBuffer buffer = JavaProfiler.initializeContextTls0();
ThreadContext context = new ThreadContext(buffer);
```

### Lock-Free Guarantees

The read path is completely lock-free:
1. **No mutex locks**: Signal handler never acquires locks
2. **No atomic RMW operations**: Only loads (no compare-and-swap)
3. **No memory allocation**: All data structures pre-allocated
4. **No system calls**: Pure memory reads with checksum validation
5. **Bounded time**: Worst case ~25ns (no unbounded loops)

## Version-Specific Implementations

### BufferWriter Architecture

```
┌────────────────────────────────────────────────────────────┐
│              BufferWriter (public API)                     │
├────────────────────────────────────────────────────────────┤
│  writeOrderedLong(buffer, offset, value)                   │
│  writeVolatileLong(buffer, offset, value)                  │
│  writeOrderedInt(buffer, offset, value)                    │
│  writeVolatileInt(buffer, offset, value)                   │
└────────────────────────────────────────────────────────────┘
                          │
          ┌───────────────┴───────────────┐
          │                               │
┌─────────▼──────────┐      ┌─────────────▼─────────┐
│  BufferWriter8     │      │   BufferWriter9       │
│  (Java 8)          │      │   (Java 9+)           │
├────────────────────┤      ├───────────────────────┤
│ Unsafe-based       │      │ VarHandle-based       │
│                    │      │                       │
│ putOrderedLong()   │      │ setRelease()          │
│ putLongVolatile()  │      │ setVolatile()         │
│ putOrderedInt()    │      │ setRelease()          │
│ putIntVolatile()   │      │ setVolatile()         │
└────────────────────┘      └───────────────────────┘
```

### Java 8 Implementation (Unsafe)

```java
public final class BufferWriter8 implements BufferWriter.Impl {
    private static final Unsafe UNSAFE;

    @Override
    public long writeOrderedLong(ByteBuffer buffer, int offset, long value) {
        // putOrderedLong: Store-Release semantics
        //   - ARM: STR + DMB ISH
        //   - x86: MOV + compiler barrier
        UNSAFE.putOrderedLong(null,
            ((DirectBuffer) buffer).address() + offset, value);
        return UNSAFE.getLong(((DirectBuffer) buffer).address() + offset);
    }

    @Override
    public long writeAndReleaseLong(ByteBuffer buffer, int offset, long value) {
        // putLongVolatile: Full volatile semantics
        //   - ARM: DMB ISH; STR; DMB ISH
        //   - x86: LOCK MOV or MFENCE
        UNSAFE.putLongVolatile(null,
            ((DirectBuffer) buffer).address() + offset, value);
        return UNSAFE.getLong(((DirectBuffer) buffer).address() + offset);
    }

    @Override
    public void writeInt(ByteBuffer buffer, int offset, int value) {
        UNSAFE.putOrderedInt(null,
            ((DirectBuffer) buffer).address() + offset, value);
    }

    @Override
    public void writeAndReleaseInt(ByteBuffer buffer, int offset, int value) {
        UNSAFE.putIntVolatile(null,
            ((DirectBuffer) buffer).address() + offset, value);
    }

    @Override
    public void fullFence() {
        UNSAFE.fullFence();  // Equivalent to __atomic_thread_fence(__ATOMIC_SEQ_CST)
    }
}
```

### Java 9+ Implementation (VarHandle)

```java
public final class BufferWriter9 implements BufferWriter.Impl {
    private static final VarHandle LONG_VIEW_VH;
    private static final VarHandle INT_VIEW_VH;

    static {
        LONG_VIEW_VH = MethodHandles.byteBufferViewVarHandle(
            long[].class, ByteOrder.nativeOrder());
        INT_VIEW_VH = MethodHandles.byteBufferViewVarHandle(
            int[].class, ByteOrder.nativeOrder());
    }

    @Override
    public long writeOrderedLong(ByteBuffer buffer, int offset, long value) {
        // setRelease: Store-Release semantics (matches putOrderedLong)
        //   - Prevents prior stores from reordering after this
        //   - One-way barrier: prior → this
        LONG_VIEW_VH.setRelease(buffer, offset, value);
        return (long) LONG_VIEW_VH.get(buffer, offset);
    }

    @Override
    public long writeAndReleaseLong(ByteBuffer buffer, int offset, long value) {
        // setVolatile: Full volatile semantics (matches putLongVolatile)
        //   - Sequential consistency
        //   - Two-way barrier: prior → this → subsequent
        LONG_VIEW_VH.setVolatile(buffer, offset, value);
        return (long) LONG_VIEW_VH.get(buffer, offset);
    }

    @Override
    public void writeInt(ByteBuffer buffer, int offset, int value) {
        INT_VIEW_VH.setRelease(buffer, offset, value);
    }

    @Override
    public void writeAndReleaseInt(ByteBuffer buffer, int offset, int value) {
        INT_VIEW_VH.setVolatile(buffer, offset, value);
    }

    @Override
    public void fullFence() {
        VarHandle.fullFence();
    }
}
```

## Testing and Validation

### Unit Tests (C++)

Located in `ddprof-lib/src/test/cpp/context_sanity_ut.cpp`:

**Test: Basic Read/Write**
```cpp
TEST(ContextSanityTest, BasicReadWrite) {
    Context ctx;
    ctx.spanId = 100;
    ctx.rootSpanId = 200;
    ctx.checksum = 300;

    EXPECT_EQ(ctx.spanId, 100ULL);
    EXPECT_EQ(ctx.rootSpanId, 200ULL);
    EXPECT_EQ(ctx.checksum, 300ULL);
}
```

**Test: Sequential Write/Read Cycles**
```cpp
TEST(ContextSanityTest, SequentialWriteReadCycles) {
    Context ctx;
    // Multiple write/read cycles with memory fences
    __atomic_thread_fence(__ATOMIC_ACQUIRE);
    // Validates memory ordering across cycles
}
```

**Test: TLS Mechanism**
```cpp
TEST(ContextSanityTest, TlsMechanism) {
    Context& ctx = Contexts::initializeContextTls();
    // Write via one reference
    ctx.spanId = 123;
    // Read via TLS getter
    Context& readCtx = Contexts::get();
    EXPECT_EQ(readCtx.spanId, 123ULL);
}
```

### Integration Tests (Java)

Located in `ddprof-test/src/test/java/`:

**Test: Context Wall Clock**
- Tests context propagation through profiling samples
- Validates checksum computation
- Verifies JFR event correlation

**Test: Multi-threaded Updates**
- Concurrent context updates from multiple threads
- Stress testing for race conditions
- Validates thread-local isolation

### Stress Testing

**Approach:**
1. Generate high-frequency context updates (>1M/sec per thread)
2. Trigger profiling signals at high rate (>10K/sec)
3. Validate all JFR events have valid checksums
4. Run on both x86 and ARM platforms
5. Test with TSan (ThreadSanitizer) build configuration

**Success Criteria:**
- Zero checksum validation failures
- No torn reads detected
- No TSan warnings
- Consistent behavior across platforms

## Future Enhancements

### Potential Optimizations

1. **Lockless Custom Tags**: Currently custom tags use ordered writes without checksum protection
2. **Batched Updates**: Batch multiple context updates with single final barrier
3. **Adaptive Checksums**: Skip checksum when signal frequency is low
4. **NUMA-Aware Allocation**: Allocate context on local NUMA node for better cache locality

### Monitoring and Observability

1. **Checksum Failure Metrics**: Track rate of torn reads (should be ~0)
2. **Write Latency Histograms**: P50/P99/P999 write latencies
3. **Read Latency in Signal Handler**: Impact on total sample collection time
4. **Platform-Specific Behavior**: Compare x86 vs ARM performance characteristics
