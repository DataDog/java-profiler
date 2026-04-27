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
| `kill` (cross-process/thread) | `SI_USER` (0) | none → forward |
| `raise` / `tgkill` / `pthread_kill` (foreign) | `SI_TKILL` (-6) | none → untrusted, must forward |
| `sigqueue` from another process | `SI_QUEUE` (-1) + foreign cookie | cookie mismatch → forward |

### Cookie strategy

Cookies live in `signalCookie.h` and are the addresses of private static tag
variables — unique per shared-library image, forgery-resistant against
in-process attackers who would have to read the DSO's symbols to guess a
valid cookie:

```cpp
namespace SignalCookie {
    namespace detail {
        inline char cpu_tag;
        inline char wallclock_tag;
    }
    inline void* cpu()       { return &detail::cpu_tag; }
    inline void* wallclock() { return &detail::wallclock_tag; }
}
```

One cookie for CTimer (the only CPU engine that can carry a cookie), one for
wallclock. Rationale for wallclock needing a cookie: `SI_TKILL` +
`si_pid == getpid()` is **not** sufficient — `si_pid` for `SI_TKILL` is the
sending process's PID, and all threads in our process share the same PID, so
that check accepts any in-process `tgkill` of SIGVTALRM (including from other
libraries). Real isolation requires a payload.

Earlier iterations used magic numbers (`reinterpret_cast<void*>(0xDDDD01)`).
Symbol-address cookies are strictly stronger: they cannot collide with a
legitimate pointer value from third-party code (the tag lives in a fresh
DSO-private BSS slot), and they are resistant to an attacker who only knows
the constants published in open-source headers.

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
bool OS::shouldProcessSignal(siginfo_t* si, int expected_si_code, void* expected_cookie);
bool OS::sendSignalWithCookie(int thread_id, int signo, void* cookie);   // rt_tgsigqueueinfo wrapper
void OS::forwardForeignSignal(int signo, siginfo_t* si, void* uctx);
```

Handler skeleton:

```cpp
void Engine::signalHandler(int signo, siginfo_t* si, void* uctx) {
    if (!OS::shouldProcessSignal(si, SI_TIMER, ENGINE_COOKIE)) {
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
// SIG_DFL: drop (reproducing termination on every foreign signal is worse than ignoring it)
// SIG_IGN: drop (matches kernel ignore semantics)
```

`OS::installSignalHandler` already captures this via the `oldact` out-parameter
of `sigaction` — just need to make it retrievable by signal number.

#### sa_mask chaining — opt-in via env var

By default, chained handlers run under whatever signal mask the profiler's
handler was given by the kernel (which has `signo` blocked because we install
without `SA_NODEFER`). This is the **fast chain path**: no mask-setup syscalls,
~24 ns pure function cost, ~37 ns end-to-end including signal delivery
(measurements from `signalOrigin_bench.cpp` on Linux x86_64).

Applying `prev.sa_mask` faithfully — so the chained handler sees the same
masked environment the kernel would have given it under normal delivery —
requires two raw `rt_sigprocmask` syscalls (`SIG_BLOCK` then `SIG_SETMASK`).
On modern Linux this measures ~1 µs per foreign signal, ~30% per-signal
end-to-end overhead. (`pthread_sigmask` is NOT used: it would call libc internals
and is not async-signal-safe on all configurations.)

Because the realistic foreign-signal sources this plan targets
(Go's `ITIMER_PROF`, `raise()`, most `tgkill` callers) do not rely on
`sa_mask` for correctness, we take the fast path by default and expose an
env-var escape hatch:

| Env var value | Behavior |
|---|---|
| `DDPROF_FORWARD_APPLY_SIGMASK=1` (or `true` / `on` / `yes`) | Slow path: `rt_sigprocmask` block+restore around the chained call |
| unset / any other value | Fast path (default): no mask syscalls; chained handler runs with only `signo` blocked |

Enable the slow path when profiling exposes a chained handler that depends
on the kernel's normal masked environment — e.g. a crash handler installed
before the profiler that expects other fatal signals blocked during its run.

SIGSEGV / SIGBUS forwarding is not affected by this flag — those use the
existing SafeAccess PC-range discrimination, not `forwardForeignSignal`.

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
     (uses `tgkill` under the hood) with `OS::sendSignalWithCookie(tid,
     SIGVTALRM, WALLCLOCK_COOKIE)` which invokes `rt_tgsigqueueinfo`
     directly — portable across glibc and musl.
   - Add `SI_QUEUE` + `WALLCLOCK_COOKIE` gate in
     `WallClockASGCT::sharedSignalHandler` (current line 52). Forward on mismatch.
     (J9WallClock uses JVMTI GetAllStackTracesExtended polling — no signal handler — and is out of scope)
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
   - CPU: `raise(SIGPROF)` (SI_TKILL on glibc/musl, no cookie) → assert `FOREIGN`.
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
