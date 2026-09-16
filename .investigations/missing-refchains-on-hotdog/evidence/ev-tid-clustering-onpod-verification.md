---
id: ev-tid-clustering-onpod-verification
type: evidence
status: pending-verification
depends_on: [find-lambda-fragments-calltrace-id, q-allocation-site-selection]
supersedes: []
related: [find-lambda-fragments-calltrace-id, q-allocation-site-selection]
tags: [pod-logs, on-pod, post-fix, live-verification, tid-clustering, dominant-gens, NEW-THIS-SESSION]
created: 2026-08-28
updated: 2026-08-28
---

# tid-based clustering on-pod: still dominant_gens=1

## Context

After switching the clustering key from `call_trace_id` to `tid`
(commit `2c50bf0cd`), deployed to pod PID 58100, .so md5
`abe3c2dc7e...`.

## Observation

All `foldKlassCountsLocked minted=` lines show `dominant_gens=1`:

```
minted=2 for klass_id=205 dominant_tid=58393 dominant_gens=1
minted=3 for klass_id=20  dominant_tid=58471 dominant_gens=1
minted=1 for klass_id=2213 dominant_tid=58470 dominant_gens=1
minted=1 for klass_id=279 dominant_tid=58470 dominant_gens=1
minted=2 for klass_id=12  dominant_tid=58393 dominant_gens=1
```

klass_id=4 has the strongest leak signal (gen_count=33, slope=30.4,
consecutive_positive=13) but no `minted=` line — representatives
already live, `need_mint=false`.

## Problem

User pushback: the liveness tracking table IS cross-epoch, surviving
objects accumulate ages across GC cycles. The 12 leaking [B from
tid=172 (`simulated-memory-leak`) should all be in the table with
different ages. So `insertThreadGen` should be called 12 times for
tid=172 with 12 different ages → `dominant_gens=12`, not 1.

Possible explanations (not yet verified):
1. Liveness tracker subsampling: only 1 of 12 leaking [B is tracked
2. `tid` field is 0 or wrong for some entries
3. Only 1 surviving object per thread per epoch in the scratch

## Next step

Diagnostic commit `5e4493dbf` logs per-thread `age_count` breakdown
in `foldKlassCountsLocked`. Needs redeploy to see whether tid=172
(or equivalent) has 1 age (subsampling) or multiple ages (bug in
insertThreadGen).
