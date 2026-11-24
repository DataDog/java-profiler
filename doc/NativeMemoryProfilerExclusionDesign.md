<!-- Copyright 2026, Datadog, Inc. -->

# Native-memory profiler exclusion

**Status:** Implemented. The admission check described here ships in this
change set; the glibc Linux behavior is covered by the gtest and child-JVM
suites in this repository. Verification against released ddprof archives (the
matrix below) is not complete for every cell.

This document records the design decision and its rationale. The implemented
runtime contract is documented in
[Native Memory Profiling](architecture/NativeMemoryProfiling.md).

## Decision

Configure one native-memory allocation profiler per process. Add a Java-side check
that rejects a native-memory profiling request when its allocation targets contain
a recognized direct ddprof hook or a retained forwarding pointer to that hook.

Do not add a `free` hook, bypass ddprof, or try to produce two native-memory
allocation profiles. Keep unrelated profiling engines available.

The Java-side check protects against an existing conflict. Startup configuration
must prevent later or concurrent activation of another allocation profiler. This
check alone cannot enforce process-wide exclusion across both activation orders.

## Problem

java-profiler saves allocation function pointers from its own Global Offset Table
(GOT). Each allocation hook forwards through the corresponding saved pointer.
It then replaces allocation imports in other loaded libraries.

If ddprof has already patched java-profiler's imports, the saved pointers can be
ddprof hooks. java-profiler can then redirect a library that ddprof did not patch
through those hooks:

```text
malloc -> java-profiler -> saved ddprof hook -> allocator
free   -> allocator
```

For the tested amd64 zstd-jni binary, ddprof skips the library because it has only
`DT_HASH`. java-profiler patches its allocation imports but not `free`. This changes
ddprof's allocation coverage without matching deallocation coverage. The issue is
not specific to zstd API names: the changed forwarding route causes the mismatch.

Released java-profiler 1.52.1 and ddprof 0.26.0/0.27.0 reproduce this route on Linux
x86_64 with glibc and jemalloc. Real zstd streams leave sampled live records after
all streams are closed. Stopping Java recording leaves the forwarding hooks
installed [S8]. These observations establish false live-profile accounting; they do
not establish production RSS growth or the original service-specific rates.

Sources: [Java hook capture and installation][S1], [ddprof ELF handling][S2], and
[ddprof activation][S3].

## Goals

- Reject the recognized existing ddprof allocation-hook conflict before Java's
  first allocation-hook writes for that request.
- Distinguish allocation interception from a ddprof library that is merely loaded.
- Preserve other successfully activated Java profiling engines.
- Handle both fresh initialization and cached forwarding pointers.
- Report incompatibility separately from symbol-resolution failure.
- Add no work to allocation, deallocation, or signal-handler paths.

## Non-goals

- Support simultaneous ddprof and Java native-memory allocation profiling.
- Enforce exclusion against later or concurrent ddprof activation.
- Change ddprof's `DT_HASH` handling or control ddprof through its start/stop API.
- Resolve or bypass ddprof to select another allocator target.
- Uninstall previous Java hooks or repair existing ddprof live records.
- Detect arbitrary static/custom profiler builds or a ddprof hook hidden behind
  another wrapper.
- Change sampling, JFR schemas, allocator configuration, or C++ allocation coverage.

## Configuration contract

The configuration owner is the tracer, launcher, or deployment that selects the
profilers. It must not request both allocation profilers for the same process.
The library check is a defensive admission check, not a replacement for this rule.

| ddprof configuration | Java native-memory request | Policy |
|---|---|---|
| No allocation profiling | Absent | No conflict |
| CPU-only, including a loaded library | Present | Allow if target inspection succeeds without recognizing a ddprof allocation hook |
| Allocation-volume or live-heap profiling | Absent | Do not reject Java CPU, wall, or Java-allocation modes for this conflict |
| Allocation-volume or live-heap profiling | Present | Reject Java native-memory activation when the direct hook is recognized |

A Java native-memory request means `nativemem` is enabled by the parsed arguments.
`nativemem=0` is a request to record every allocation; it is not a disable value.
A request without native-memory profiling must not invoke this check.

No new configuration flag or override is added. The check must not silently
change the process allocator or disable ddprof.

## Admission semantics

### Target set

Inspect these allocation operations:

- `malloc`
- `calloc`
- `realloc`
- `posix_memalign`
- `aligned_alloc`

For each operation, inspect:

1. The current targets of the profiler library's import slots that Java can patch.
2. The effective saved forwarding pointer, when one is already initialized.

