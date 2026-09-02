---
id: q-togcroot-acceptance-paths
type: question
status: open
depends_on: [find-canary-lane-backoff-design, find-default-live-samples-ratio-lottery]
related: [find-canary-continue-skips-discovered-instances, find-representative-changes-lose-canary, find-shared-deadline-starves-expand]
tags: [flakiness, tests, canary, pacing, open, NEW-THIS-SESSION]
created: 20260901
updated: 20260901
---

# ToGcRoot/UnboundedCache flakiness: multiple acceptance paths x canary pacing - what actually closes it?

The remaining intermittent slow-suite failures (ReferenceChainTrackingTest
shouldReconstructReferrerChainToGcRoot, sometimes UnboundedCacheLeak) are
NOT the live-samples-ratio lottery (fixed; the "representative
died/evicted" symptom is gone at :l:1.0) and are not purely
machine-load (latest failure at load ~3).

## The confusing data (all on the work-scaled backoff build)

- Green run (18:09, 10% ratio): PASS with only 13 passes, ZERO canary
  prunes - the ReferenceChain event arrived via a NON-canary path
  (discovered-instance/leak-tag machinery) without the marker chase
  ever resolving.
- Fail run (19:1x, :l:1.0, load 3): 124 passes, 101+ Tier-2 rotation
  selections, canary NEVER pruned, no chain within the window.
- Earlier fail runs (17:47-18:04, 10% ratio): ~114-200 passes, mostly
  zero-edge, same no-prune outcome.

## Candidate factors (untested)

1. The chase needs ~200 mostly-cheap rotation passes to lap to the
   marker's holder; work-scaled spacing = mult x EMA(pass wall), and
   the EMA is polluted by occasional ~300ms root-enum passes
   (ROOT_ENUM_MIN_INTERVAL gates them back in; pass wall includes the
   full root-enum phase), inflating spacing 10x exactly when the chase
   is otherwise cheap. Hypothesis: exclude root-enum passes from the
   EMA (or measure chase-pass cost separately).
2. Tier-2 selected the right-looking holders (fanout up to 1700,
   hundreds of selections) yet the marker was never pruned - is the
   marker rep's actual parent among the winning (leaf, parent-class)
   signatures? Needs a one-shot diagnostic tying a Tier-2 selection to
   the marker tag.
3. The 13-pass green run shows the acceptance can be met without the
   canary at all - which path served it, and why does it not serve it
   in the failing runs? (Discovered-instance gate? leak-tag
   interception ordering?)

## New data points (post admission-boost, still failing identically)

- The chase-phase admission boost (admitForTracking watched tids) is
  neutral on this failure, as expected (suite tests already run
  memory=64:l:1.0 so admission was 100% all along) - but it confirmed the
  chase machinery engages: noteSelectedCandidates published the
  scenario's tid in the failing child, 0 "representative died" lines.
- BOTH failing runs hit exactly 124 passes (pre- and post-boost) -
  the pass budget looks like a structural ceiling (16 rounds x wakes),
  not timing randomness: the chase needs ~200 rotation passes to lap
  to the holder and the test only ever funds ~124. Under this model
  the fix candidates are: fewer passes to resolution (Tier-2 holder
  expansion actually pruning the marker - 535-821 selections never did,
  which is itself suspicious: is the marker rep's parent EVER among the
  selected parents?), or more funded passes (rounds/grace), or a
  shorter resolution path (the 13-pass green run's non-canary path).

## Next instrumentation (when this becomes the active thread)

- TEST_LOG in tagLeakInstances/canary-prune with per-pass edges +
  which pass pruned; per-pass EMA contributions split
  root-enum vs chase.
- One failing run with those lines answers (1) and (2).
