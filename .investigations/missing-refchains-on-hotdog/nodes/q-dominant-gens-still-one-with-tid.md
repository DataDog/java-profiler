---
id: q-dominant-gens-still-one-with-tid
type: question
status: open
depends_on: [find-lambda-fragments-calltrace-id, ev-tid-clustering-onpod-verification]
supersedes: []
related: [find-lambda-fragments-calltrace-id, q-allocation-site-selection]
tags: [referenceChains, livenessTracker, tid, dominant-gens, subsampling, NEW-THIS-SESSION]
created: 2026-08-28
updated: 2026-08-28
---

# Why is dominant_gens=1 even with tid-based clustering?

## Context

Switched clustering from `call_trace_id` to `tid` (commit `2c50bf0cd`).
On-pod: still `dominant_gens=1` for every class every epoch.

User says: the liveness table IS cross-epoch, and the leaking [B
instances ARE all from the same thread (tid=172). So the per-thread
age set should have 12 distinct ages, not 1.

## Hypotheses

1. **Subsampling**: The liveness tracker subsamples allocations
   (`_subsample_ratio`). If the ratio is low, only 1 of 12 leaking [B
   is tracked. That 1 instance has 1 age → `dominant_gens=1`. The
   per-class `gen_count=33` comes from 33 different threads each
   contributing 1 tracked instance.

2. **tid field not populated**: `_table[target].tid` might be 0 for
   some entries, causing all objects to cluster under tid=0.

3. **insertThreadGen bug**: The sorted-insert or dedup logic might
   be wrong — but the code looks correct (linear scan for existing
   tid, sorted insert of distinct ages).

## Diagnostic

Commit `5e4493dbf` logs per-thread `age_count` breakdown:
```
thread[0] tid=58393 age_count=1
thread[1] tid=58471 age_count=1
...
```

If all threads show `age_count=1`, hypothesis 1 (subsampling) is
likely. If one thread shows `age_count=12` but `dominant_gens` is
still 1, there's a bug in the dominant-thread selection.

## Implication

If subsampling is the cause, per-epoch per-thread tracking in the
scratch table can never produce `dominant_gens > 1` — the signal is
too sparse. Would need cross-epoch per-thread tracking in
`KlassPopulationEntry` (a per-thread ring buffer), only for leak
candidates.
