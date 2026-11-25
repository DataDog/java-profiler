<!-- Copyright 2026, Datadog, Inc. -->

# Native I/O Hooks

The Linux native I/O interposer and native socket bytes sampler share imported
function patches. `NativeSocketInterposer` produces synchronous TaskBlock events;
`NativeSocketSampler` samples stream-socket bytes and elapsed time. Patching is
restricted to selected JDK networking libraries and validated Netty native epoll
images, including shaded images with cached markers. Non-Linux implementations
do not install these hooks.

## Ownership and forwarding

Each owner start reserves an installation generation and publishes its active flag
together under the patch lock, before library discovery.
`LibraryPatcher::_socket_active` describes installed/shared-refresh state, not
producer eligibility. Stop disables the consumer before conditionally removing
the patches; patches remain installed while the other consumer is active.
A current installation failure disables both consumers and restores saved import values.
A failure local to one Netty image is the exception; see [Netty epoll](#netty-epoll).
A failed discovery from an older generation cannot disable a newer owner.
Original libc function pointers remain available for hooks entered before
restoration.

The four stream hooks forward directly to the saved original when both consumers
are inactive. That path performs no FD classification, clock reads, sampler
recording or NativeBlockScope construction. With only the bytes sampler active,
the wrappers use its existing hooks. With both active, the underlying I/O call
runs once and bytes recording follows the TaskBlock scope. Hook forwarding
preserves arguments, return values and errno.

The JDK 8 libnet poll-to-ppoll adapter remains the forwarding target when a
shared hook displaces it. Both owners preserve that policy, including sampler-only
operation. Other poll imports keep their globally resolved original.

## Interval and patch domains

Native scopes project the current thread's registry identity lazily. They use the
same generation-qualified block tracker and recording-activity gate as Java and
JVMTI producers. Entry requires no active span or context window. Exit captures
one synchronous IO_WAIT stack for an eligible completed interval.

Native admission classifies the owner's JDK housekeeping status on first use.
The cached `InnocuousThread` verdict also covers threads created before recording.
Synthetic thread-start callbacks preserve a known verdict.

Active calls use `run_with_cleanup` to end intervals on return or cancellation.
The scope uses explicit storage, so no automatic C++ destructor spans libc's
cancellation point. This avoids static-libgcc forced-unwind cleanup actions.

Cancellation is disabled during admission and cleanup, not during application I/O.
Each admitted call adds cancellation-state transitions and a libc cleanup registration.
The original cancellation state is restored before calling libc and before returning.

A live dump emits no prefix for an open native interval. An exit after the dump
writes the full interval. An exit during closed rotation clears its owner and
increments `task_block_dropped_rotation` without retaining an event. Stop/start
invalidates open owners; an old exit cannot consume a new recording's native run.
TaskBlocks have no cached anchor or correlation field.

Socket transactions pin their selected DSOs while import slots are installed.
Non-socket patching uses a live-library walk for pthread and sigaction imports.
The domains can share a DSO, but never an import slot or restoration table.
Image fingerprints hash relocation layout and symbol names, not patched values.

### Full-RELRO reloads

Each new socket transaction candidate re-establishes GOT writability while its
validated image is pinned and the patch lock is held. Stopping releases that
pin; an identical DSO can then reload at the same base with a read-only
full-RELRO GOT. The append-only `CodeCache` survives that reload, so its cached
patchability flag cannot establish the new mapping's protection. The native
transaction and the non-socket live walker both use unconditional
`makeImportsWritable()` before writing new mappings, retaining their separate
import ownership and rollback rules.

The patchability cache is atomic: `LibraryPatcher` and `MallocHooker` use
separate patch locks. Acquire/release protects that shared flag, not DSO
lifetime; each writer still needs its own mapped-image validation and pin.

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
hits do not perform another SO_TYPE probe. **TaskBlock admission is different:**
while the interposer is active, every stream or datagram hook probes SO_TYPE
before it admits TaskBlock, including after a cached negative. Raw close/dup2
from an unpatched library therefore cannot leave TaskBlock admission permanently
positive or negative. Sampler-only admission uses the sampler's cached verdict
and probes only on a cache miss. A stale positive verdict is caught by the
sampled-event revalidation. A stale negative verdict suppresses byte sampling of
that descriptor until a patched close/dup or a recording restart invalidates it.
Concurrent replacement between a probe and the underlying syscall remains the
normal descriptor-number TOCTOU; these hooks do not acquire ownership of the
application's open file description.

The packed fields never cycle within a cache bank. Each classifier allocates two
65536-entry low-FD and 4096-entry high-FD banks on first classification (1,114,112
bytes of atomic entries total, excluding allocator overhead). Both owners
therefore retain at most 2,228,224 bytes of entries in four array allocations.
Both owners are process-lifetime singletons, so the tables stay allocated after
`stop()` and are never freed. The `native_mem_*` counters do not include them.
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

Recurring syscall cost is explicit. TaskBlock admission costs one SO_TYPE probe
per entered hook while the interposer is active. Sampler-only admission costs no
probe on a cache hit. Each sampled positive byte result costs one additional
SO_TYPE revalidation, and each accepted sample costs one getpeername. A transient
admission failure is not cached, so it costs one probe on every call. Combined
ownership does not double admission probes. Classifier calls remain cached until
bank exhaustion; the uncached fallback probes on every classification.

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
Before copying, `ThreadExitRegistry::isCurrentExiting()` rejects exiting threads, whose
faults the crash handlers chain without recovery. A stale mark on a reused identity (no
`ProfiledThread`, profiling signals unblocked) is cleared instead, so its copy is recovered.
The lookup adds one syscall per non-null timeout, and a mask query for a marked identity.

The copy is bounded to 16 bytes on supported Linux x64/arm64 and does not allocate.
An exiting thread or failed copy suppresses TaskBlock admission and forwards all original
arguments and errno unchanged. The original timeout pointer is not replaced.

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

- `LibraryPatcherSocketTransactionTest.OwnerRestartMakesReloadedFullRelroImportsWritable`:
  production owner start/stop, actual unmap/reload at the same base, read-only GOT
  precondition, restarted installation/forwarding and restored originals.
- `NettyEpollImageSkipTest`: a missing slot, incomplete imports, a failed pin of a
  mapped image or a GOT that cannot be made writable skip only the
  Netty image beside a patched JDK libnet, with both owners active, the counter,
  no retained pin and no retry before the next installation. A Netty failure after
  validation, a libnet failure or a full skip table still fails closed. A stale
  generation or an inactive refresh records no skip. A missing libc `epoll_pwait2`
  leaves a non-NULL Netty slot untouched and keeps the other hooks.
- `NettyEpollAliasDiscoveryTest`: removed loader symlinks with live/deleted backing
  files, forwarding/restoration, final-close retention and unload before fallback pin.
- `LibraryPatcherSocketTransactionTest.OwnersPreserveDisplacedJdk8PollAdapterForwardingAndRestoration`:
  both owner modes retain the ppoll adapter, without redirecting ordinary poll calls.
- `libraryPatcherUnload_ut.cpp`: pin/restore socket safety, pthread live-walk
  fingerprint identity, foreign-loader-lock order and same-layout replacement.

- `nativeIoCancellation_ut.cpp`: contained release-mode pthread cancellation of
  read, recv, poll and accept, including pending cancellation, join and owner/TLS cleanup.
- `JvmInternalThreadClassificationTest`: cached positive/negative housekeeping
  verdicts, JNI/JVMTI failure cleanup and synthetic-start preservation.
- `NativeSocketTaskBlockTest`: pre-recording platform poller exclusion (Read-Poller
  or MasterPoller) with a platform control; clean-context pinned JNI read attribution
  against observed carrier Java id and Linux tid.
- `NativeSocketCarrierReuseTest`: ordered context-writer and pinned-read lifecycles
  in one JVM with a single reused carrier.
- `nativeSocketInterposer_ut.cpp`: zero-slot incomplete-import rejection and inactive stream forwarding without probes or
  TaskBlock entry, active block kinds, sampler-only/combined forwarding,
  close/dup invalidation and production patch rollback.
- `nativeSocketSampler_ut.cpp`: low/high-FD transient revalidation and real reuse,
  forced-probe publication across low/high-FD replacement, stable classification,
  probe-free unsampled admission with sampled-event revalidation, and existing
  byte-sampler controls.
- `nativeIoQualification_ut.cpp`: packed epoch controls, competing/stale positive
  and negative publication, all four errno-forwarding branches, initial rollback
  and reverse ownership stop order.
- `nativeIoAdmission_ut.cpp`: real raw dup2 positive/negative reuse for every
  owner combination and all four branches, inactive allocation checks, scope and
  combined-recording errno preservation, plus bounded cache exhaustion. Its
  admission cost case reports paired raw/hooked SO_TYPE costs over 40000 actual
  socket operations per owner/FD combination, requires a real limit above 65536,
  checks one TaskBlock admission probe per hook and none for a warm sampler-only
  verdict, and checks all owned descriptors are closed. Timing is diagnostic, not a throughput-threshold pass or a
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
  live-marked, exiting and reused identities with real profiler crash handlers, and actual-libc
  baseline/hook fault comparisons. VM flags here model
  dispatch only, not a running JVM. The ppoll/pselect fault originals enter the
  actual kernel with the supplied pointer; select does so where SYS_select is
  available (x64), otherwise its original is a forwarding/errno control.
- `NativeIoErrnoTest` / `NativeIoCombinedErrnoTest`: real running JVM/profiler,
  installed JDK import targets (not UNIT_TEST), /dev/full DEBUG logging failures,
  original successful-I/O errno and sampled JFR operations for all four branches.

These units do not replace real JVM/JFR, unload/reload, architecture, sanitizer
or release-performance qualification.

## Netty epoll

Netty images are selected by the exact epoll JNI load/unload markers cached during
symbol ingestion. Discovery validates the mapped base and fingerprint, not pathname
equality. It pins each image before reading cached imports and retains the pin until restoration.

If the cached maps pathname cannot pin an image, discovery copies its loader-owned
name outside the patch lock. It pins by that name and revalidates the fingerprint.
This supports deleted backing files and removed symlinks after marker ingestion.

Initial ingestion is not guaranteed when neither pathname can retain the image.

A failure local to one Netty image skips only that image. These failures are a
failed pin, incomplete imports, a GOT that cannot be made writable and a missing
import slot. The commit validates each new Netty image before any GOT write.
A skipped image has no patch, and its pin is released before the transaction
returns. Other libraries keep their patches, and both owners stay active. Each
skip increments `native_io_netty_images_skipped`.

The patcher remembers a skipped image by base and fingerprint until the socket
patches are removed. This also skips other cached descriptions of the same image.
Library refreshes and a second owner start do not retry it. The next
installation, normally the next recording, retries it once. An unmapped image or
a fingerprint mismatch is not a failure: discovery ignores it without a skip.

These failures still disable both owners and restore every image: a missing libc
original, a candidate-table or transaction allocation failure, any JDK image
failure, a full table of 64 skipped images and a missing slot found after
writes started. A stale generation still
abandons the transaction without changing a newer owner.
A NULL weak `epoll_pwait2` import stays NULL; supported imports use the same
errno-preserving scope as the other epoll waits. When libc has no `epoll_pwait2`
(glibc before 2.35), every `epoll_pwait2` import stays untouched. This includes a
non-NULL lazy-binding stub. Such an import does not disable the hooks or skip the image.

Recording admission validates the requesting native TID, lifecycle generation and
recording epoch under the registry lock before provisioning suppression backing
and resetting its payload. Cold admission retries failed allocations and prepares
context sidecars when a later recording enables snapshots.
The registry retains live ownership across restarts; an old completion cannot
consume another worker's run. This lock is independent of loader/patcher locks.

The real-Netty JVM fixture qualifies Linux glibc: the published Netty native
artifacts require glibc. Missing epoll availability fails that fixture on glibc;
musl retains the profiler's native epoll, weak-import and lifecycle tests instead.
Qualification runs five positive-timeout JNI waits on a verified `EpollEventLoop`
worker (`inEventLoop()`), separately from the unchanged default-select-strategy
case, and retains matching syscall, JFR and independently owned child-exit evidence.
