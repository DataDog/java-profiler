# Plan: Signal Origin Validation for ddprof Signal Handlers

## Goal
Make ddprof's signal handlers process only signals that originated from ddprof's own timers / inter-thread kills. Foreign signals are forwarded to the previously-installed handler.

Context: A Go-cgo shared library (e.g. trivyjni) linked into the JVM can install
`setitimer(ITIMER_PROF)` via `dd-trace-go`'s CPU profiler. That timer is
process-wide and delivers SIGPROF to arbitrary threads — including threads that
were never registered with ddprof's `pthread_create` interceptor. ddprof's
SIGPROF handler currently processes every SIGPROF, which can land on threads
whose dynamic-TLS blocks for libjavaProfiler.so have not been allocated yet.
First-touch access of any `thread_local` on such a thread inside the signal
handler triggers `__tls_get_addr` → `calloc`, which can deadlock against a
malloc lock held by the interrupted thread.

## Scope

- SIGPROF (CTimer — default CPU engine, `timer_create`-based)
- SIGVTALRM (WallClock engine, ASGCT variant)
- **Out of scope**:
  - SIGSEGV / SIGBUS — synchronous faults use a different discrimination
    mechanism (SafeAccess PC range check).
  - ITimer (alternate CPU engine, `setitimer(ITIMER_PROF)`-based) — setitimer
    signals carry `si_code == SI_KERNEL` with no `sigval` payload, so an
    origin cookie cannot be attached. Migrating ITimer to `timer_create`
    would duplicate CTimer. ITimer is a fallback for platforms where
    `timer_create` is unavailable; deployments vulnerable to the Go
    `ITIMER_PROF` deadlock should use CTimer (the default).

## Design

### Discriminators by signal source

