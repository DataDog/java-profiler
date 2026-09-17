---
id: find-tier1-tail-starvation
type: root-cause
status: confirmed
depends_on: [find-anchor-tail-starvation, ev-leaktag-onpod-round14-results]
related: [find-fresh-lane-verification]
tags: [root-cause, referenceChains, tier-1, tail-starvation, containers, round-14, NEW-THIS-SESSION]
created: 20260915
updated: 20260916
---

# Find: tier-1 tail starvation (round-15 diagnosis — admitted-at-tail container never walked)

Parent: find-anchor-tail-starvation (round 13, same invariant at index
scale). Round 14 shrank the cohort (containers 1633) but the invariant
`coverage = rate × lifetime ≥ cohort` STILL fails at tier scale, now with
cleaner measured numbers.

## The mechanism (all measured on pod rz992, round-14 build, 20:22-20:53Z —
raw numbers in ev-leaktag-onpod-round14-results.md, deploy + design in
ev-leaktag-onpod-round14.md)

1. Anchor index order = admission order; statics admit in SWEEP order =
   loaded-class order (app-partitioned, ProfileAnalyzer at 24627/33270).
2. The wrapper's holder class is late in the class list ⇒ the wrapper is
   admitted mid/late in whatever search is live when the sweep crosses it
   (observed: pass 43-44), landing at the anchor-index TAIL ⇒ container
   ordinal ~LAST (1634 of 1633).
3. Tier-1 fair cursor walks 16/pass from ordinal 0 ⇒ wrapper walked at
   admission_pass + ~102.
4. Search lifetimes are 44-75 passes (frontier fills 2.5-7.5k/pass — noise
   seeding ~650 inserts/min + sweep admits + expansion; cap 250k abandon).
5. ⇒ wrapper walk owed at pass ~102+ > lifetime 44-75 ⇒ **deterministic
   miss by 30-50 passes**, every search, every lap.
6. Compounder: every search today is a CANARY CHASE (candidate = the [B
   leak class, 0/1 found). The candidate is only "found" via a resolved
   chain, which needs the wrapper walk (see 5), so the chase can never
   succeed — while its exponential backoff (16×ema≈3s/pass) slows the
   passes that would reach the wrapper. Self-sustaining deadlock.

## Why round-14's own guarantee was insufficient

Round-14 guaranteed "walked within ceil(cohort/budget) passes OF ADMISSION"
(ceil(1633/16)=102) — the guarantee is correct as stated; the missing
assumption was that a search LIVES ≥ 102 passes after the wrapper's
admission. Round-13 measured ~190-pass lifetimes; round-14 observed 44-75
(the fill rate rose 2-5x: leak-accumulator seeding noise + faster sweep
admits). The scale invariant (lifetime × rate ≥ cohort) must be asserted
against the MEASURED lifetime, not the round-13 one — same lesson as the
circle review: measure the invariant whole, per deployment.

## Fix (round 15): fresh-admission priority

Walk anchors admitted since the last collector pass FIRST (newest-first),
at least the container-shaped ones. Admission at pass N ⇒ walk at N+1.
STW-neutral (same 16-walk budget, reordered). Breaks the deadlock
end-to-end: wrapper walk ⇒ subtree expansion admits leak-tagged chunks ⇒
chain resolves ⇒ canary candidate found ⇒ chase exits ⇒ event emitted.

Note: fresh-priority must not starve the fair tiers permanently — fresh
admits are bounded by the sweep's admit rate (~16-64/pass of containers),
so the fresh lane drains within a few passes and the fair cursors resume.
Shape-independent fresh-priority would flood the budget with fresh
String/other statics; prefer fresh+container (or fresh with shape lag:
classify-then-walk next pass).

## Secondary observations (record, don't fix now)

- Search lifetime regression driver candidates: seeding noise (fanout=1,
  round-13 node) ~10-20% of fill; the rest is sweep admits + expansion.
  If fresh-priority alone doesn't close the loop, the seeding noise is
  the next lever (also a round-13-documented correctness bug).
- reconcile classification log fires once per class per JVM; early-lap
  windows rotate out of the log buffer fast (67k lines ≈ 4 min) — capture
  with `kubectl logs -f` streams, not --since windows, for early-lap
  evidence. Buffer rotation burned ~20 min of round-14 verification time.
- Sweep gate: opens only while the loaded-class count changes (app loads
  lambdas in waves); cursor resets to 0 when count shrinks below cursor
  (lambda unloading) — laps complete in ~2-10 min during churn.
- Old-JVM debt-drain arithmetic sanity: PainBudget drains at exactly its
  spec rate (30ms/s at refill 0.03); the "slow drain" illusion was buffer
  window misestimation.
