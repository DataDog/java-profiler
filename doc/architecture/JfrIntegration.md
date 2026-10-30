<!-- Copyright 2026, Datadog, Inc. -->

# JFR Integration

## Overview

The profiler writes its own JFR files natively; it does not use the JDK's
`jdk.jfr` machinery. The writer lives in `ddprof-lib/src/main/cpp/`:

| File | Contents |
|------|----------|
| `flightRecorder.h` / `flightRecorder.cpp` | `FlightRecorder` (public entry points), `Recording` (one open recording file), `Lookup` (per-dump symbolication), `MethodMap` / `MethodInfo` |
| `flightRecorder.inline.h` | `MethodInfo::getLineNumber()` and `MethodInfo::isHidden()` |
| `jfrMetadata.h` / `jfrMetadata.cpp` | `JfrType` IDs and the `JfrMetadata` type tree |
| `buffers.h` | `Buffer` / `RecordingBuffer`: big-endian and LEB128 encoders, flush thresholds |

Citations below are `file:line` relative to that directory unless a path is
given.

Related documents:

- [CallTraceStorage](CallTraceStorage.md): how stack traces are stored,
  deduplicated and rotated before the writer drains them.
- [StringDictionary](StringDictionary.md): the class, endpoint-label and
  context-value dictionaries that supply constant-pool IDs.
- [EventTypeSystem](../reference/EventTypeSystem.md): the `BCI_*` sample types
  that `FlightRecorder::recordEvent()` dispatches on.

## Object Model

```
Profiler
 └─ FlightRecorder _jfr           _rec_lock (SpinLock), _filename, _args
     └─ Recording* _rec           one open file descriptor (_fd)
         ├─ RecordingBuffer _buf[CONCURRENCY_LEVEL]     event buffers, one per lock stripe
         ├─ ThreadIdTable _thread_ids[CONCURRENCY_LEVEL][2]  threads seen, per stripe
         ├─ Buffer _cpu_monitor_buf
         └─ MethodMap _method_map  method constant pool, kept across chunks
```

- `FlightRecorder::start()` opens `args.file()` and creates the `Recording`, charging
  `sizeof(Recording)` (which embeds all the buffers) to `NM_JFR_BUFFERS`
  (`flightRecorder.cpp:2707-2736`).
- `stop()` nulls `_rec` and deletes the `Recording`, whose destructor calls
  `finishChunk(true)` (`flightRecorder.cpp:2738-2752`, `1005-1008`).
- `dump(filename)` calls `Recording::switchChunk()`; dumping to the recording's
  own file is rejected (`flightRecorder.cpp:2754-2776`).

These three take `_rec_lock` exclusively. Every record path takes it shared
through `OptionalSharedLockGuard`, which gives up after
`DEFAULT_SHARED_SPIN_BUDGET` (256) failed CAS attempts or as soon as it sees the
exclusive lock held (`spinLock.h:59`, `77-90`, `128-143`). `recordEvent()` and
`recordEventDelegated()` count such drops in `SAMPLES_DROPPED_REC_LOCK`
(`flightRecorder.cpp:2908-2910`, `2939-2941`); the other record paths skip the
event silently.

## Event Buffers

### Per-stripe, not per-thread

`Recording` owns `CONCURRENCY_LEVEL` (16) `RecordingBuffer`s
(`flightRecorder.h:84`, `283`). They are indexed by the profiler's lock stripe,
not by thread:

1. `Profiler::getLockIndex(tid)` hashes the thread ID to a stripe.
2. The caller `tryLock()`s that stripe, then up to two others; if all three are
   taken the sample is dropped (`Profiler::recordSample()` and the other
   `record*()` methods).
3. With the stripe lock held it calls `FlightRecorder::recordEvent(lock_index, ...)`,
   which writes into `_buf[lock_index]` (`flightRecorder.cpp:2866-2907`).

So each buffer has one writer at a time, but is shared by many threads, and a
thread can land in another buffer when its home stripe is busy.