| Source | `si_code` | Additional validation |
|---|---|---|
| `timer_create` (CTimer; ITimer post-migration) | `SI_TIMER` (-2) | `siginfo->si_value.sival_ptr == CPU_COOKIE` |
| `rt_tgsigqueueinfo` (WallClock — new) | `SI_QUEUE` (-1) | `siginfo->si_value.sival_ptr == WALLCLOCK_COOKIE` |
| `setitimer` (foreign — Go's CPU profiler) | `SI_KERNEL` / kernel-defined | none → untrusted, must forward |
| `kill` / `raise` | `SI_USER` (0) | none → forward |
| `tgkill` / `pthread_kill` (foreign) | `SI_TKILL` (-6) | none → untrusted, must forward |
| `sigqueue` from another process | `SI_QUEUE` (-1) + foreign cookie | cookie mismatch → forward |

### Cookie strategy

Static per-engine sentinels in a shared header. Use non-null, easily
identifiable constants:

Cookies live in `signalCookie.h` and are exposed via inline functions
(`reinterpret_cast` is not allowed in `constexpr`):

```cpp
namespace SignalCookie {
    inline void* cpu()       { return reinterpret_cast<void*>(0xDDDD01); }
    inline void* wallclock() { return reinterpret_cast<void*>(0xDDDD02); }
}
```

One cookie for CTimer (the only CPU engine that can carry a cookie), one for
wallclock. Rationale for wallclock needing a cookie: `SI_TKILL` +
`si_pid == getpid()` is **not** sufficient — `si_pid` for `SI_TKILL` is the
sending process's PID, and all threads in our process share the same PID, so
that check accepts any in-process `tgkill` of SIGVTALRM (including from other
libraries). Real isolation requires a payload.

### Portable per-thread queued signal

`pthread_sigqueue(3)` is a glibc-only extension; musl does not implement it.
To keep musl support, send via the `rt_tgsigqueueinfo(2)` syscall directly —
it is the kernel primitive both glibc and musl expose via `syscall(...)`:

```cpp
#include <sys/syscall.h>
#include <linux/signalfd.h>   // siginfo_t

static int tg_sigqueue_thread(pid_t tgid, pid_t tid, int sig, void* cookie) {
    siginfo_t si = {};
    si.si_signo = sig;
    si.si_code  = SI_QUEUE;          // must be < 0 to be accepted by kernel
    si.si_value.sival_ptr = cookie;
    si.si_pid   = tgid;              // convention: sender's TGID
    si.si_uid   = getuid();
    return (int)syscall(SYS_rt_tgsigqueueinfo, tgid, tid, sig, &si);
}
```

The receiving handler then sees:
- `siginfo->si_code == SI_QUEUE`
- `siginfo->si_value.sival_ptr == WALLCLOCK_COOKIE`

The kernel rejects any positive `si_code` from userspace (reserved for
kernel-generated signals), so this is safe.

### Handler gate (common helper)

```cpp
// os.h
bool OS::isOwnTimerSignal(siginfo_t* si, void* expected_cookie);   // SI_TIMER + cookie
bool OS::isOwnQueuedSignal(siginfo_t* si, void* expected_cookie);  // SI_QUEUE + cookie
int  OS::queueSignalToThread(pid_t tid, int sig, void* cookie);    // rt_tgsigqueueinfo wrapper
void OS::forwardForeignSignal(int signo, siginfo_t* si, void* uctx);
```

Handler skeleton:

```cpp
void Engine::signalHandler(int signo, siginfo_t* si, void* uctx) {
    if (!OS::isOwnTimerSignal(si, ENGINE_COOKIE)) {
        Counters::increment(ENGINE_SIGNAL_FOREIGN);
        OS::forwardForeignSignal(signo, si, uctx);
        return;
    }
    Counters::increment(ENGINE_SIGNAL_OWN);
    // existing handler body
}
```

### Foreign-signal forwarding

Must preserve correctness for other libraries sharing the signal (e.g. Go's
`runtime.sighandler`). Store the previous `sigaction` at install time and
forward via:

```cpp
if (prev.sa_flags & SA_SIGINFO) {
    prev.sa_sigaction(signo, si, uctx);
} else if (prev.sa_handler != SIG_DFL && prev.sa_handler != SIG_IGN) {
    prev.sa_handler(signo);
}
// SIG_DFL / SIG_IGN: drop
```

`OS::installSignalHandler` already captures this via the `oldact` out-parameter
of `sigaction` — just need to make it retrievable by signal number.

## Implementation steps

1. **`os.h` / `os_linux.cpp`**: add the three helper functions + previous-action
   storage keyed by signal number.
2. **`ctimer_linux.cpp`**: set `sev.sigev_value.sival_ptr = CPU_COOKIE` in the
   `timer_create` call; add origin gate at top of `signalHandler` (current
   line 145).
3. **`itimer.cpp`**: left unchanged — see scope note. Callers who need the
   origin check must configure the profiler to use CTimer (the default).
4. **`wallClock.cpp` + `os_linux.cpp`**:
   - Replace the current `OS::sendSignalToThread(tid, SIGVTALRM)` implementation
     (uses `tgkill` under the hood) with `OS::queueSignalToThread(tid,
     SIGVTALRM, WALLCLOCK_COOKIE)` which invokes `rt_tgsigqueueinfo`
     directly — portable across glibc and musl.
   - Add `SI_QUEUE` + `WALLCLOCK_COOKIE` gate in
     `WallClockASGCT::sharedSignalHandler` (current line 52) and the JVMTI
     variant. Forward on mismatch.
5. **`counters.h`**: add `CPU_SIGNAL_FOREIGN` / `CPU_SIGNAL_OWN` and
   `WALLCLOCK_SIGNAL_FOREIGN` / `WALLCLOCK_SIGNAL_OWN` counters.
6. **Feature flag**: gate the whole change behind `DDPROF_SIGNAL_ORIGIN_CHECK`
   (default ON) so it can be disabled if a regression emerges.

## Testing

1. **Unit tests** (per engine):
   - CPU: `timer_create` + `timer_settime` with `CPU_COOKIE` → assert `OWN`
     counter increments.
   - CPU: `setitimer(ITIMER_PROF)` → assert `FOREIGN` counter increments and
     signal is forwarded.
   - CPU: `raise(SIGPROF)` (SI_USER, no cookie) → assert `FOREIGN`.
   - Wallclock: `rt_tgsigqueueinfo(..., WALLCLOCK_COOKIE)` → assert `OWN`.
   - Wallclock: `tgkill(SIGVTALRM)` from another thread (no cookie) → assert
     `FOREIGN` and forwarded.
   - Wallclock: `rt_tgsigqueueinfo` with a foreign cookie → assert `FOREIGN`.
   - Musl build: confirm `rt_tgsigqueueinfo` path compiles and signals are
     delivered with correct `si_code` / `si_value`.
2. **Integration**: a test process that installs `setitimer(ITIMER_PROF)`
   alongside ddprof; verify ddprof samples are all attributed to registered
   threads (none from kernel-selected pre-existing threads).
3. **Regression**: reproduce the trivyjni scenario — load a Go-cgo lib that
   calls `profiler.Start(CPUProfile)`, run with ddprof active, confirm no
   lockup and no ddprof samples from Go-runtime threads that weren't explicitly
   registered.

## Metrics to watch post-deploy

- `CPU_SIGNAL_FOREIGN > 0` on services with Go cgo + dd-trace-go CPU profiler
  → confirms the fix is discriminating.
- `CPU_SIGNAL_OWN` unchanged vs. pre-fix baseline → confirms no false negatives.
- `WALLCLOCK_SIGNAL_OWN` unchanged vs. pre-fix baseline → confirms the
  `rt_tgsigqueueinfo` migration preserves delivery.
- `WALLCLOCK_SIGNAL_FOREIGN` should be 0 under normal conditions; non-zero
  indicates another in-process sender or external `sigqueue` to us.
- P99 request latency on trivy-affected services → should lose the lockup tail.

## What this does NOT fix

- SIGSEGV on pre-existing threads touching a not-yet-allocated `thread_local`
  for the first time (separate audit — need to enumerate profiler-owned
  `thread_local`s and either eliminate, make allocation-free, or pre-touch at
  registration).
- If Go ever adds a `SIGEV_SIGNAL`-targeted `SIGPROF` with its own sival →
  our cookie is non-null and distinct, so it is still filtered.
