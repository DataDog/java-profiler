# How reference-chain hunting decides when to run and when to back off

*A guided tour of the signals in `ReferenceChainTracker` (`referenceChains.cpp`/`.h`), for
readers with no prior context on this subsystem.*

## 1. What problem this is solving

Java heaps leak. When they do, the useful question isn't "how big is the heap" — it's
*"what is holding onto these objects and refusing to let go?"* Answering that means
walking live references backwards from a suspect object to a GC root, i.e. reconstructing
a **reference chain**.

The obstacle: walking the heap graph (JVMTI's `FollowReferences`/`IterateThroughHeap`)
requires the JVM to stop every thread at a safepoint — a Stop-The-World (STW) pause, the
same kind a GC pause is. A profiler that stops the world to investigate a leak is
trading one problem for another. So the whole design of this subsystem is really an
answer to one question:

> **How do we get a useful heap walk without stopping the world for longer, or more
> often, than the leak justifies?**

Everything below is the machinery that answers that question — split into two halves:
*when should the next slice of walking happen* (triggering), and *how big/frequent
should that slice be allowed to get* (pacing/pausing).

## 2. The core trick: one long pause becomes many short ones

A single "walk the whole reachable heap and find the chain" pass could take seconds on a
large heap — an unacceptable pause. Instead, this subsystem does **bounded, resumable
BFS**: each *pass* only visits a limited number of objects (a *budget*), remembers where
it left off using JVMTI object tags, and picks the walk back up on the next pass. So a
"search" for a leak's chain is really a sequence of many short passes, each its own small
safepoint, spread out over time.

This reframes the whole design problem from "avoid the pause" (impossible — see §3) to
"decide, pass by pass, whether *now* is a good time to spend one of these small pauses,
and how big it should be."

## 3. Why GC callbacks can only ever be a *signal*, never the *work*

The natural instinct: "GC just ran, the heap just changed — hook the GC callback and do
the walk right there, for free, since the VM is already stopped."

This doesn't work, and the reason is worth understanding because it shapes the rest of
the design. JVMTI's spec is explicit: inside `GarbageCollectionStart`/
`GarbageCollectionFinish`, an agent may call only the **Memory Management** category
(`Allocate`/`Deallocate`). Everything a heap walk needs — `SetTag`, `GetTag`,
`GetObjectsWithTags`, `FollowReferences`, `IterateThroughHeap` — is in the **Heap**
category, which is explicitly *not* on that allow-list. Calling any of them from inside
the GC callback is exactly what the restriction forbids (confirmed against
`GCCallbackGuard` in `referenceChains.cpp`, which asserts this in debug builds).

So the GC callback can do exactly one cheap, legal thing: bump an atomic counter.

```cpp
void ReferenceChainTracker::onGCFinish() {
  GCCallbackGuard guard;               // "we are inside the forbidden window"
  atomicIncRelaxed(_gc_finish_epoch, (u64)1);
}
```

That's it. No walk, no tag calls, nothing heap-related — just "a GC finished, epoch N".
This is the first, and most important, idea to internalize:

> **A GC callback is a doorbell, not a worker.** It tells a separate thread "something
> happened, go check if it's worth acting on" — it never does the acting itself.

The actual walk happens later, on a dedicated background thread, deliberately outside
the safepoint the GC callback fired inside. That thread calling `FollowReferences`
triggers its *own*, independent safepoint — the GC's pause and the walk's pause are two
separate STW events, not one shared one. (An earlier version of this design hoped to
"ride" the GC's own pause for free; that turned out to be architecturally impossible
without reaching into unversioned HotSpot internals — see
`doc/architecture/LiveHeapReferenceChains.md`'s Triggering section for the full
investigation.)

## 4. The scheduling loop: cadence + epoch, not "run on every GC"

The background thread (`threadLoop()`) wakes roughly once a second and asks
`shouldRunPass()`: "should I spend a pass right now?" Two independent signals feed that
decision:

1. **The GC-finish epoch changed** since the last pass. A GC just happened — the heap
   graph likely moved, so a fresh pass is probably worth its cost.
2. **A fixed cadence has elapsed** since the last pass, even with no new GC. Two distinct
   roles, easy to conflate:
   - For a **workload with no/rare GCs** it is the fallback the naive reader expects —
     without it, the search would stall forever waiting for a signal that never comes.
   - For an **in-progress search** it is the *crawl's pacing knob*, not a signal re-check:
     passes between GCs are the only thing that drains the search's own frontier backlog
     (its "found but not yet expanded" objects). GC time does not advance the crawl —
     pass time does — so a RUNNING search legitimately runs cadence-driven passes with
     zero new signal, and the pause-time controller (§7) widens/narrows exactly this
     cadence. The only genuinely stale re-check is the terminal state's cheap
     restart-gate re-evaluation (§5), two atomic loads, deliberately kept unconditional.

```cpp
u64 gc_finish_epoch = gcFinishEpoch();
if (gc_finish_epoch != _last_pass_gc_finish_epoch) {
  return true;   // "a GC just happened, a pass may be worth running soon"
}
...
return cadence_elapsed;
```

Notice what's deliberately *not* here: the loop does **not** wake up early on every GC.
`onGCFinish()` only bumps a counter — it never calls `pthread_kill()` to interrupt the
sleeping thread (the only early-wake signal is shutdown's abort, §10). Why swallow the
up-to-~1s latency instead of reacting instantly? Because under a GC-heavy workload,
waking on *every* GC would collapse the loop's cadence down to GC frequency — each wake
is a full iteration of scheduling logic, not free. The design accepts "at most ~1s of
extra latency" in exchange for not turning a GC storm into a scheduling storm. This is
a recurring theme in this subsystem: **every signal is deliberately made cheap to check
and expensive to over-react to.**

One caveat the epoch trigger carries: it is an *unconditional* bypass — while it is
set, no cadence check applies. Minor young GCs bump the epoch as readily as majors, so
once the adaptive cadence (§7) has shrunk to its floor, a workload that GCs more often
than the wake interval effectively drives one pass per wake, at up to GC frequency.
That is bounded and acceptable for the crawl lanes (each pass is pause-budgeted by the
PID controller); the one lane that needs a rate bound of its own — the canary chase —
gets one explicitly (§8).

## 5. Not every wake actually walks: the leak-signal gate

Waking up and checking cheap counters is fine to do often. Actually walking the heap
costs real STW time, so before a **brand-new search** (or a **restart** of one that
finished) is allowed to begin, a second, independent gate applies:
`LivenessTracker`'s population-trend signal — "is there currently a class whose live
object count looks like it's growing without bound?" (`hasLeakSignal()`).

```cpp
bool ReferenceChainTracker::hasLeakSignal() {
  if (!LivenessTracker::instance()->gcGenerationsEnabled()) {
    return true;   // no trend signal available at all -> don't gate on it
  }
  ...
  int n = LivenessTracker::instance()->selectLeakCandidates(probe, 1);
  return n > 0;
}
```

This matters because a full-heap BFS is expensive relative to a targeted one, and there's
no point paying that cost speculatively, with nothing to justify it. If the leak-tracking
feature isn't even enabled, this reduces to "always true" — the walk runs unconditionally,
exactly as a simpler standalone version of this feature would.

Once a *search is already running*, though, this leak-signal gate is deliberately **not**
re-applied per pass — an in-progress search's own frontier (its list of "found but not yet
expanded" objects) is allowed to keep converging pass after pass regardless of whether a
fresh leak candidate happens to be visible right now. Gating an already-running search on
"is there a candidate this instant" would stall its progress for no good reason; the gate's
job is to decide whether *starting* new expensive work is worth it, not to second-guess
work already committed to.

The same "a potential leak is currently detected" signal also raises *liveness tracking
fidelity* itself: once candidate selection has fired, the qualifying tids' allocations are
admitted to the tracking table at 100% instead of the configured live-samples ratio
(default 10% — a 90% probabilistic drop that thins small per-(klass, tid) populations;
`LivenessTracker::admitForTracking()`). The raise is bounded by the candidate threads'
own allocation rate, not the process's whole allocation rate, so the tracking table's
cost scales with the leak's own threads; and it is refreshed — and cleared — poll by poll
with the candidate selection, so it never outlives the chase. The OOM urgency ramp
(§9) raises admission to 100% for *all* allocations for the same reason it drops every
pacing rule: the process is expected to die soon, and maximizing what the last chapter
captures outweighs the tracking table's transient volume.

## 6. Paying for it: the "pain budget" leaky bucket

Even with a real leak signal, restarting a full search back-to-back forever would be
its own kind of runaway cost. The safety valve here is a **leaky bucket over cost**, not
over time — `PainBudget` (`painBudget.h`):

```cpp
// spend(): "that last search cost N milliseconds of wall-clock work"
// canStartNow(): "has that debt drained back to ~0 yet, at refill_rate?"
```

The intuition: if a search finished *cheaply*, it can restart again almost immediately.
If it was *expensive*, the next restart has to wait proportionally longer. This is a much
better model than a fixed cooldown timer, because "how expensive was the last search"
is exactly the thing worth reacting to — a fixed cooldown would either be too
conservative after a cheap search or too permissive after an expensive one.

`canAffordNewSearch()` combines both gates from §5–6: the leak signal has to say "worth
it" *and* the pain budget has to say "affordable" before a new/restarted search is
allowed to begin.

## 7. Self-tuning the pause itself: a PID controller on pause time

So far: *when* to run a pass. Now: *how expensive should that pass be allowed to get?*

Each pass has a target STW duration (`_pause_target_ms` — an operator-configured ceiling,
e.g. "no single pass should take more than N ms"). After every pass, the tracker measures
how long it actually took and feeds that into a small PID controller
(`_pause_pid.compute()`), which nudges the *per-pass budget* — how many objects the next
pass is allowed to visit — up or down:

- Pass ran comfortably under target → budget can grow a bit (there's headroom).
- Pass ran over target → budget shrinks, so the *next* pass is smaller and faster.

This is the same self-correcting idea used elsewhere in this profiler for sampling rates
(`ObjectSampler`, `MallocTracer`) — measure the actual cost, compare to a target, adjust
the knob that controls the next iteration's cost, repeat. It means the operator doesn't
have to hand-tune a "safe" fixed budget for every heap size and object graph shape; the
controller finds it empirically, pass by pass.

There's a second knob the same controller feeds: if the budget is already at its floor
and *still* over target, that's a sign the real problem isn't "how much work per pass" —
it's "passes are happening too close together." In that case the controller widens the
*cadence* (the sleep interval between passes) instead. Conversely, if a pass finishes
comfortably under target even at the configured budget ceiling, the idle cadence is
shortened — there's slack to use it to converge faster. Either way, the same measured
signal (pass duration vs. target) drives both "how much work per pass" and "how often to
even try."

There's also a small "savings account" on top of this (budget-borrowing): a *sustained*
run of comfortably-under-target passes slowly raises the ceiling itself, not just the
budget inside it — but a single pass that isn't comfortably under target revokes that
extra headroom immediately. The asymmetry is deliberate: earning slack should take
sustained good behavior; losing it should be instant, so a run of easy passes can never
turn into an excuse for one expensive one.

## 8. When "wait for the next cadence tick" isn't good enough: canary mode

The scheduling described in §4–7 assumes a slow, whole-heap background search. But
sometimes there's a much sharper signal available: `LivenessTracker` has already flagged
*specific* suspect objects (a small, pre-tagged "canary" set) worth confirming quickly. In
that mode:

```cpp
bool canary_active = _candidate_count > 0 &&
    __builtin_popcountll(_candidate_found_bits) < (u64)_candidate_count;
if (canary_active) {
  return true;   // run the next pass immediately, no cadence wait
}
```

While a canary search is active, cadence is bypassed — passes run back-to-back *while the
chase is fresh or making candidate progress*, because the PID controller (§7) is already
keeping each individual pass's pause small, and a chase that is genuinely close to its
target should resolve in a handful of passes.

Back-to-back-forever, however, is exactly the wrong promise for the failure mode this
feature actually meets in production: a candidate the crawl cannot reach soon (a leak
holder buried behind a deep frontier backlog — the coverage lottery inherent to an
external JVMTI agent with no reverse-edge primitive). Measured live on a production-like
analyzer pod: one such un-findable candidate held the chase open for 32 minutes at ~88
passes/min — a full core of engine work — because the bypass applied unconditionally and
the loop skips its sleep whenever a pass will run. "Well under 20ms per 60s recording"
is only ever true for *findable* candidates.

So the canary lane carries its own rate bound — a **progress-driven, work-scaled
exponential backoff**. The inter-pass spacing is a *multiple of the measured cost of a
pass itself* (an EMA of each pass's wall duration), not a fixed wall-clock constant:
- Every pass that makes candidate progress (a candidate found, or a new candidate
  admitted) resets the spacing multiplier to 1 — back-to-back. At multiplier 1 the
  next pass starts as soon as the last one ended, which is harmless by construction
  for a cheap pass, and exactly the fast-resolution burst a chase that is genuinely
  close should get.
- Every pass with *no* candidate progress doubles the multiplier, capped at 16. A
  permanently stuck chase therefore settles at one pass per 16 × (its own cost) —
  it keeps ticking indefinitely (abandonment is a separate, frontier-aware detector's
  job, below), but its steady burn is structurally bounded to ~1/16 of a core on pass
  work, *whatever that work is*.
- The work-scaling is the point: a fixed cap only binds when it exceeds the pass's own
  duration — the production pod's passes ran 0.7–4s, so a 1s cap would have changed
  nothing at all (the loop is work-bound, never sleep-bound, when the pass exceeds the
  cap), while the same 1s cap starved a genuinely reachable deep chase whose passes
  cost milliseconds. Scaling to the measured cost gives the expensive-pod chase a real
  bound and the cheap-but-deep chase its density from the same law.
- The GC-epoch trigger deliberately does **not** bypass the backoff: a GC-heavy workload
  bumps the epoch on virtually every wake, so letting GCs override the spacing would make
  the backoff unreachable on exactly the deployments that burn the most.
- The OOM urgency ramp (§9) overrides it entirely — imminent OOM remains the one regime
  where the chase burns budget back-to-back.

The pain-budget refill rate is raised 100x while a chase is open, but note what that
means now: **not** a rate control (the backoff is the rate bound) — just a double-throttle
guard, so the conservative base refill rate tuned for the ordinary ~1 pass/s crawl doesn't
starve a chase the backoff has already paced. The earlier covering-vs-emergency refill
distinction existed to feed the unbounded back-to-back mode and is gone with it.

## 9. The panic button: ramping up as OOM approaches

All of the above optimizes for "acceptable background cost most of the time." But if
`LivenessTracker` projects the heap is genuinely on a collision course with
`OutOfMemoryError` within the next ~30 minutes (`secondsToOOM()`), "acceptable background
cost" is the wrong objective — the process might not survive long enough for a leisurely
search to finish. So there's a third mode: an **urgency ramp**.

As projected time-to-OOM shrinks from 30 minutes toward zero, the pause-time target and
the pass cadence both ramp *exponentially* toward much more aggressive ceilings:

```cpp
double x = 1.0 - seconds_to_oom / OOM_RAMP_START_S;  // 0 at 30min out, 1 at OOM
target_ms = pause_target * pow(URGENT_PAUSE_TARGET_MS / pause_target, x);
cadence_ns = pow(URGENT_CADENCE_NS / PASS_CADENCE_NS, x) * PASS_CADENCE_NS;
```

The reasoning behind exponential (rather than linear) ramping: at 30 minutes out, the
situation still might resolve itself (a GC frees the suspect objects, the trend reverses)
— stay cheap. In the last seconds before OOM, the process is likely to die anyway, so it's
worth spending far more of the pause-time budget to collect a usable chain *before that
happens* than to protect a latency budget for a process that may not be there to benefit
from it. Held flat-out cheap the whole time, this urgency signal would arrive too late to
matter; held aggressive the whole time, it would waste budget on every one of the many
false alarms a rising trend that later reverses produces.

Two more details make this practical rather than flappy:

- **Hysteresis, not a bare threshold.** `isUrgent()` *latches* on when
  time-to-OOM drops below a threshold, and only *releases* after several consecutive
  observations comfortably clear of a separate (higher) release bar. A single noisy
  reading crossing back and forth across one threshold would otherwise thrash the ramp
  on and off every second.
- **One search per urgency episode.** Once an urgent episode has spent its one
  authorized search, further ticks within the same episode don't keep tearing down and
  restarting it from scratch — the per-candidate probe (§5) remains the only trigger
  until the episode actually clears.

## 10. Stopping mid-pass: the abort path

Everything above is about *starting* passes thoughtfully. There's also a clean way to
*stop* one that's already in flight — needed when the profiler itself is shutting down
(or a test needs to reset state) while a `FollowReferences` call is still blocked inside
the JVM.

```cpp
_abort_pass_requested.store(true, std::memory_order_relaxed);
pthread_kill(_thread, WAKEUP_SIGNAL);   // interrupts a sleeping thread promptly
```

The callback JVMTI invokes for each visited object checks this flag and returns an abort
code the moment it sees it set — since nothing outside the JVM can interrupt a call
already inside `FollowReferences`, the flag has to be checked *from inside* the callback
JVMTI itself is driving. `pthread_kill` with a no-op-handler signal only helps the *other*
common case — a thread parked in `OS::sleep()` between passes — wake up promptly instead
of waiting out the rest of its interval.

## 11. Putting it together

| Question | Signal | Where |
|---|---|---|
| Did the heap graph just change? | GC-finish epoch bump | `onGCFinish()` → `shouldRunPass()` |
| No GC signal — is it time anyway? | Fixed/adaptive cadence elapsed | `shouldRunPass()` |
| Is a *new* search worth starting at all? | LivenessTracker population trend | `hasLeakSignal()` |
| Can we afford to spend that cost right now? | Pain-budget leaky bucket | `canAffordNewSearch()` |
| How big/frequent should passes be, steady-state? | PID controller on measured pause time | `updatePacing()` |
| Are we chasing specific known suspects? | Canary candidate set + progress-driven backoff | `canary_active` bypass + work-scaled `_canary_backoff_mult` |
| Is OOM close enough to abandon caution? | secondsToOOM() latch/release | urgency ramp in `threadLoop()` |
| Need to stop a pass already in flight? | Abort flag + wakeup signal | `_abort_pass_requested` |

The unifying idea across all eight mechanisms: **every trigger is a cheap check, and
every response is proportional to real, measured cost** — never a fixed guess. GC
callbacks stay legal by doing nothing but incrementing a counter. Whether to search at
all is gated on an independent leak-trend signal, not "because a GC happened." Whether a
search can *restart* is gated on how expensive it actually was last time, not a flat
cooldown. How big a pass gets is tuned from its own measured pause time, not a static
config value. And the one scenario where none of that caution applies — imminent OOM — is
its own explicitly separate, hysteretic escalation path, not a tweak to the steady-state
knobs.

That's what makes several short, adaptively-sized pauses a genuinely better trade than
one long one: the *decision* of when to pay each of those small costs is never blind —
it's always backed by a signal that says this particular pause is likely to be worth it.