`recordEvent()` dispatches on the `BCI_*` event type (CPU, wall, allocation,
liveness, lock, park, native malloc, native socket) to a
`Recording::record*()` serializer, then calls `addThread(lock_index, tid)` so
the thread appears in the chunk's thread pool (`flightRecorder.cpp:2873-2906`).
`recordEventDelegated()` handles CPU and wall samples whose stack is captured by
the JVM instead (HotSpot `RequestStackTrace`): it writes a stack-trace ID of 0
and the correlation ID (`flightRecorder.cpp:2914-2943`, `flightRecorder.h:646-651`).

### Buffer layout and thresholds

| Constant | Value | Source |
|----------|-------|--------|
| `RECORDING_BUFFER_SIZE` | 65536 | `buffers.h:23` |
| `RECORDING_BUFFER_LIMIT` (= `JFR_EVENT_FLUSH_THRESHOLD`) | 65536 − 4096 | `buffers.h:24`, `flightRecorder.h:44` |
| `RECORDING_BUFFER_OVERFLOW` | 8192 bytes of slack past the buffer | `buffers.h:22` |
| `MAX_STRING_LENGTH` | 8191; `putUtf8()` truncates to it | `buffers.h:25`, `171-176` |

The overflow area exists so that a serializer overrunning the limit corrupts
the recording rather than the neighbouring buffer (`buffers.h:15-22`,
`192-214`).

`Recording::flushIfNeeded(buf, limit)` flushes when `offset() >= limit`, with
`limit` defaulting to `JFR_EVENT_FLUSH_THRESHOLD` (`flightRecorder.cpp:1368-1372`).
`Recording::flush()` is a plain `write(2)` of the buffer to `_fd`, followed by
an atomic add to `_bytes_written` and a reset (`flightRecorder.cpp:1360-1366`).
There is no background writer: the thread that fills a buffer past the
threshold, which can be a signal handler, writes it out.

Fixed-size events call `flushIfNeeded()` after writing. Events whose size
depends on input reserve room first by flushing against a reduced limit, for
example `RECORDING_BUFFER_LIMIT - length` for settings
(`flightRecorder.cpp:1584`) or the worst-case chain size for
`datadog.ReferenceChain` (`flightRecorder.cpp:2558-2600`, `flightRecorder.h:48-81`).

### Event encoding

Every event starts with a size prefix and its `JfrType` ID, followed by fields
in the order the metadata declares them. Integers are LEB128
(`putVar32`/`putVar64`, `buffers.h:127-157`); fixed-width values are big-endian.

- **Sample events** (`recordExecutionSample()`, `recordAllocation()`, ...)
  reserve a 1-byte size with `skip(1)` and patch it with
  `writeEventSizePrefix()`, which asserts the event is shorter than
  `MAX_JFR_EVENT_SIZE` (256) (`flightRecorder.cpp:2355-2376`,
  `flightRecorder.h:43`).
- **Variable-size events** (settings, native libraries, OS/JVM info,
  `profiler.Log`, the metadata and constant-pool events) reserve 5 bytes and
  patch them with the fixed-width form `putVar32(offset, v)`, which always
  writes 5 LEB128 bytes (`buffers.h:182-189`, `flightRecorder.cpp:1582-1597`).