An absent optional import is not an inspection failure and retains its existing
unsupported-operation behavior. Missing required allocator resolution retains a
symbol-resolution error, not a ddprof diagnostic.

Current imports and saved pointers are different state:

| Observed state | Current import | Saved forwarding pointer | Required result |
|---|---|---|---|
| ddprof started first; Java has not installed hooks | ddprof | Candidate ddprof target | Reject |
| Java previously captured ddprof, then stopped recording | Java hook | ddprof | Reject |
| Java captured the allocator; ddprof activated afterward | ddprof | Allocator | Reject the next Java native-memory start; do not claim this prevented the earlier overlap |
| Java stopped after an admitted, non-conflicting start | Java hook | Allocator | Recheck and allow if no conflict or inspection failure is found |

Recognize Java's own hook by its known function address, not by an image-name
match. Follow its saved forwarding pointer for admission. An own-hook target
without valid saved forwarding state is indeterminate; do not follow it into a
cycle or treat it as a clean allocator. The own-hook rules are platform-
neutral and also run on non-Linux; there only foreign-written inconsistent
own-slot states can newly reject, since the owner classifier always returns
`NOT_RECOGNIZED`.

Do not inspect every application's allocator import. The check covers
Java's own current and effective forwarding targets. It is not a consistency
audit of all loaded libraries.

### Target-owner identity

Locate the loaded image that contains the target address. Check whether that
same image defines externally visible function symbols named:

- `ddprof_start_profiling`
- `ddprof_stop_profiling`

Both must be definitions in the target-owning image. An undefined import, local
symbol, or definition found only in a dependency is not an owned exported
function. Accept ordinary defined function symbols; do not execute either
function or resolve a resolver-backed (GNU IFUNC) marker candidate. The known
ddprof shared-library export contract contains both markers [S9].

These markers identify the known shared-library ABI, not ddprof's internal
recording state. A retained pointer into that image is enough to reject the
chain even if ddprof has subsequently stopped recording.

Identity must not depend on a basename, extraction path, `LD_PRELOAD`, an
environment flag, or a global `dlsym` result. A global lookup can find the loader
or a different image. Renamed and extracted libraries must use the same rules.

### Inspection outcomes

| Outcome | Meaning | Admission |
|---|---|---|
| `DDPROF` | The target-owning image defines both exported function markers | Reject |
| `NOT_RECOGNIZED` | Valid owner metadata contains no owned externally visible definition of either marker name | Continue checking other targets |
| `INDETERMINATE` | Owner/lifetime/metadata cannot be validated, owned marker definitions are partial, wrong-kind or ambiguous, or forwarding state is inconsistent | Reject with an inspection diagnostic |

**Conservative policy:** indeterminate inspection declines Java
native-memory profiling. Do not report that ddprof was detected when inspection
was indeterminate.

A recognized ddprof target takes precedence over an indeterminate target. The
check may stop on `DDPROF`; otherwise retain any indeterminate result and inspect
the remaining targets before choosing the diagnostic. After resolving known
Java-hook forwarding, admit only if no relevant target produces `DDPROF` or
`INDETERMINATE`.

`NOT_RECOGNIZED` is not proof that no profiler exists downstream. Admission is
limited to the supported direct-hook case. A third-party wrapper can conceal the
next function it calls; the configuration contract remains necessary.

## Startup sequence

### Fresh hook initialization

1. Locate the profiler library and resolve its allocation imports using the
   existing resolution behavior. Resolution can call allocation functions; this
   design does not promise an allocation-free startup. A required-resolution
   failure returns the resolution error before any commit, nested probe, mark
   or seed; the error text and its caching are unchanged. (The nested probe no
   longer runs in that branch: its temporary write can land in the image that
   owns the `posix_memalign` target, which can be a ddprof hook image.)
2. Build candidate forwarding state locally. Do not commit compatibility success
   or publish new forwarding state yet.
3. Inspect the current imports and candidate forwarding targets.
4. On rejection, return the specific error without running nested probes,
   publishing `_running`, advancing `_patched_libs`, or installing allocation
   hooks.
5. After admission, commit the forwarding state and run the existing nested-call
   probes, hook marking, and random-generator initialization.
6. Publish initialized state only after successful initialization. Continue with
   the existing running-state publication and library patching.

The check must precede `detectNestedMalloc()`, not just `patchLibraries()`.
The nested probe already patches imports in the image that owns the saved
`calloc` or `posix_memalign` target. That image can be ddprof, despite the existing
local variable being named `libc` [S1].

