# glibc Malloc Arena Warning

## Scope

The profiler checks once per JFR chunk whether glibc holds a large amount of
free native memory across many per-thread malloc arenas. It writes two JFR
events:

- `datadog.MallocArenaStats`: one event per chunk.
- `datadog.MallocArenaWarning`: written when the warning state changes (see
  [Emission](#emission)).

The detector is always on. It does not need `nativemem`. It is compiled only
for Linux with glibc (`__linux__` and `__GLIBC__`). On other platforms and on
musl, `Recording::writeMallocArenaEvents()` is empty and no arena event is
written.

The detector runs on the JFR flush path, in `Recording::finishChunk()`, after
`writeNativeMem()`. It never runs in a signal handler.

## Failure mechanism

glibc limits the number of malloc arenas to 8 times the number of online CPUs
(2 times on 32-bit targets) unless `MALLOC_ARENA_MAX` or the
`glibc.malloc.arena_max` tunable sets another limit. The limit uses the CPU
count of the host. It ignores a cgroup CPU quota. A container with a quota of
2 CPUs on a 64-CPU host can therefore have up to 512 arenas.

An arena keeps freed memory. glibc releases the memory of a non-main arena
only from the top of a heap and only above the trim threshold. Interior free
chunks stay committed. Many threads that allocate and free therefore leave a
large amount of free but committed memory spread over many arenas.
`MALLOC_ARENA_MAX` set to a value near 8 times the quota CPUs limits this.

On aarch64 with glibc 2.43, every non-main arena is at least 2 MiB in size
when the kernel THP mode is `madvise`. The arena count alone can then account
for a significant amount of resident memory.

## Components

| Unit | Files | Role |
|---|---|---|
| Walker | `mallocArenaWalker.{h,cpp}` | Reads the glibc arena list without a lock |
| Inputs | `mallocArenaInputs.{h,cpp}` | Captures process-static inputs once per `Recording` |
| Rule | `mallocArenaRule.{h,cpp}` | Evaluates the condition and keeps the warning state. No I/O |
| Events | `mallocArenaEvents.{h,cpp}`, `jfrMetadata.{h,cpp}` | Event types and serializers |
| Glue | `Recording::writeMallocArenaEvents()` in `flightRecorder.cpp` | Gates, calls, and emission |

## Arena walk

`MallocArenaWalker::walk()` follows the circular `malloc_state->next` list of
glibc. glibc does not export the `malloc_state` layout, so the walker reads the
fields at known offsets.

### Seed

1. The calling thread calls `malloc(64)` and reads the size field of the
   chunk header.
2. A seed is accepted only when the chunk is not mmapped and has the
   non-main-arena bit set. A chunk in `main_arena` gives no seed.
3. The heap start is the chunk address masked to a 64 MiB boundary
   (`HEAP_MAX_SIZE`). The first word of the heap is `heap_info.ar_ptr`. The
   distance from the heap start to `ar_ptr` must be 32 or 48 bytes
   (`sizeof(heap_info)` before and since glibc 2.35).
4. The validated arena address is cached for the process lifetime. A later
   walk does not allocate again. When no seed is available, the walk returns
   `no-seed` and the next chunk tries again from the thread that flushes it.

The seed allocation is made on the flushing thread. If this thread has no
non-main arena, glibc can create one for it. The arena count can therefore
include one arena that the detector caused.

### Structural check

An arena `a` is a non-main arena when `a` is at `heap_info` size from its
64 MiB-aligned heap start and the first word of that heap equals `a`.
`main_arena` is a static object and fails this check. A complete walk must
return to the seed and must meet exactly one arena that fails the check.

All reads of arena memory use `SafeAccess::safeCopy`. A fault becomes the
status `fault`. The walk needs the SIGSEGV/SIGBUS handler that
`Profiler::setupSignalHandlers()` installs on HotSpot and OpenJ9.

For each arena, `system_mem` must be non-zero and a multiple of 4096, and
`max_system_mem` must not be smaller than `system_mem`.

### Layout calibration

| Index | Name | `next` | `attached_threads` | `system_mem` | `max_system_mem` |
|---|---|---|---|---|---|
| 0 | `2.17-2.22` | 2152 | none | 2168 | 2176 |
| 1 | `2.23-2.26` | 2152 | 2168 | 2176 | 2184 |
| 2 | `2.27-2.42` | 2160 | 2176 | 2184 | 2192 |
| 3 | `2.43+` | 2072 | 2088 | 2096 | 2104 |

Offsets are in bytes, for 64-bit targets. Vendors backport changes, so the
glibc version only orders the candidates: the candidate that matches the
`gnu_get_libc_version()` release is tried first. The first layout that passes
a full walk is cached and used for all later walks. If no layout passes, the
result is the failure status of the first candidate tried. The `layout` field
of the warning is empty in this case.

After calibration, a failed walk does not select another layout.
`threadPrivateArenas` counts arenas with `attached_threads == 1`. It is -1
for layout `2.17-2.22`, which has no such field.

### Walk statuses

`walkStatus` has one of these values:

| Value | Meaning |
|---|---|
| `ok` | The walk is trustworthy |
| `unsupported-platform` | Not Linux with glibc (walker stub) |
| `unsupported-jvm` | The JVM is neither HotSpot nor OpenJ9 (for example Zing) |
| `replaced-allocator` | A replacement allocator is active, or an ASan/TSan build |
| `hugetlb-tunable` | `glibc.malloc.hugetlb` is 2 or more in `GLIBC_TUNABLES`, so the heap size is not 64 MiB |
| `no-seed` | No non-main-arena chunk was available |
| `no-layout` | No candidate layout was tried |
| `fault` | A read of arena memory faulted |
| `implausible` | `system_mem` or `max_system_mem` failed the checks |
| `bad-next` | A `next` pointer was unreadable or null |
| `second-main` | More than one arena failed the structural check |
| `no-main` | The walk returned to the seed without meeting `main_arena` |
| `too-many` | The list is longer than the cap |

The cap is the arena limit clamped to 64..65536, plus 64.

When the status is not `ok`, the detector fails closed: it does not raise a
warning and it keeps the current warning state. `Recording::gateStatus()`
decides `unsupported-jvm`, `replaced-allocator` and `hugetlb-tunable` before
the walk, in this order. The walker itself never returns these three values.

## Inputs

`MallocArenaInputs::capture()` runs in the `Recording` constructor, so every
`start` captures the values again.

| Input | Source |
|---|---|
| CPU quota (`cpuQuotaMilli`) | `OS::getCgroupCpuMillicores()`: cgroup v2 `cpu.max`, else cgroup v1 `cpu.cfs_quota_us`. `-1` when there is no quota |
| Online CPUs | `OS::getCpuCount()`, at least 1 |
| Arena limit and its source | `glibc.malloc.arena_max` in `GLIBC_TUNABLES` (`tunable`), else `MALLOC_ARENA_MAX` (`env`), else 8 x online CPUs (`default`). A value that is not a positive integer is ignored |
| Memory limit and its source | `OS::getContainerMemoryLimit()` (`cgroup`), else `OS::getRamSize()` (`physical`), else -1 (`unknown`) |
| glibc version | `gnu_get_libc_version()` |
| hugetlb | `glibc.malloc.hugetlb` in `GLIBC_TUNABLES` |
| Max heap | `JVMSupport::maxHeapBytes()` |

`JVMSupport::maxHeapBytes()` is `Runtime.getRuntime().maxMemory()`. It is
resolved through JNI in `JVMSupport::initExecution()`, which runs at profiler
start. It is -1 when it could not be resolved. Each later start tries again.

## Rule

`evaluateMallocArenaRule()` is a pure function. The warning is active when
the walk is `ok` and both conditions are true.

1. **Arena count.** The CPU quota exists, and `arenaCount` is greater than
   `recommendedArenaMax`. `recommendedArenaMax` is 8 x the quota rounded up to
   whole CPUs (a quota of 1500 millicores gives 16). Without a quota the
   condition is false, so no warning is raised.
2. **Held memory.** The measure is greater than `thresholdPercent` percent of
   `nativeHeadroom`. The comparison is strict and uses 128-bit arithmetic.

`nativeHeadroom` is derived from the memory limit:

| Condition | `nativeHeadroom` | `headroomSource` | `heapExceedsLimit` |
|---|---|---|---|
| Limit known, max heap known and below the limit | limit minus max heap | `limit-minus-heap` | false |
| Limit known, max heap unknown (`<= 0`) or `Long.MAX_VALUE` | limit | `limit-only` | false |
| Limit known, max heap at or above the limit | limit | `limit-only` | true |
| Limit unknown | 0 | `limit-only` | false |

With an unknown limit, condition 2 is false.

### Measure

`conditionMeasure` names the compared value:

- `free-held`: `mallinfo2().fordblks`, the free bytes that glibc retains in
  all arenas.
- `committed`: the sum of `system_mem` of the non-main arenas from the walk.

`free-held` needs `mallinfo2()`. The code calls it only when
`DD_HAVE_MALLINFO2` is defined, that is, when the glibc headers at compile
time are 2.33 or newer. Release builds use older headers, so they do not
contain the call. In release builds `conditionMeasure` is `committed` and
`freeHeldBytes` is -1 until `mallinfo2` is resolved at runtime. `committed`
over-states the held memory, because it includes memory that is in use.
`updateMallocArenaStats()` is the single place that calls `mallinfo2()`, once
per chunk, so a runtime lookup replaces that one function.

### Threshold

`arenawarn=<percent>` sets the threshold. The default is 25. See
[Argument](#argument).

## Emission

The `Recording` holds one `MallocArenaWarningState`. It starts idle.
`step()` returns one of these transitions:

| Transition | When |
|---|---|
| `raised` | Idle and the rule is active |
| `worsened` | Raised and the measure is at least 125% of the measure at the last `raised` or `worsened` event |
| `cleared` | Raised and the rule is no longer active |
| none | All other cases. A walk that is not `ok` keeps the state and gives none |

A transition produces one `datadog.MallocArenaWarning` event whose `state`
field is the transition name. The detector does not write the event again
while the state stays unchanged.

dd-trace-java uploads one file per `dump()`, and `dump()` ends a chunk. A
warning that was raised in an earlier chunk would then be missing in later
files. To avoid this, the first `finishChunk()` after `switchChunk()` writes
the current state again when the warning is active and the walk is `ok`. The
`state` field is then `raised` or `worsened`, as in the last emitted event.
`cleared` is not repeated. A new `Recording` starts idle, so a `stop` and
`start` can raise the warning again.

`MallocArenaStats` is written on every chunk, including when the walk failed
or when `arenawarn=0` is set. For a failed walk the counts are 0 and
`walkStatus` names the reason.

The writers do not allocate. The buffer is flushed after each event.

## Events

Both events have `startTime` (ticks) as the first field. A value that is not
available is -1. Strings are written inline, truncated to 32 bytes.

`datadog.MallocArenaStats`

| Field | Type | Note |
|---|---|---|
| `arenaCount` | int | |
| `nonMainArenaBytes` | long, bytes | Sum of `system_mem` of non-main arenas |
| `freeHeldBytes` | long, bytes | -1 without `mallinfo2` |
| `largestArenaBytes` | long, bytes | |
| `cpuQuotaMilli` | int | -1 without a quota |
| `memoryLimit` | long, bytes | -1 when unknown |
| `maxHeap` | long, bytes | -1 when unresolved |
| `walkStatus` | string | |

`datadog.MallocArenaWarning`

| Field | Type | Note |
|---|---|---|
| `state` | string | `raised`, `worsened` or `cleared` |
| `arenaCount` | int | |
| `arenaLimit` | int | Limit that glibc applies |
| `arenaLimitSource` | string | `tunable`, `env` or `default` |
| `onlineCpus` | int | |
| `cpuQuotaMilli` | int | |
| `memoryLimit` | long, bytes | |
| `memoryLimitSource` | string | `cgroup`, `physical` or `unknown` |
| `maxHeap` | long, bytes | |
| `nativeHeadroom` | long, bytes | |
| `headroomSource` | string | `limit-minus-heap` or `limit-only` |
| `heapExceedsLimit` | boolean | |
| `freeHeldBytes` | long, bytes | -1 without `mallinfo2` |
| `nonMainArenaBytes` | long, bytes | |
| `conditionMeasure` | string | `free-held` or `committed` |
| `thresholdPercent` | int | |
| `threadPrivateArenas` | int | -1 without `attached_threads` |
| `largestArenaBytes` | long, bytes | |
| `largestArenaMaxBytes` | long, bytes | Largest `max_system_mem` |
| `recommendedArenaMax` | int | 8 x quota CPUs, rounded up |
| `glibcVersion` | string | |
| `layout` | string | Calibrated layout name, empty when none |
| `walkStatus` | string | |

For a `cleared` event the numeric fields describe the chunk in which the
condition ended.

## Argument

`arenawarn=<percent>` takes an integer from 0 to 100. Other values are
rejected at argument parsing. The default is 25. The value 0 disables the
warning: no `MallocArenaWarning` is written. `MallocArenaStats` is still
written, and the walk still runs.

## Degraded inputs

| Situation | Result |
|---|---|
| Zing, or any JVM other than HotSpot and OpenJ9 | `walkStatus=unsupported-jvm`, no walk, no warning |
| Replacement allocator (`mallctl` or `tc_malloc_size` symbol found), ASan or TSan build | `replaced-allocator`, no walk, no warning |
| `glibc.malloc.hugetlb` 2 or more | `hugetlb-tunable`, no walk, no warning |
| No CPU quota | Condition 1 is false. Stats are still written |
| Memory limit unknown | Condition 2 is false |
| No `mallinfo2` (release builds) | `conditionMeasure=committed`, `freeHeldBytes=-1` |
| Layout not recognized | `walkStatus` is not `ok`, no warning, no crash |
| musl, macOS | No event is written |

The hugetlb check reads only `GLIBC_TUNABLES` of the process environment at
`Recording` creation.

## Open items

- Release builds cannot use `free-held` until `mallinfo2` is resolved at
  runtime.
- When the seed allocation lands in `main_arena`, the walk reports `no-seed`
  and does not retry from another thread in the same chunk.
- The detector does not attribute arenas to threads or stacks.

## Tests

- C++: `mallocArenaWalker_ut`, `mallocArenaInputs_ut`, `mallocArenaRule_ut`,
  `mallocArenaEvents_ut`, `mallocArenaStats_ut`, `jvmSupport_ut`,
  `arguments_ut`.
