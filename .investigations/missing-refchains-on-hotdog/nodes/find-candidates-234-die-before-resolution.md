---
id: find-candidates-234-die-before-resolution
type: question
status: refuted
depends_on: [ev-postfix-static-field-onpod-live-verification]
supersedes: []
related: []
tags: [open, referenceChains, candidate, canary, sample-lifetime, NEW-THIS-SESSION]
created: 2026-08-25
updated: 2026-08-25
---

# Open: candidates 2-4 repeatedly report representative died/evicted before resolution

## Observation

Across multiple post-fix check windows, candidate slots 2-4 (klass_id
varying: 50, 236, 237, 232, 279 observed at different times/slots — the
slot<->klass_id mapping appears to shift between checks, not yet
investigated) repeatedly log:

```
candidate[N] klass_id=<K> representative could not be resolved (died/evicted)
```

Counts from one 2-minute window: klass_id=236 x3, klass_id=50 x10 (slot
1); klass_id=237 x38, klass_id=50 x36 (slot 2); klass_id=236 x36,
klass_id=50 x43 (slot 3); klass_id=232 x36, klass_id=236 x40,
klass_id=237 x53 (slot 4). This is a dominant, high-frequency pattern —
not a rare edge case.

## Hypothesis (not yet investigated)

Likely a sample-lifetime vs. candidate-selection/search-cadence mismatch:
the sampled representative object for these candidates is short-lived
enough to be GC'd before the reference-chain search gets around to acting
on it, independent of the static-field-sweep fix. This is a plausible
**pre-existing** issue (the static-field-sweep cursor fix only changes
static-field root admission, not sample/candidate selection or object
lifetime), but has NOT been confirmed as pre-existing — no comparison
against pre-fix logs has been done, and no code-read of the
representative-resolution path has happened yet.

## Status: REFUTED as a bug — expected app behavior

User confirmed directly: "the 2-4 dying is because we have only one
reliable leak in the app. everything else are
more-than-ephemeral-instances but they keep on getting garbage
collected." I.e. only one candidate (the actual synthetic leak target,
resolved as candidate[1]/klass_id=283 per `find-candidate1-never-tagged`)
is a genuine permanently-retained object; the other selected candidates
are just longer-lived-than-typical instances that are still ordinarily
collectible, so their sampled representatives dying before the search
reaches them is exactly the expected outcome, not a search/tooling
defect. No further investigation needed here.
