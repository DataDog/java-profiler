<!-- Copyright 2026, Datadog, Inc. -->

# Native I/O Hooks

The Linux native I/O interposer and native socket bytes sampler share imported
function patches. `NativeSocketInterposer` produces synchronous TaskBlock events;
`NativeSocketSampler` samples stream-socket bytes and elapsed time. Patching is
restricted to selected JDK networking libraries; non-Linux implementations do
not install these hooks.

## Ownership and forwarding

Each consumer publishes its own active flag before requesting installation.
`LibraryPatcher::_socket_active` describes installed/shared-refresh state, not
producer eligibility. Stop disables the consumer before conditionally removing
the patches; patches remain installed while the other consumer is active.
Installation failure disables both consumers and restores saved import values.
Original libc function pointers remain available for hooks entered before
restoration.

The four stream hooks forward directly to the saved original when both consumers
are inactive. That path performs no FD classification, clock reads, sampler
recording or NativeBlockScope construction. With only the bytes sampler active,
the wrappers use its existing hooks. With both active, the underlying I/O call
runs once and bytes recording follows the TaskBlock scope. Hook forwarding
preserves arguments, return values and errno.

## FD type and lifecycle

Each consumer has an independent `NativeFdClassifier`. Its lazily allocated
low-FD and direct-mapped high-FD tables distinguish stream, datagram, other socket
and stable non-socket verdicts. A cache word includes type, epoch and FD/slot
incarnation; high-FD entries additionally identify the descriptor sharing that
slot.

Classification captures the cache word and recording epoch **before** probing
SO_TYPE. It publishes only by comparing against that captured word. Close/dup
invalidation advances the incarnation, so a probe spanning the invalidation
cannot publish the old descriptor's type into its replacement's cache entry.
ENOTSOCK is a stable non-socket result; EBADF and other transient failures return
unknown without caching a negative verdict. Direct classifier ready-path cache
hits do not perform another SO_TYPE probe. **Hook admission is different:** every
active stream or datagram hook probes SO_TYPE before admitting TaskBlock or byte
sampling, including after a cached negative. Raw close/dup2 from an unpatched
library therefore cannot leave admission permanently positive or negative.
Concurrent replacement between that probe and the underlying syscall remains the
normal descriptor-number TOCTOU; these hooks do not acquire ownership of the
application's open file description.

The packed fields never cycle within a cache bank. Each classifier allocates two
65536-entry low-FD and 4096-entry high-FD banks on first classification (1,114,112
bytes of atomic entries total, excluding allocator overhead). Both owners
therefore retain at most 2,228,224 bytes of entries in four array allocations.
The first active classification may allocate the arrays; lifecycle invalidation
and subsequent classification do not allocate classifier tables. Banks are never
reused during that classifier's lifetime. A 17-bit epoch boundary retires the
current bank, as does exhaustion of a low/high slot's 28/24-bit incarnation.
Every successful stable publication consumes an incarnation, even when SO_TYPE
is unchanged; otherwise a delayed negative probe could overwrite a newer
same-type positive observation. Lifecycle invalidation also consumes an
incarnation. Thus a hot high-FD slot can retire a bank after 16,777,215 combined
publications/invalidations, including colliding descriptors, rather than only
after that many descriptor replacements. The probe that discovers exhaustion
is conservatively ineligible; later calls use the next bank or uncached probes.
Readers and publishers retain their captured bank and compare the **full**
64-bit epoch after probing. Once both banks retire, classification remains
available but does not read or publish cached verdicts. It probes each time;
there is no engine shutdown, table recycling, further classifier-table
allocation, or wrapped identity. The full epoch saturates at UINT64_MAX rather than wrapping. At that
final bound a fresh uncached probe still classifies but cannot detect an
invalidation that overlaps the syscall; no result is published or retained.
Lifecycle invalidation before first classification advances the epoch without
allocating tables. Both owners inactive means no classification, clocks, scopes,
or lifecycle-cache allocation, regardless of installed import state.

Recurring syscall cost is explicit: one SO_TYPE probe per entered active hook,
one additional SO_TYPE revalidation per sampled positive byte result, and one
getpeername per accepted sample. ENOTSOCK/transient admission adds one probe then
forwards directly. Combined ownership does not double admission probes. Direct
classifier calls remain cached until bank exhaustion; uncached fallback has the
same admission syscall count as the normal hook path. This favors correctness
under unobserved FD reuse over the previous zero-syscall ready admission path;
performance qualification must measure this new cost, not assume the old rate.