### Cached initialization

Before returning success from cached initialization, recheck the current imports
and saved forwarding state. Do not assume that a prior successful admission
remains valid.
Do not refresh the saved pointers by copying Java's own installed hooks.

A rejection must not erase, replace, or relabel previously saved targets. Existing
hooks can remain installed from an earlier session; declining a new session does
not undo that state. A process that already ran the unsafe combination needs a
restart with exclusive configuration for a clean baseline.

Do not cache a compatibility rejection as successful initialization. A later
attempt must inspect the then-current imports and retained forwarding state.
Generic resolution failures must remain distinguishable from compatibility
failures; this design does not require unrelated initialization-cache changes.

### Background library refresh

Do not add inspection to allocation hooks or to the periodic library refresher.
The normal refresher gates its installer call on a positive
`MallocTracer::running()` check [S4]. A fresh admission rejection must never
publish running state or arm allocation-hook installation through the refresher.

The check and third-party patching do not share an atomic transaction. A ddprof
start between inspection and Java hook installation is outside the guarantee.
Do not describe the check as race-free process-wide arbitration.

## Error behavior

Return an `Error` that distinguishes these cases:

| Condition | Diagnostic |
|---|---|
| Recognized direct/retained ddprof hook | `Native-memory profiling was not started: an allocation target points to a ddprof hook. Enable only one native-memory allocation profiler for this process.` |
| Indeterminate inspection | `Native-memory profiling was not started: allocation-target ownership could not be determined.` |
| Allocator resolution failure | Preserve the allocator-resolution diagnostic |

Change the internal `MallocHooker::initialize()` result from `bool` to `Error`.
Have `MallocTracer::start()` propagate that error before enabling the tracer.
Cover the initialized return path as well as fresh initialization. Do not convert
compatibility rejection to the generic "Failed to resolve malloc symbols" error.

Use the existing engine-start error path [S5]:

- A native-memory-only request fails with the specific error and existing cleanup.
- A mixed request reports the native-memory error and can continue if another
  requested engine activates successfully.
- If no engine activates, overall startup still fails.

The detector returns its result; it must not add another helper-level warning on
top of the existing engine-start warning. Diagnostics must not claim that ddprof
is recording merely because a retained pointer identifies its hook image. Do
not recommend a retry as a guaranteed repair.

## Implementation boundaries

Keep common admission/state handling in the malloc tracer. Put ELF and loader
inspection in Linux implementation code behind an internal platform interface.
Other platforms retain their current native-memory behavior; no Linux ELF logic
belongs in shared code under new preprocessor branches.

Use read-only import access. `CodeCache::peekImport()` exposes only the primary
slot [S7], while `patchImport()` can write multiple slots [S10]. Provide a bounded
read-only view of the relevant slots rather than calling an accessor that makes
the GOT writable or inspecting only the first slot.

Deduplicate target addresses and protected owner-image identities within an
attempt using small fixed-capacity collections. Reuse an owner's classification
only while its lifetime protection remains held. Do not add a process-lifetime
owner-identity cache: mapping reuse and later hook changes would invalidate it.

Owner lookup finds the owning image and checks target containment inside one
`dl_iterate_phdr()` callback. The loader holds its load write-lock for the
whole iteration, and `dlclose()` unmaps only under that same lock (musl never
unmaps), so a reported object stays mapped while its callback runs. No loader
handle is acquired; lifetime is held by the loader iteration. Containment is
checked against the loader's live program headers of the same object, so a
stale `CodeCache` for a reused range cannot misattribute the owner.
Read in-memory exported-symbol metadata with checked ranges and arithmetic.
Use the architecture's pointer normalization for address comparisons without
changing the saved callable function pointer. Do not require an on-disk file or
dereference an unvalidated target/image.
An inspection failure must become `INDETERMINATE`, not a false negative or crash.

Query the ELF GNU/SysV symbol hash/index for the two names; do not linearly scan
large symbol tables. The existing `CodeCache::findSymbol()` uses a linear name
scan [S6] and is not the production lookup. Likewise, do not add a
repeated full-library scan for each operation; account for the existing address
lookup's cold path rather than claiming it is constant time.

Each GNU or SysV hash-chain walk has a 65,536-entry work cap. Exceeding it
returns `INDETERMINATE` and rejects native-memory activation, even if the image is
otherwise a valid ELF. This is a conservative compatibility limit; the tested
ddprof 0.26.0 and 0.27.0 images have a longest GNU chain of two entries.

