---
id: find-refchains-log-flood-configurable
type: fix-verification
status: confirmed-pending-pod-verification
depends_on: [find-wrapper-demotion-self-parent, ev-leaktag-onpod-round16-results]
related: [find-round16-endgoal-verification, find-jvmti-heap-walk-stw-vmop]
tags: [observability, debug-logs, runtime-knob, rcDebugLevel, pod-safety, fix, NEW-THIS-SESSION]
created: 20260916
updated: 20260916
---

# Find: reference-chains log flood made runtime-configurable, silent by default (f70bcc454)

User need: keep hotdog running the DEBUG profiler build (TEST_LOG is
`#ifdef DEBUG`-only via common.h — that is why the pod floods at all)
but stop the reference-chains diagnostic logs from swamping the pod
("it will get killed sooner or later"). Deleting them would discard
what cracked rounds 12-16, so they are gated at a runtime level instead
(new header `rcDebugLevel.h`, included AFTER common.h by
referenceChains.cpp + livenessTracker.cpp; re-points TEST_LOG at a
level check and adds TEST_LOG_SUMMARY).

## Levels and tier rule

0 = SILENT (the new default — pod-safe with the same .so). 1 =
lifecycle/summary. 2 = full firehose. Tier rule, sized EMPIRICALLY from
the round-16 stream (3.1M lines/55min): **per-pass/per-poll outcomes
and state-machine transitions → 1; per-object/per-klass/per-entry inner
loops → 2.** The measured flood: auto-marks 1.2M (auto-marked chain
per instance per poll), selectLeakCandidates entries 490k,
trackLeakAccumulation 190k, heap admits 148k, sweep STATIC_FIELD 92k,
maybeUpgradeRootAttached 24k, resolveClassMap 23k, pushAtRisk 10k —
all level 2. Level 1 keeps: shouldRunPass/canary decisions, candidate
state machine, rotation_candidates (with self_edge_skips/quota_drops),
drain re-emitted, correlateAdmittedLeakTag, candidates-armed — est.
<300 lines/min. 49 RC + 11 liveness sites re-tiered to SUMMARY.

## Sources and the callback-context constraint

Env `DD_PROFILING_REFERENCE_CHAINS_DEBUG=N` at start; runtime override
WITHOUT restart: `echo N > /tmp/ddprof_root/refchains_debug_level`
(single digit; remove the file → fall back to env), re-checked ~1s TTL
from the RC threadLoop. JVMTI heap callbacks only READ the cached
atomic — the open/read never runs there (callbacks must not allocate;
the fprintf these lines already do in DEBUG builds is the tolerated
debug-build exception, but the knob adds nothing new there). Level
reported on the threadLoop-start line for confirmation. Flip from
outside the pod: `kubectl exec <pod> -c prof-analyzer -- sh -c 'echo 2
> /tmp/ddprof_root/refchains_debug_level'`.

## Two build/workflow lessons

1. **The gtest binary compiles the main sources WITHOUT DEBUG** —
   discovered when `#ifdef DEBUG`-only declarations failed the UT
   compile (the library TU built fine; only the test TU saw no
   declarations). So the level machinery is compiled UNCONDITIONALLY:
   in non-DEBUG builds nothing calls it (the macros are no-ops) and the
   gtest binary (non-DEBUG) can test it directly — RcDebugLevelTest
   (parse/read/refresh-env), suite 121/121.
2. **A multi-edit tool call rejected on one ambiguous anchor applies
   NOTHING (atomic)** — and re-applying only the remembered edit left
   the include + impl block silently missing, surfacing only as
   "undeclared identifier" compile errors far from the cause. After a
   rejected batch: re-apply EVERY edit, then grep that each landed
   (one `grep -n rcDebugLevel` would have shown the include missing).

## Pod verification (build f70bcc454, pod 289f8, JVM 96 min) — TWO escapes found and fixed

1. **Header escape (fixed 7aa68744b)**: 10 TEST_LOG call sites lived
   INLINE in referenceChains.h (buildChainEvent + buildCanaryChainEvent
   bodies) — compiled with common.h's ungated TEST_LOG because TUs
   including the header never see rcDebugLevel.h's macro redefinition
   (~130-1700/min of 'buildChainEvent false:' leaked at level 0).
   Fixed by moving both member functions out of line into the .cpp
   (buildChainEvent outcomes level 2; buildCanaryChainEvent outcomes
   level 1 — the chase's lifecycle, bounded by candidate count). Could
   NOT fix by including rcDebugLevel.h from referenceChains.h: that
   would re-point TEST_LOG TU-wide for javaApi.cpp/profiler.cpp/
   vmEntry.cpp (24 unrelated sites) — macro state is per-TU from the
   include point; header-inline bodies from headers included EARLIER
   (e.g. profiler.h) stay ungated regardless.
2. **Tick-cadence mis-tier (fixed 524c35325)**: live level-1 window
   measured ~2600/min — lines tiered "per poll" actually fire every
   ~250ms threadLoop tick (poll candidate state, selectLeakCandidates
   returning, noteSelected, tagLeakInstances summary,
   collectLeakAccumulation selected). 10 sites demoted to level 2;
   level 1 now = true transitions/bounded outcomes only (<500/min).
   LESSON: tier by measured firing cadence, not by the call site's
   intent — verify the tier empirically with a level-1 window before
   declaring it leave-on safe.

## Pod verification round 2 (build 524c35325, in-place JVM restart to pid_28570 at 12:09Z, same pod 289f8)

DEFAULT SILENCE VERIFIED: 0 reference-chains/LivenessTracker lines at
level 0 (3-min window; header escape gone). Remaining TEST_LOG ~300/min
is the .so unpacker's pre-existing 'Unpacking' lines - other subsystem,
out of scope. Two level-1 stragglers found + demoted (48c1e1c22):
'shouldRunPass held off by canary backoff mult' fires per ~100ms tick
EVALUATION (835/85s), and the collectLeakAccumulation... selected line
(4/s during rotation) - missed by the 524c35325 demotion because its
format string splits across two lines and the concatenation probe has a
quote-quote '''''' between the halves; when demoting, probe the line
AFTER the TEST_LOG_SUMMARY line, not just the concatenation.

The runtime flip ITSELF verified live: `echo 1 > file` → summary lines
within ~1s (no restart), rm → silent. Round-16 pipeline live on this
JVM: re-emitted=8, candidate[0] klass_id=10 ([B — ids differ per JVM),
self_edge_skips=26150, quota_drops=1644, fifo_size=161. CANARY STILL
0/1 (now 3 JVMs / hours; backoff 16, ~1 pass/3s). MOVING-TARGET
HYPOTHESIS REFUTED: level-2 window shows candidate[0] klass_id=6
tag=221704 needRefresh=0 — the SAME tag on 203 consecutive ticks (the
representative is stable, a plain object tag 221704, not a leak tag).
The representative is simply NEVER ADMITTED by any walk while pool
instances are — next-round diagnosis: catch a full manual-walk sweep
(level 2, the walked=48 truncated=0 pass) and check whether the
wrapper's subtree admits chunks, and which holder holds tag 221704
(cf. find-representative-changes-lose-canary for the refresh variant —
not this one). Walk machinery healthy on this JVM: full 48-anchor
sweeps completing untruncated, partial walks edges 198-3887 truncated=1,
self_edge_skips=5174, fresh lane active (fresh_tier=4 fresh_queue=324),
drain re-emitted=2. Remaining non-ours debug noise on the pod: ~180/min
'Unpacking' lines (the .so unpacker's pre-existing DEBUG logging).
