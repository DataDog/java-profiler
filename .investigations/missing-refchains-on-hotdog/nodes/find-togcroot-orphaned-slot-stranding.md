---
id: find-togcroot-orphaned-slot-stranding
type: finding
status: fixed
depends_on: [q-togcroot-acceptance-paths, find-canary-lane-backoff-design]
related: [find-per-tid-qualification-design, find-leak-tag-pool-implementation]
tags: [fix, root-cause, canary, slots, flakiness, NEW-THIS-SESSION]
created: 20260901
updated: 20260901
---

# ToGcRoot failure root cause: discovered instances stranded when the candidate ages out of the poll list

Answers q-togcroot-acceptance-paths. The 124-pass mystery was NOT pass
starvation - it was slot stranding.

## The failure mechanism (log-proven, togcroot4 = failing run)

- Candidate ChainLink (klass_id=4, both id spaces agree) admitted into
  slot 0 at the first poll; qualifies via the 15-epoch seeded ramp only.
- The walk is slow: 66 of 124 passes admit ZERO edges; only 8 of 69,001
  ChainLinks are ever admitted (the elementData expansion admits its
  first 8 children, budget truncates mid-array, and the holder is never
  re-walked - the leak-accumulation fanout ranking is drowned by noise
  parents: 97k edges under noise klasses vs the real holder's fanout 8;
  all 821 Tier-2 selections went to noise, fanouts up to 56,329).
- The seeded ramp ages out of the ring at ring_fill=22 (slope decays to
  ~0.5, consecutive_positive resets to 0, line 32028) - klass 4 never
  returns in selectLeakCandidates() again (199 zero-candidate polls).
- The 8 discoveries are recorded the pass AFTER the drop-out (line
  50654, discoveredCounts=[8,...] for the remaining 116 passes) - but
  the discovered-chain loop iterates only the CURRENT poll's
  candidates. The slot persists by design ("can still be found there")
  but NOTHING ever read it again. No chain is built -> test fails after
  grace. Green runs = crawl lucky enough to discover while the seeds
  still held.

## Fix 1 (user-picked "1"): slot-driven chain building (load-bearing)

buildDiscoveredInstanceChains(klass_id, search_gen) extracted from
pollWatchedTargets' discovered loop; two call sites: the per-poll-
candidate loop (fresh chains for still-qualifying klasses) + an orphan
sweep over persistent slots absent from the current poll's candidates
(idempotent via the source_search_ns cache check; skip still-qualifying
slots to keep log volume unchanged). gtest
OrphanedSlotBuildsDiscoveredChainsAfterCandidateDropsOut; 551 green.
VERIFIED: full slow suite green twice consecutively at load 28.7 and
53 (was failing at load 3).

## Fix 2 (user-picked "then 2"): persistent allocator thread

One "togcroot-leak-allocator" thread reused across all 16 rounds;
tid seeds use its tid so seeds and real folds agree. HONEST CAVEAT: the
candidate STILL ages out mid-run in the verified green run (54
zero-candidate polls, 52 sweep firings) - shared-JVM GC-epoch noise
resets consecutive_positive, so sustained organic qualification is
inherently fragile; fix 1 remains the guarantee. Improvement of fix 2
is the active thread (see STATE.md).

## Fix 2 improved: seed-magnitude cliff (verified)

The residual aging-out was a SEED artifact, not epoch noise: the seeds
planted epoch*10 (10..150) in the same 30-slot ring the organic
generation-count ramp (+1/epoch, values 1..15 by test end) later fills;
when real samples displaced the seeded tail, hasQualifyingGrowth()'s
third-window slope went NEGATIVE (-20..-40) and consecutive_positive
never recovered - a "transition cliff". Rescaled the seeds to the
organic ramp's own magnitude (count = epoch, tid counts = epoch): the
ring series becomes [1..15, 1, 2, 3, ...] and every third-window pairing
across the transition stays positive - consecutive_positive grew
organically to 19 through ring_fill 28, zero candidate drop-outs
(zeroCands 54 -> 2), zero negative slopes, chains built by the ordinary
per-poll path, the orphan sweep UNUSED (pure safety net, as designed).
Two incidental finds: (a) the fix-2 test code had a compile-scope bug
(allocator referenced from finally while declared inside try) and the
two earlier "fix 2 verified" suite runs had executed STALE classes
(Gradle testSlowDebug UP-TO-DATE quirk) - fix 2 only actually executed
after the hoist + --rerun; fix 1's verification stands (native code was
in those runs). (b) the correlation scenario's seeds grow unboundedly
per round (hysteresisEpoch++ with epoch*10) so they never cliff - no
change needed there. Suite green post-fix at load 9-15 and 28-53; the
single correlation-test failure en route was the known 4-crawl-pass
knife-edge at load 31 (green on rerun with identical code).

## Code landmarks

buildDiscoveredInstanceChains in referenceChains.cpp (~4690, before
recordDiscoveredInstance); orphan sweep in pollWatchedTargets (after
the per-candidate loop, "Orphan fix" comment); declaration in
referenceChains.h next to recordDiscoveredInstance; gtest at the
PollWatchedTargetsTest fixture's tail.