The detector runs in ordinary profiler-start context, not in a malloc hook or
signal handler. No new detection flag, symbol lookup, allocation, logging, lock,
or loader operation may enter those hot paths.

## Cost and compatibility

The intended added cost is startup-only target/image inspection. The target set
is bounded by five operations, their import slots, and retained forwarding
pointers. Deduplication avoids repeated image work for shared targets.

No free hook, address-tracking table, background polling, per-allocation lookup,
JFR field, or public Java API is added. Existing sampling and hook forwarding are
unchanged after an admitted start.

Startup latency and temporary allocations have not been measured for an
implementation. Record cold/cached admission costs and allocation counts before
merge; do not substitute the inspection prototype's runtime for those results.

## Acceptance criteria

These are implementation requirements, not claims that a guard already passes.

| ID | Required observation |
|---|---|
| AC1 | Without a Java native-memory request, the detector is not called and existing profiling behavior is unchanged. `nativemem=0` does invoke admission. |
| AC2 | Existing ddprof allocation-volume and live-heap hooks reject Java native-memory activation under glibc and jemalloc. Test ddprof 0.26.0 and 0.27.0 or record an explicitly reviewed replacement baseline. |
| AC3 | Explicitly loaded CPU-only ddprof and no-ddprof controls allow Java native-memory sampling. Assert nonzero native-allocation events from a real workload. |
| AC4 | Each of the five operations independently triggers rejection when its current or saved target identifies the hook image. Cover secondary import slots and deduplicated addresses. |
| AC5 | Detection succeeds for renamed/extracted hook images and does not depend on an on-disk pathname. Dependency-only markers, undefined symbols, local symbols, and partial/invalid metadata follow the stated classification rules. |
| AC6 | On a fresh rejection, neither the temporary nested probe nor permanent allocation-hook writer runs. Snapshot after ordinary import resolution, or distinguish the dynamic linker's lazy-binding writes from Java hook writes. `_running` remains false, `_patched_libs` does not advance, and admission success is not cached. |
| AC7 | Java-hook current imports cannot conceal a saved ddprof target across stop/restart. Conversely, a clean saved allocator cannot conceal a newly installed current ddprof hook on the next Java start. |
| AC8 | An admitted cached restart with unchanged non-conflicting targets still samples correctly. A rejected attempt is reevaluated on the next request without copying Java hooks into saved forwarding state. |
| AC9 | A native-memory-only conflict returns the specific error. A mixed request with a working other engine remains usable, emits that engine's events, and emits no native-memory samples from the rejected session. Cover the no-engine-activated failure branch too. |
| AC10 | Indeterminate inspection declines native-memory activation without a false ddprof claim, invalid read, leaked handle, or generic symbol-resolution misdiagnosis. A recognized ddprof target takes diagnostic precedence over another indeterminate target. Missing optional imports retain their current behavior. |
| AC11 | The known zstd workload with ddprof-first startup no longer acquires a Java-to-ddprof allocation bridge after the rejected request. Capture hook targets before/after; do not accept an empty profile alone as proof. |
| AC12 | No additional code runs on allocation/free/signal paths. Record cold/cached startup costs and temporary allocations against the same build configuration. |
| AC13 | Real late/concurrent ddprof activation remains a documented unsupported configuration; tests and user messages must not claim that the startup check prevents it. |

Use gtests for target classification, ELF bounds, import enumeration, state
transitions, and resource ownership. Fixtures must exercise the production lookup
against actual ELF definitions, not inject the expected classification result.
Cover GNU hash, SysV hash, both tables, missing tables, invalid bucket/chain ranges,
unterminated or cyclic chains, and size arithmetic boundaries. Cover wrong-kind marker definitions, unattributable targets (`NO_OWNER` for
anonymous or unloaded ranges), and the callback contract: no loader, lock,
log or allocation call inside the callback, and admission concurrent with a
`dlopen`/`dlclose` loop finishes without deadlock. Assert that inspection does
not increment marker-function or resolver call counters. Use real released ddprof binaries and JNI workloads for
end-to-end routing and mixed-engine behavior.

For merged native/Java code, run the repository wrapper for `gtestDebug` and
`testDebug`, plus the relevant ASan suites where available. Run the aarch64
container gate for lifecycle/native-memory-reader changes. Validate the Linux
musl path and unchanged macOS behavior; neither follows from the glibc x86_64
experiments. See the [Testing Guide](building/TestingGuide.md) for tooling.