Sampled byte events require fresh revalidation. The sampler uses the
classifier's private forced-probe path: it bypasses a cached verdict but retains
the same pre-probe epoch/incarnation and conditional publication. It must not
probe first and then publish a non-socket verdict using a newly loaded cache
incarnation. A transient revalidation failure suppresses that sampled event,
not all subsequent sampling for a newly valid descriptor of the same number.

While either owner is active, the close hooks clear both type caches and the
sampler's address cache even on a failed close. Successful dup2/dup3 clear the target; failed duplication leaves
it unchanged. This invalidation covers calls through patched imports, not every
possible descriptor operation elsewhere in the process.

## Application-owned timeout memory

The ppoll, pselect and select hooks do not directly dereference their timeout
pointers. Inactive interposers forward without inspecting them. For an active
interposer on HotSpot/OpenJ9, the same VM kinds where `setupSignalHandlers()`
installs the profiler crash handler, a NOINLINE predicate uses
`SafeAccess::safeCopy()` to copy exactly one timespec/timeval into stack storage.
This is a bounded byte-granular read (16 bytes on supported Linux x64/arm64),
with no allocation or extra syscall. A failed copy suppresses TaskBlock admission
and forwards all original arguments and errno unchanged. It does not replace the
original timeout pointer with the snapshot.

Zing does not install that crash handler, so a non-null timeout is never read by
the profiler and that readiness call is not admitted to TaskBlock. A null timeout
needs no copy and retains normal infinite-wait eligibility. This policy trades
Zing timed-readiness visibility for transparent forwarding rather than adding an
unprotected read. The snapshot cannot pin application memory: the original libc
may still read or write the original pointer after the eligibility check.

The guarantee is **no new unhandled profiler-origin fault**, not universal EFAULT
for an invalid timeout. In particular glibc ppoll/pselect copy `*timeout` in userspace
before entering the kernel, and select also reads timeout fields in userspace.
A PROT_NONE timeout may therefore fault inside the original libc too. Tests must
separate safe-copy recovery and raw-kernel EFAULT forwarding from actual libc
baseline/hook comparisons; preserving a libc-origin fault is not evidence of a
new hook fault or of successful EFAULT recovery.

## Source-named checks

- `nativeSocketInterposer_ut.cpp`: inactive stream forwarding without probes or
  TaskBlock entry, active block kinds, sampler-only/combined forwarding,
  close/dup invalidation and production patch rollback.
- `nativeSocketSampler_ut.cpp`: low/high-FD transient revalidation and real reuse,
  forced-probe publication across low/high-FD replacement, stable classification
  and existing byte-sampler controls.
- `nativeIoQualification_ut.cpp`: packed epoch controls, competing/stale positive
  and negative publication, all four errno-forwarding branches, initial rollback
  and reverse ownership stop order.
- `nativeIoAdmission_ut.cpp`: real raw dup2 positive/negative reuse for every
  owner combination and all four branches, inactive allocation checks, scope and
  combined-recording errno preservation, plus bounded cache exhaustion. Its
  admission cost case reports paired raw/hooked SO_TYPE costs over 40000 actual
  socket operations per owner/FD combination, requires a real limit above 65536,
  checks exactly one admission probe per hook, and checks all owned descriptors
  are closed. Timing is diagnostic, not a throughput-threshold pass or a
  substitute for a running-profiler workload.
- `nativeFdClassifier_ut.cpp`: concurrent first-use cache publication, no
  allocation after pre-admission invalidation
  exhausts both banks, second-bank retirement with untouched positive and
  negative observations, and actual 28/24-bit incarnation-bound publication
  rejection, plus same-type successor publication against a stale ENOTSOCK probe.
  The incarnation case performs 268435456 low-FD and 16777216 high-FD
  invalidations through public APIs, with no private counter injection.
- `nativeIoTimeout_ut.cpp`: contained child faults for ppoll/pselect/select,
  HotSpot/OpenJ9 VM-dispatch safe-copy recovery, Zing/no-active-read forwarding,
  exact-boundary readable/null/zero/positive controls, original arguments/errno,
  and captured actual-libc baseline/hook fault comparisons. VM flags here model
  dispatch only, not a running JVM. The ppoll/pselect fault originals enter the
  actual kernel with the supplied pointer; select does so where SYS_select is
  available (x64), otherwise its original is a forwarding/errno control.
- `NativeIoErrnoTest` / `NativeIoCombinedErrnoTest`: real running JVM/profiler,
  installed JDK import targets (not UNIT_TEST), /dev/full DEBUG logging failures,
  original successful-I/O errno and sampled JFR operations for all four branches.

These units do not replace real JVM/JFR, unload/reload, architecture, sanitizer
or release-performance qualification.
