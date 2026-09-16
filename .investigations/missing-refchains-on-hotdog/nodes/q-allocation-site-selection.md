---
id: q-allocation-site-selection
type: question
status: implemented
depends_on: [find-age-heuristic-insufficient]
supersedes: []
related: [find-age-heuristic-insufficient]
tags: [design, referenceChains, livenessTracker, allocation-site, representative-selection, NEW-THIS-SESSION]
created: 2026-08-28
updated: 2026-08-28
---

# How to select representatives by allocation site?

## Context

User approved combining directions 1+3 from the research analysis:

- **Direction 1** (Cork/Melt): group surviving objects by
  `(klass_id, call_trace_id)` instead of just `klass_id`. Track growth
  trend per allocation site. Select representatives from the
  highest-growth site.
- **Direction 3** (Swat): per site, compute
  `growth_rate × survival_count`. Sites with many surviving instances
  outrank sites with few, regardless of individual object age or size.

## Implementation questions

1. `KlassCountScratch` currently keys by `klass_id` only. Keying by
   `(klass_id, call_trace_id)` means more distinct entries per epoch.
   The scratch table is capped at `MAX_KLASS_POPULATION_ENTRIES = 256`.
   With per-site granularity, there could be >256 distinct sites. Need
   to either increase the cap or prioritize sites with higher survival
   counts when the table is full (drop low-survival sites = noise).

2. `KlassPopulationEntry` tracks per-klass ring buffer of generation
   counts. With per-site tracking, need a ring buffer per
   `(klass_id, call_trace_id)` pair. Either:
   - (a) Expand `_klass_population` to key by `(klass_id, call_trace_id)`
     — more entries, more memory.
   - (b) Keep per-klass tracking for the leak signal (selectLeakCandidates)
     but add per-site tracking for representative selection only —
     the leak signal fires per-class, but the representative is picked
     from the highest-growth site within that class.

3. `TrackingEntry` already has `call_trace_id` and `tid`. The
   `accumulateKlassCount()` method receives `jlong age, jweak
   sample_source` but not `call_trace_id`. Need to pass it through.

4. `KlassCountScratch::oldest[]` tracks top-3 oldest instances. With
   per-site selection, we'd want top-3 oldest from the **highest-growth
   site**, not from all sites of the class.

## Implementation (commit 0b492612b)

**Implemented**: per-allocation-site generation cardinality tracking.

- `KlassCountScratch` now has `SiteGens[]` (max 16 sites × 32 ages
  each) tracking distinct surviving GC ages per `call_trace_id`.
- `accumulateKlassCount()` accepts `call_trace_id` and calls
  `insertSiteGen()` for EVERY surviving object (not just first per
  age — critical: per-site generation tracking must see all objects).
- `insertSiteGen()` maintains sorted distinct-age arrays per site.
- `foldKlassCountsLocked()` finds the dominant site by generation
  cardinality (most distinct surviving ages), then mints
  representatives preferentially from that site.
- `insertOldestSample()` now also stores `call_trace_id` per sample,
  so the minting logic can filter by site.

User refined the approach: use generation cardinality (distinct
surviving ages per site), not raw survival count — this reuses the
same signal that `selectLeakCandidates()` uses per-class, applied at
per-site granularity. A site with 12 distinct surviving ages
(continuous leak) outscores a site with 1 age (one-time burst).

**Not yet deployed**: pod still running `21ff0a928` + `cd68be618`.
