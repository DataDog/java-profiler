# SIGSEGV Handler Protection via sigaction Interposition

## Problem

Some native libraries install SIGSEGV/SIGBUS signal handlers that violate POSIX async-signal-safety requirements. A notable example is **wasmtime**, whose signal handler calls `__tls_get_addr` for TLS access, which in turn may call `malloc()`.

When the profiler uses `safefetch` (safe memory access via intentional SIGSEGV), the following deadlock can occur:

1. Application code holds malloc's internal lock
2. Profiler's signal handler runs and calls `safefetch`
3. `safefetch` triggers SIGSEGV
4. Wasmtime's handler (installed on top of ours) runs first
5. Wasmtime's handler calls `__tls_get_addr` → `malloc()`
6. `malloc()` tries to acquire its lock → **deadlock**

## Solution

The profiler intercepts `sigaction()` calls via GOT (Global Offset Table) patching. When a library tries to install a SIGSEGV/SIGBUS handler, we:

1. Store their handler as a "chain target"
2. Keep our handler installed (the call returns 0 without installing theirs)
3. Call their handler from within ours when we do not handle the fault ourselves

To avoid chaining loops, both install calls and query-only calls (`act == nullptr`) return the JVM's original handler as `oldact`, never ours.

This ensures:
- Our handler always runs first
- We control when/if the chained handler is invoked
- Problematic handlers never become the "top" handler

## Implementation

### Components

1. **`os_linux.cpp`** - Signal handler protection logic:
   - `OS::protectSignalHandlers()` - Resolves the real `sigaction` via `dlsym`, saves the JVM's current SIGSEGV/SIGBUS handlers and records ours as protected
   - `sigaction_hook()` - Intercepts sigaction calls, stores chain targets (exposed through `OS::getSigactionHook()`)
   - `OS::getSegvChainTarget()` / `OS::getBusChainTarget()` - Return the current chain target
   - `os_macos.cpp` has no-op stubs

2. **`libraryPatcher_linux.cpp`** - GOT patching:
   - `LibraryPatcher::patch_sigaction_in_library()` - Patches the sigaction GOT entry in one library
   - `LibraryPatcher::patch_sigaction()` - Patches every loaded library not yet patched; a no-op until `LibraryPatcher::initialize_persistent()` has run

3. **`codeCache.cpp`** - Import tracking:
   - Tracks `sigaction` imports in loaded libraries (via `im_sigaction`)

4. **`profiler.cpp`** / **`libraries.cpp`** - Integration:
   - `Profiler::setupSignalHandlers()` - Installs our handlers (HotSpot and OpenJ9 only) and calls `patch_sigaction()`
   - `Profiler::dlopen_hook()` - After a successful `dlopen`, calls `Libraries::refresh()` (or, in a signal context, marks the library set dirty for the refresher thread)
   - `Libraries::refresh()` - Parses new libraries and calls `patch_sigaction()`
   - `Profiler::switchLibraryTrap()` - Enables/disables the dlopen hook

### Initialization Flow

```
JVM Initialization
    └── VM::ready()                                  (vmEntry.cpp, once)
        └── Profiler::setupSignalHandlers()
            ├── OS::protectSignalHandlers()          save JVM handlers; must precede install
            ├── OS::replaceSigsegvHandler() / replaceSigbusHandler()
            └── LibraryPatcher::patch_sigaction()    no-op if LibraryPatcher is not initialized yet

Java API init (JavaProfiler.getInstance() -> init0)
    └── Profiler::init()                             (once, state NEW)
        └── LibraryPatcher::initialize_persistent()  enables patching

Profiling Start
    └── Profiler::start()
        ├── LibraryPatcher::initialize_persistent()  idempotent; the first call on the
        │                                            -agentpath path (VMInit -> run())
        ├── Libraries::startRefresher()
        └── switchLibraryTrap(true)                  enable dlopen hook

Library Load (via dlopen) / refresher tick with dirty flag
    └── Libraries::refresh()
        └── LibraryPatcher::patch_sigaction()        patch every loaded, not-yet-patched lib
```

