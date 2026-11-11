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
   - `LibraryPatcher::patch_sigaction()` - Patches every loaded library not yet patched; a no-op until `LibraryPatcher::initialize()` has run

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

Profiling Start
    └── Profiler::start()
        ├── LibraryPatcher::initialize()             enables patching
        ├── Libraries::startRefresher()
        └── switchLibraryTrap(true)                  enable dlopen hook

Library Load (via dlopen) / refresher tick with dirty flag
    └── Libraries::refresh()
        └── LibraryPatcher::patch_sigaction()        patch every loaded, not-yet-patched lib
```

`LibraryPatcher::initialize()` is first called from `Profiler::start()`, which normally runs after `VM::ready()`. In that order the `patch_sigaction()` call in `setupSignalHandlers()` returns immediately, and libraries loaded before `start()` are patched by the first `Libraries::refresh()` after it (triggered by a `dlopen` or by the refresher thread when the library set is marked dirty). GOT patches are not undone by `stop()`.

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