Stack-sampled events refer to their stack by the 64-bit trace ID returned by
`CallTraceStorage::put()`, to their thread by the OS TID, and to thread state
and execution mode by small enum IDs. All of these are constant-pool
references, resolved when the chunk is finished (see
[Constant Pools](#constant-pools)). Most sample events end with the tracing
context: span ID, local-root span ID, and one varint per configured context
attribute (`writeCurrentContext()`, `flightRecorder.cpp:2339-2353`). Liveness
events write the context snapshot taken when the allocation was tracked
(`writeContextSnapshot()`, `flightRecorder.cpp:2330-2337`,
`livenessTracker.cpp:2411`).

### Writers outside `recordEvent()`

- `wallClockEpoch()`, `recordTraceRoot()`, `recordQueueTime()`,
  `recordDatadogSetting()`, `recordHeapUsage()` and the reference-chain writers
  use `_buf[lock_index]`; their `Profiler` callers take the stripe lock first
  (`Profiler::writeDatadogProfilerSetting()`, `writeHeapUsage()`, and the
  reference-chain drains in `dump()` and `stop()`).
- `recordLog()` builds the event in an `alloca` buffer and writes it to the
  file at once, without a stripe lock (`flightRecorder.cpp:2945-2966`).
- `cpuMonitorCycle()` writes `jdk.CPULoad` into `_cpu_monitor_buf`, which
  `finishChunk()` flushes; nothing in `ddprof-lib/src/main/cpp` calls it today.

## Chunk Lifecycle

A recording file holds one JFR chunk at a time. `dump()` finishes it, copies it
out, truncates the file, and starts the next chunk.

```
Recording()          header, metadata, settings, OS/CPU/JVM info, system props,
                     native libraries  -> flush(_buf)
   ... events appended to _buf[0..15] by samplers ...
finishChunk()        info events, flush all 16 buffers, write constant pool,
                     back-patch sizes and chunk header
switchChunk(fd)      finishChunk(true, true), copy [0, chunk_end) to fd,
                     truncate, rewrite header/metadata/info events
```

The start-of-chunk events go into `_buf[0]`; OS/CPU/JVM info, system
properties and native libraries can be turned off with `NO_SYSTEM_INFO`,
`NO_SYSTEM_PROPS` and `NO_NATIVE_LIBS` (`flightRecorder.cpp:978-994`,
`1188-1205`). `writeHeader()` writes a 68-byte header whose chunk size is a
1 GiB placeholder ("for JMC to skip incomplete chunk") and whose offsets are 0
(`flightRecorder.cpp:1396-1411`).

### `finishChunk()`

`Recording::finishChunk(end_recording, do_cleanup)` (`flightRecorder.cpp:1016-1167`):

1. **Pin classes.** `GetLoadedClasses()` holds a local JNI reference to every
   loaded class until the end of the function, so those classes cannot be
   unloaded while their `jmethodID`s are symbolicated. Classes unloaded before
   this call get no protection (`flightRecorder.cpp:1020-1038`).
2. **Trailing events.** Flush `_cpu_monitor_buf`; write newly loaded native
   libraries, engine settings, `datadog.DatadogProfilerConfig`, and, when
   `end_recording` is set, `jdk.ActiveRecording`; then counters, native-memory
   statistics and unwind failures (`flightRecorder.cpp:1040-1089`).
3. **Flush all stripes.** `flush(&_buf[i])` for each of the 16 buffers
   (`flightRecorder.cpp:1091-1093`). From here on no event can be appended to
   this chunk: the constant pool comes next, and the header records its offset
   as the end of the event section (`flightRecorder.h:314-319`).
4. **Constant pool.** `writeCpool()` into `_buf[0]`, then flush
   (`flightRecorder.cpp:1095-1098`).
5. **Back-patch** with `pwrite()`: the constant-pool event size, the
   pool-count byte, and 56 header bytes at `_chunk_start + 8`: chunk size,
   constant-pool offset, metadata offset (always 68, the end of the header),
   start time (ns), duration (ns), start ticks and TSC frequency
   (`flightRecorder.cpp:1100-1133`).
6. **Method-map cleanup** if `do_cleanup`, while classes are still pinned
   (`flightRecorder.cpp:1139-1147`; see [Method map ageing](#method-map-ageing)),
   then release the class references (`flightRecorder.cpp:1155-1165`).

### How `Profiler` drives it

`Profiler::dump()` first emits pending
reference-chain events under a stripe lock, refreshes libraries and thread
names, then runs `_jfr.dump()` inside `rotateDictsAndRun()`. `Profiler::stop()`
runs `_jfr.stop()` the same way.

`rotateDictsAndRun()` (`profiler.h:245-268`):

1. Blocks profiling signals on the dumping thread (`SignalBlocker`).
2. Rotates `_class_map`, `_string_label_map` and `_context_value_map`, so each
   one's standby buffer is a stable snapshot for the constant pool.
3. `lockAll()` takes all 16 stripe locks, runs the JFR operation, `unlockAll()`.
   With every stripe held, no sampler can write to a `RecordingBuffer` or to
   `CallTraceStorage` while the chunk is finished.
4. `clearStandby()` on the three dictionaries.

## Metadata

The JFR metadata event describes every type and field that appears in the
chunk. It is generated at run time from an in-memory tree, not loaded from a
resource.

### Building the tree

`JfrMetadata::initialize(contextAttributes)` builds the tree with a small DSL
(`jfrMetadata.cpp:62-459`):

- `type(name, id, label, simple)` creates a `class` element. IDs above
  `T_EVENT` (100) get `superType="jdk.jfr.Event"`; IDs above `T_ANNOTATION`
  (200) get `java.lang.annotation.Annotation` (`jfrMetadata.h:195-211`).
- `field(name, type, label, flags, condition)` creates a `field` element. Flags
  add `constantPool="true"` (`F_CPOOL`), `dimension="1"` (`F_ARRAY`), or unit
  annotations such as `Timestamp(TICKS)` or `DataAmount(BYTES)`. A false
  `condition` returns a `NoField`, which `operator<<` drops, so a field can be
  left out of the schema (`jfrMetadata.h:213-253`, `144-149`, `165-170`).
- `element || contextAttributes` appends one `field` per configured context
  attribute, typed `profiler.types.AttributeValue` and stored in the constant
  pool (`jfrMetadata.h:151-160`). This is the only part of the schema that
  changes between recordings. Event types that carry tracing context
  (`datadog.ExecutionSample`, `datadog.MethodSample`, `datadog.ObjectSample`,
  `datadog.HeapLiveObject`, `datadog.QueueTime`, ...) end with it
  (for example `jfrMetadata.cpp:138-150`).

The tree holds the primitive and constant-pool types (`java.lang.Class`,
`java.lang.Thread`, `jdk.types.StackTrace`/`StackFrame`/`Method`/`Package`/`Symbol`,
...; `jfrMetadata.cpp:71-136`), the `datadog.*` events, the `jdk.*` events the
profiler emits itself (`jdk.CPULoad`, `jdk.ActiveSetting`, `jdk.NativeLibrary`,
...) and `profiler.Log` (`jfrMetadata.cpp:138-429`), then the `jdk.jfr.*`
annotation types and a `region` element (`jfrMetadata.cpp:431-452`).

Type IDs are the `JfrType` enum (`jfrMetadata.h:26-99`). Event serializers write
the same enum value as their first field, so the enum ties each `record*()`
function to its metadata entry.

Element names, attribute keys and attribute values are stored as IDs into a
static string table filled by `getId()` (`jfrMetadata.h:114-122`);
`initialize()` drops the lookup map once the tree is built and keeps the ordered
`_strings` vector (`jfrMetadata.cpp:455-458`).

### Lifecycle

`Profiler::start()` calls `JfrMetadata::reset()` then `initialize()` with
`args._context_attributes`, truncated to `DD_TAGS_CAPACITY`, before
`_jfr.start()`. `reset()` deletes the tree and
re-registers `"root"` as string 0 so the root element's name stays valid
(`jfrMetadata.cpp:43-60`). Both require `Profiler::_state_lock` and must not run
while engines are active (`jfrMetadata.h:276-284`).

### Serialization

`Recording::writeMetadata()` (`flightRecorder.cpp:1374-1394`) writes the
`T_METADATA` event header, the string table, and then the tree via
`writeElement()`. Each element is written as its name ID, its attribute
key/value ID pairs, a child count and the children. Recursion stops at depth 10.
The child count comes from `countSerializableChildren()`, which applies the same
null-child and depth rules as the writer, so the count always matches what is
written (`flightRecorder.cpp:1413-1465`). Skipped children increment
`METADATA_TREE_NULL_CHILD` or `METADATA_TREE_DEPTH_EXCEEDED`.

## Constant Pools

`Recording::writeCpool()` (`flightRecorder.cpp:1756-1805`) writes one
`T_CPOOL` checkpoint event per chunk. Pools that may be empty are skipped, so
the pool count is not known up front. A 1-byte placeholder is written and
`finishChunk()` back-patches it (`flightRecorder.cpp:1768-1773`, `1107-1112`).

| Pool | Written by | Source of entries | Always present |
|------|------------|-------------------|----------------|
| `jdk.types.FrameType` | `writeFrameTypes()` | fixed list of 8 | yes |
| `jdk.types.ThreadState` | `writeThreadStates()` | fixed list of 10 | yes |
| `datadog.types.ExecutionMode` | `writeExecutionModes()` | fixed list of 6 | yes |
| `profiler.types.LogLevel` | `writeLogLevels()` | fixed list | yes |
| `java.lang.Thread` | `writeThreads()` | `_thread_ids` + `ThreadInfo` | yes (contains the recording thread) |
| `jdk.types.StackTrace` | `writeStackTraces()` | `CallTraceStorage` | no |
| `jdk.types.Method` | `writeMethods()` | `MethodMap` rows marked this chunk | no |
| `java.lang.Class` | `writeClasses()` | `Profiler::classMap()->standby()` | no |
| `jdk.types.Package` | `writePackages()` | `Lookup::_packages` | no |
| `jdk.types.Symbol` | `writeConstantPoolSection()` | `Lookup::_symbols` | no |
| `java.lang.String` | `writeConstantPoolSection()` | `stringLabelMap()->standby()` | no |
| `profiler.types.AttributeValue` | `writeConstantPoolSection()` | `contextValueMap()->standby()` | no |

Order matters: the stack-trace pool is written first among the variable pools
because resolving its frames is what fills the method, class, package and
symbol pools (`flightRecorder.cpp:1768-1771`, `1794-1802`).

### Deduplication

Each pool has its own deduplication:

- **Stack traces:** `CallTraceStorage`, at record time; see
  [CallTraceStorage](CallTraceStorage.md).
- **Classes, endpoint strings, context values:** `StringDictionary` instances
  owned by `Profiler`; see [StringDictionary](StringDictionary.md). During the
  dump, `Lookup` adds class names with `lookupDuringDump()`, which probes the
  dump buffer and then the active buffer and inserts into both if the name is
  new. That is why `writeClasses()` sees classes first met while resolving
  frames (`flightRecorder.cpp:1775-1781`, `2032-2058`, `stringDictionary.h:503-509`).
- **Symbols and packages:** `Dictionary` instances owned by the `Lookup`, which
  `writeCpool()` creates per dump (`flightRecorder.h:522-523`,
  `flightRecorder.cpp:1784`). Symbol and package IDs therefore only hold for
  one chunk.
- **Methods:** `MethodMap`, below.
- **Threads:** `addThread()` inserts the TID into
  `_thread_ids[lock_index][active]`, a fixed 256-slot open-addressing table
  that uses only atomics (`flightRecorder.cpp:2702-2705`, `threadIdTable.h`).
  `writeThreads()` flips `_active_index`, collects and clears the previous set,
  and names each thread from `ThreadInfo`, or `[tid=N]` if unknown
  (`flightRecorder.cpp:1873-1923`).

### Method pool

`MethodMap` is a `std::map` from a 64-bit key to `MethodInfo`, and it lives in
the `Recording` across chunks. The top two key bits separate key kinds: a
`jmethodID` (bit 61 set for a raw `Method*` plus a 13-bit tag), a native
function-name address, a packed remote-symbolication frame, or a vtable-receiver
class ID (`flightRecorder.h:149-213`).

`Lookup::resolveMethod()` maps an `ASGCT_CallFrame` to a row
(`flightRecorder.cpp:690-750`):

1. Null or not-walkable `method_id`: the shared `_unknown_method` row, a
   `Lookup` member rather than a map entry so fault recovery can return it
   without allocating (`flightRecorder.h:525-537`).
2. Raw `Method*` frames: `fillRawMethod()`, cached per dump
   (`flightRecorder.cpp:752-780`).
3. Row already marked for this chunk: returned without arming crash protection
   (`flightRecorder.cpp:722-735`).
4. Otherwise `fillMethod()` symbolicates inside a `sigsetjmp`/`siglongjmp`
   window; a SIGSEGV/SIGBUS on stale VM metadata yields `_unknown_method` and
   increments `METHOD_RESOLVE_FAULT_RECOVERED` (`flightRecorder.cpp:782-932`).

`MethodInfo::_mark` means "filled for this chunk". `fillMethod()` sets it only
after a fill completes (`flightRecorder.cpp:891-917`), and `writeMethods()`
clears it after writing the row, so the next chunk resolves the row again
against that chunk's symbol and package IDs (`flightRecorder.cpp:1981-1991`).
`writeMethods()` writes every marked row, plus `_unknown_method` if it was used
(`flightRecorder.cpp:1993-2030`).

Pool IDs (`MethodInfo::_key`) are allocated once per row by
`MethodMap::allocId()`, which reuses IDs freed by erased rows and otherwise
increments a high-water mark. ID 0 means "no entry" (`flightRecorder.h:215-237`).
IDs are not derived from the map size, because erasing rows would then reissue
an ID still held by a live row (`flightRecorder.cpp:909-915`).

### Method map ageing

`writeStackTraces()` clears `_referenced` on every row and sets it on each row a
frame resolves to (`flightRecorder.cpp:1926-1929`, `1949`, `1959`). On
`switchChunk()` (`do_cleanup = true`), `cleanupUnreferencedMethods()` ages each
unreferenced row and erases it, freeing its ID, once it has gone 3 consecutive
chunks unreferenced. Referenced rows reset to age 0. The `mcleanup` option
turns this off; it is on by default (`flightRecorder.cpp:1244-1291`,
`arguments.cpp:387-391`, `arguments.h:322`).

## From `CallTraceStorage` to the Stack-Trace Pool

`writeStackTraces()` (`flightRecorder.cpp:1925-1979`) is the only consumer of
stored traces. It calls `Profiler::processCallTraces()`, which hands the lambda
to `CallTraceStorage::processTraces()`, or an empty set when stack traces are
omitted (`profiler.h:377-385`). Rotation, liveness preservation and the reserved
trace IDs are covered in [CallTraceStorage](CallTraceStorage.md). The callback
runs inside `processTraces()`, so the `CallTrace` pointers stay valid while it
runs.

For each `CallTrace` the writer emits:

```
trace_id                 varint (the 64-bit ID that sample events reference)
truncated                byte   (only when num_frames > 0)
num_frames               varint
per frame:  method key   varint (MethodInfo::_key)
            line number  varint
            bci          varint
            frame type   byte
```

- **Truncated flag:** when the outermost frame (`frames[num_frames - 1]`) is a
  Java frame, the trace is reported truncated unless that frame is an entry
  point (`Thread.run()` or an override in a `Thread` subclass, or
  `main(String[])`); for native outermost frames it is `CallTrace::truncated`
  (`flightRecorder.cpp:1946-1955`, `366-388`).
- **Java frames:** the frame type and BCI are decoded from the packed `bci`
  field (`FrameType::decode()` / `FrameType::bci()`), and the line number comes
  from the method's line-number table (`flightRecorder.cpp:1962-1967`,
  `flightRecorder.inline.h`).
- **Native, remote and vtable-receiver frames:** line number 0, the raw `bci`,
  and the row's own frame type (`flightRecorder.cpp:1968-1972`).

Each frame resolution marks the method row and, through the `Lookup`, adds its
class, package and symbols to the pools written next.

## Java Side

There is no Java-side JFR event type registration. `ddprof-lib/src/main/java`
defines no `jdk.jfr.Event` subclasses; all event types come from the native
metadata tree above. The Java API reaches the writer through JNI:

| Java (`JavaProfiler`) | JNI (`javaApi.cpp`) | JFR event |
|-----------------------|---------------------|-----------|
| `dump(Path)` (`JavaProfiler.java:349`) | `dump0` → `Profiler::dump()` (`javaApi.cpp:269-276`) | finishes and copies the chunk |
| `recordSetting(...)` (`JavaProfiler.java:358-370`) | `recordSettingEvent0` (`javaApi.cpp:311-328`) | `datadog.ProfilerSetting` |
| `recordTraceRoot(...)` (`JavaProfiler.java:198-208`) | `recordTrace0` (`javaApi.cpp:242-266`) | `datadog.Endpoint` |
| `recordQueueTime(...)` (`JavaProfiler.java:386-393`) | `recordQueueEnd0` (`javaApi.cpp:337-375`) | `datadog.QueueTime` |

Values for the context-attribute fields come from Java as dictionary encodings:
`ContextValueCache.registerConstant0()` interns a value in
`Profiler::contextValueMap()` (`javaApi.cpp:1062-1069`), and those encodings are
what `writeCurrentContext()` writes and the `profiler.types.AttributeValue` pool
resolves. The attribute names themselves are the `attributes=` profiler option,
`;`-separated (`arguments.cpp:370-380`), which become the extra metadata fields
described in [Building the tree](#building-the-tree).

How `BCI_*` sample types relate to the upstream `EventType` enum is documented
in [EventTypeSystem](../reference/EventTypeSystem.md).