`LibraryPatcher::initialize_persistent()` is first called from `Profiler::init()` (Java API path) or `Profiler::start()` (`-agentpath` path), both of which normally run after `VM::ready()`. In that order the `patch_sigaction()` call in `setupSignalHandlers()` returns immediately, and libraries loaded before then are patched by the next `Libraries::refresh()` (triggered by a `dlopen`, by the refresher thread when the library set is marked dirty, or by `start()`'s first `updateSymbols()`). The `sigaction` and `pthread_create` GOT patches are persistent: `stop()` (`LibraryPatcher::unpatch_recording_hooks()`) only undoes the socket hooks.

### Signal Handler Chain

```
SIGSEGV occurs
    └── Profiler::segvHandler()
        ├── crashHandlerInternal(): profiler-related faults (safefetch, etc.)
        └── If not handled:
            ├── OS::getSegvChainTarget() set? → invoke it (e.g., wasmtime's, ASAN's)
            └── else → the handler replaceSigsegvHandler() displaced (JVM's)
```

`busHandler()` does the same for SIGBUS. An intercepted library that chains on to the `oldact` we returned reaches the JVM's original handler.

## Crash-handler bootstrap

`segvHandler`/`busHandler` first filter by fault PC with
`Profiler::isProfilerOwnedFault()`: a PC inside this library (SafeAccess stubs,
`checkFault` walks), a WX trap page, or the JDK-8313796 interpreter range. While
the library range is unknown every fault counts as owned. Other faults belong
to the JVM and chain before any syscall, TLS read, registry lookup or fence.

Owned faults then consult `ThreadExitRegistry` before TLS access.
Marked threads bypass `SignalHandlerScope` and `crashHandlerInternal` and
chain to the preceding handler, or the default action when none exists.

Early marks cover the pthread-create wrapper, JVMTI ThreadEnd, and normal
engine returns (wall timer, refresher, reference-chain BFS, J9 sampler).
The `ProfiledThread` TSD destructor supplies a later fallback mark.

Every mark site blocks profiling signals (`blockProfilingForExit`) before
publishing the identity: a marked thread's fault chains out without
SafeAccess or walk recovery, so a sampler must never be admitted after the
mark. The window before the block keeps only the pre-registry handler-bootstrap
exposure.

Registry identities use raw `gettid` (Linux) and `thread_selfid` (Darwin)
syscalls. Darwin profiler IDs remain Mach ports for Mach API users.
Registration clears stale registry identities when a thread ID is reused.

The 4096-slot registry scans all 64 probe slots, including deletion holes.
Removal uses compare-exchange so eviction cannot make it erase a replacement.
No allocation, TLS access or locking is required for membership operations.

On Linux, `CrashBootstrapFence` blocks SIGSEGV, SIGBUS, SIGPROF and SIGVTALRM
across the TLS prefix. A blocked synchronous fault takes the default action;
profiling walks are deferred so they cannot inherit blocked recovery faults.

The fence is a no-op on macOS. A blocked synchronous fault stays pending
there and the thread spins on the faulting instruction. Masking that fault
would live-lock the thread instead of terminating it.

The fence is explicitly disarmed before safefetch, `checkFault` or chaining.
Crash-depth admission is cached under the fence; safefetch precedes rejection
and undoes successful admission. `checkFault` resets depth before `siglongjmp`.

Each owned crash-handler entry makes one raw identity syscall for the
exit-registry lookup. On Linux the fence adds two mask syscalls, so an unmarked
owned entry costs at least three; recovery and chaining add their own. Faults
the PC filter rejects pay none of these. The empty `SIGIO` wakeup handler only interrupts sleep and does not
look up TLS or change signal depth.

These handlers use the interrupted stack, not `sigaltstack`. An unusable
handler-entry stack can fault before the registry or fence runs. Darwin has
no fence, so an unmarked thread can still recurse during bootstrap.

Unhooked native threads remain unmarked until their TSD destructor starts.
J9 cancellation skips the normal-return mark. The wrapper covers cancellation
only for threads it wraps; another mark family is not guaranteed.

Marks persist across lifetimes until registration clears them or pressure
evicts them. Once a 64-slot window is full, one colliding insertion can evict
even a recent mark; 64 simultaneous exits are not required.

A reused identity can bypass recovery until registration or a sampled
allocation clears the mark (`ThreadExitRegistry::isCurrentExiting()`). A thread
that does neither can retain that degradation for its whole lifetime. The crash
handler keeps the raw check: the reuse test reads TLS, which can fault here.

## Scope

All native libraries that import `sigaction` are patched, including:
- Application libraries (e.g., wasmtime)
- Sanitizer runtime libraries (libasan, libtsan, libubsan)

This provides defense-in-depth against any library that might install a SIGSEGV/SIGBUS handler. Sanitizer libraries are intentionally patched so our handler can intercept recoverable SIGSEGVs (e.g., from `safefetch`) while still chaining to the sanitizer's handler for unexpected crashes.

**Exclusions:**
- The profiler's own library
- Only SA_SIGINFO handlers (3-arg form) are intercepted for safe chaining; a 1-arg handler is passed through to the real `sigaction` and does replace ours
- Signals other than SIGSEGV/SIGBUS pass through unchanged
- At most `MAX_NATIVE_LIBS` libraries are patched

## Counters

Two counters track sigaction patching activity:
- `SIGACTION_PATCHED_LIBS` - Number of libraries where sigaction GOT was patched
- `SIGACTION_INTERCEPTED` - Number of sigaction install calls intercepted (handler installations prevented); query-only calls are not counted

## Why GOT Patching?

Alternative approaches considered:

1. **LD_PRELOAD** - Requires modifying JVM launch, not always possible
2. **Rebinding after load** - Libraries install handlers lazily, timing is unreliable
3. **Disabling safefetch** - Would disable core profiler functionality

GOT patching allows us to intercept function calls from specific libraries without affecting the rest of the process.

## Thread Safety

- `_segv_chain_target` / `_bus_chain_target` are read and written with atomic operations
- `LibraryPatcher::patch_sigaction()` runs as a `LiveLibraryWalk`: it holds `LibraryPatcher::_lock` (a `SpinLock`) and, on glibc, decides liveness inside a `dl_iterate_phdr()` callback so a library cannot be unloaded while its GOT is patched
- Our signal handlers do not allocate; `sigaction_hook()` only does atomic stores, struct copies and a counter increment before returning or calling the real `sigaction`

## Limitations

1. Only works on Linux (uses ELF GOT patching), and only on HotSpot and OpenJ9, where our handlers are installed
2. Requires the library to call `sigaction()` via PLT (not inline)
3. Library must be dynamically linked
4. Only SA_SIGINFO (3-arg) handlers are chained; 1-arg handlers pass through
