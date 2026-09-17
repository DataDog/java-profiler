---
id: find-age-heuristic-insufficient
type: finding
status: diagnosed
depends_on: [find-representative-changes-lose-canary]
supersedes: []
related: [find-representative-changes-lose-canary, q-allocation-site-selection]
tags: [root-cause, referenceChains, livenessTracker, age-heuristic, representative-selection, NEW-THIS-SESSION]
created: 2026-08-28
updated: 2026-08-28
---

# Age heuristic for representative selection is insufficient

## Observation

JFR analysis showed 13 [B instances in `datadog.HeapLiveObject`:

- 12 leaking: 78MB each, tid=172 (`simulated-memory-leak`), ages 33-168
  (only age=168 has allocation stack: `lambda$static$1` in `ProfileAnalyzer`)
- 1 noise: 136B, tid=284 (`s3-netty-2`), age=172, stack=`initClassName`

The oldest [B (age=172) is the **noise** — a class-name initialization
buffer. The leaking instances have ages 33-168. Pure age ranking (Lindy
heuristic) picks the noise first.

## Root cause

LivenessTracker's representative was selected as the oldest surviving
instance per klass (GC age descending). For [B, the oldest surviving
instance is a 136B class-init buffer, not a 78MB leaking array. The
Lindy heuristic assumes older = more likely to be a leak, but for
common classes with diverse allocation sites, the oldest instance may
be a long-lived framework object, not a leak.

## Proposed directions (user-approved: 1+3 combined)

1. **Allocation-site clustering** (Cork, SOSP'23; Melt, OSDI'15): group
   surviving objects by `(klass_id, call_trace_id)` instead of just
   `klass_id`. Track growth trend per allocation site. Select
   representatives from the highest-growth site, not just the oldest
   instance. `TrackingEntry` already has `call_trace_id`.

3. **Growth-rate × survival-count** (Swat, SOSP'19): per allocation
   site, compute `growth_rate × survival_count`. A site with 12
   surviving instances across 12 GC ages (leak) outscores a site with
   1 surviving instance (noise) by 12×, regardless of individual age
   or size. Addresses the "frequent but small" concern: frequent
   small allocations that die quickly score low (low survival); frequent
   small allocations that survive score high (real leak).

User rejected: size-weighted selection (shadows frequent small leaks).
User noted: retained-size weighting (direction 2) lacks data in current
implementation.