Native-memory JFR checks must assert the required fields and workload execution,
not just the existence of a file. Use Jafar for manual JFR analysis. Preserve
machine-readable results, exact binary revisions, configuration, and logs.

## Alternatives

| Alternative | Reason not selected |
|---|---|
| Add pass-through `free` interception | Pursues coexistence, which is not the required policy; adds deallocation-path work and another forwarding contract |
| Resolve an allocator target that bypasses ddprof | Changes ddprof coverage for libraries that Java patches rather than enforcing exclusion |
| Match library names or environment flags | Does not establish the actual forwarding target; can confuse CPU-only presence with allocation interception |
| Check only current GOT entries | Misses retained forwarding pointers after Java hook installation |
| Check only saved pointers | Misses changed current imports after a later third-party start |
| Recheck on each allocation or poll in the background | Adds hot/background cost and still does not provide shared activation arbitration |
| Stop Java recording after overlap | Leaves installed forwarding hooks; does not restore a clean process |
| Fix ddprof's ELF coverage alone | Can correct the specific coverage gap, but does not establish the chosen one-allocation-profiler policy |

## Review and delivery

Review must explicitly accept:

1. The bounded startup-only guarantee and configuration owner's responsibility.
2. Conservative rejection on indeterminate ownership inspection.
3. Recognition of the known direct shared-library ABI, not arbitrary hidden or
   custom hooks.
4. Startup inspection cost, with no allocation/free-path compatibility work.

The implemented runtime contract is documented in
[Native Memory Profiling](architecture/NativeMemoryProfiling.md), and the
native subsystem summary in `ddprof-lib/src/main/cpp/AGENTS.md` names the
admission check. Keep both in sync with this design in the same change set.

## Sources and verification baseline

The mechanism and lifecycle distinctions above were checked against released
java-profiler 1.52.1, ddprof 0.26.0/0.27.0, and zstd-jni 1.5.7-25 on Linux x86_64
with glibc 2.39 and jemalloc 5.3.0. There are 58 checked cases covering routing,
owner identity, recording lifecycle, later activation, and closed-stream live
accounting. The glibc Linux behavior is covered by the gtest and child-JVM
suites in this repository; the implementation verification matrix targets Linux
x86_64 and aarch64 with the published ddprof 0.26.0 and 0.27.0 archives and is
not complete for every cell. A blocked matrix cell does not
establish behavior for that architecture or mode. No service-specific
percentages, production growth rates, or RSS measurements are assumed here.

[S1]: https://github.com/DataDog/java-profiler/blob/06b4be4a64abeaa17233de9d9c75a2a69153bb6e/ddprof-lib/src/main/cpp/mallocTracer.cpp#L26-L261
[S2]: https://github.com/DataDog/ddprof/blob/29982d18e35948dffaa6010d7a396b37bb3cf1fb/src/lib/elfutils.cc#L126-L223
[S3]: https://github.com/DataDog/ddprof/blob/9830a2e27ac15fa08f4761c94392de8b9edb3d04/src/lib/dd_profiling.cc#L365-L400
[S4]: https://github.com/DataDog/java-profiler/blob/d6134dcf7b23e258fdbbba71b26f74cc0aea47fc/ddprof-lib/src/main/cpp/libraries.cpp#L79-L95
[S5]: https://github.com/DataDog/java-profiler/blob/d6134dcf7b23e258fdbbba71b26f74cc0aea47fc/ddprof-lib/src/main/cpp/profiler.cpp#L1734-L1810
[S6]: https://github.com/DataDog/java-profiler/blob/d6134dcf7b23e258fdbbba71b26f74cc0aea47fc/ddprof-lib/src/main/cpp/codeCache.cpp#L285-L293
[S7]: https://github.com/DataDog/java-profiler/blob/d6134dcf7b23e258fdbbba71b26f74cc0aea47fc/ddprof-lib/src/main/cpp/codeCache.h#L350-L362
[S8]: https://github.com/DataDog/java-profiler/blob/06b4be4a64abeaa17233de9d9c75a2a69153bb6e/ddprof-lib/src/main/cpp/mallocTracer.cpp#L406-L410
[S9]: https://github.com/DataDog/ddprof/blob/9830a2e27ac15fa08f4761c94392de8b9edb3d04/cmake/dd_profiling.version
[S10]: https://github.com/DataDog/java-profiler/blob/d6134dcf7b23e258fdbbba71b26f74cc0aea47fc/ddprof-lib/src/main/cpp/codeCache.cpp#L458-L479
