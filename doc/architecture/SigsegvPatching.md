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

The profiler intercepts `sigaction()` calls via GOT (Global Offset Table) patching. When libraries try to install signal handlers, we:

1. Store their handler as a "chain target"
2. Keep our handler installed
3. Call their handler from within ours (after our logic completes)

This ensures:
- Our handler always runs first
- We control when/if the chained handler is invoked
- Problematic handlers never become the "top" handler

## Implementation

### Components

1. **`os_linux.cpp`** - Signal handler protection logic:
   - `protectSignalHandlers()` - Registers our handlers for protection
   - `sigaction_hook()` - Intercepts sigaction calls, stores chain targets
   - `getSegvChainTarget()` / `getBusChainTarget()` - Returns current chain target

2. **`libraryPatcher_linux.cpp`** - GOT patching:
   - `patch_sigaction_in_library()` - Patches sigaction GOT entry in a library
   - `patch_sigaction()` - Iterates all libraries and patches them

3. **`codeCache.cpp`** - Import tracking:
   - Tracks `sigaction` imports in loaded libraries (via `im_sigaction`)

4. **`profiler.cpp`** - Integration:
   - `setupSignalHandlers()` - Installs handlers and patches already-loaded libs
   - `dlopen_hook()` - Patches newly loaded libraries
   - `switchLibraryTrap()` - Enables/disables dlopen hook

### Initialization Flow

```
JVM Initialization
    └── VM::ready()
        └── Profiler::setupSignalHandlers()
            ├── Install SIGSEGV/SIGBUS handlers
            ├── OS::protectSignalHandlers() - Mark handlers as protected
            └── LibraryPatcher::patch_sigaction() - Patch already-loaded libs

Profiling Start
    └── Profiler::start()
        └── switchLibraryTrap(true) - Enable dlopen hook

Library Load (via dlopen)
    └── dlopen_hook()
        └── LibraryPatcher::patch_sigaction() - Patch newly loaded libs
```

### Signal Handler Chain

```
SIGSEGV occurs
    └── Profiler::segvHandler()
        ├── Handle profiler-related faults (safefetch, etc.)
        └── If not handled: call OS::getSegvChainTarget()
            └── Invoke chained handler (e.g., wasmtime's, ASAN's)
```

## Scope

All native libraries are patched, including:
- Application libraries (e.g., wasmtime)
- Sanitizer runtime libraries (libasan, libtsan, libubsan)

This provides defense-in-depth against any library that might install a SIGSEGV/SIGBUS handler. Sanitizer libraries are intentionally patched so our handler can intercept recoverable SIGSEGVs (e.g., from `safefetch`) while still chaining to the sanitizer's handler for unexpected crashes.

**Exclusions:**
- The profiler's own library
- Only SA_SIGINFO handlers (3-arg form) are intercepted for safe chaining

## Counters

Two counters track sigaction patching activity:
- `SIGACTION_PATCHED_LIBS` - Number of libraries where sigaction GOT was patched
- `SIGACTION_INTERCEPTED` - Number of sigaction calls intercepted (handler installations prevented)

## Why GOT Patching?

Alternative approaches considered:

1. **LD_PRELOAD** - Requires modifying JVM launch, not always possible
2. **Rebinding after load** - Libraries install handlers lazily, timing is unreliable
3. **Disabling safefetch** - Would disable core profiler functionality

GOT patching allows us to intercept function calls from specific libraries without affecting the rest of the process.

## Thread Safety

- `_segv_chain_target` / `_bus_chain_target` use atomic operations
- `LibraryPatcher::patch_sigaction()` uses a spinlock
- Signal handlers are async-signal-safe (no allocations)

## Limitations

1. Only works on Linux (uses ELF GOT patching)
2. Requires the library to call `sigaction()` via PLT (not inline)
3. Library must be dynamically linked
4. Only SA_SIGINFO (3-arg) handlers are chained; 1-arg handlers pass through
