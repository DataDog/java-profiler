---
id: ev-adaptive-batchsize-onpod-verification
type: evidence
source: pod logs (kubectl logs)
collected: 2026-08-27
tags: [pod-logs, on-pod, post-fix, live-verification, adaptive-batchsize, gotw, ema, NEW-THIS-SESSION]
---

# Adaptive batch_size confirmed live on-pod

Pod `prof-analyzer-hotdog-jb-c944876b9-q8vd8`, PID 263646, build `8f69683f9`.

## Warmup phase (EMA converging from default 64)

```
batch_size=58 resolved=57 edges=3 gotw_ms=7 ema=107486
batch_size=1  resolved=1  edges=4 gotw_ms=2 ema=553786
batch_size=1  resolved=1  edges=5 gotw_ms=2 ema=884800
batch_size=1  resolved=1  edges=6 gotw_ms=2 ema=1127789
batch_size=1  resolved=1  edges=7 gotw_ms=1 ema=1288262
batch_size=19 resolved=19 edges=7 gotw_ms=2 ema=1061539
batch_size=23 resolved=23 edges=9 gotw_ms=3 ema=876599
batch_size=28 resolved=28 edges=61 gotw_ms=3 ema=724782
batch_size=34 resolved=34 edges=65 gotw_ms=3 ema=600752
batch_size=41 resolved=41 edges=0  gotw_ms=10 ema=531578
batch_size=47 resolved=47 edges=8  gotw_ms=8 ema=459475
batch_size=54 resolved=54 edges=35 gotw_ms=8 ema=400035
batch_size=62 resolved=62 edges=49 gotw_ms=9 ema=349554
batch_size=71 resolved=71 edges=116 gotw_ms=8 ema=303889
batch_size=82 resolved=82 edges=352 gotw_ms=8 ema=262992
batch_size=95 resolved=93 edges=0  gotw_ms=10 ema=231582
batch_size=107 resolved=105 edges=2 gotw_ms=11 ema=206435
```

EMA spikes from initial gotw_ms=2 on batch_size=1 (cost_per_tag = 2ms/1 =
2M ns), then recovers as larger batches show lower per-tag cost.

## Steady state (EMA converged to ~62k ns/tag)

```
batch_size=417 resolved=417 edges=0   gotw_ms=25 ema=60193
batch_size=415 resolved=415 edges=263 gotw_ms=22 ema=59192
batch_size=422 resolved=422 edges=503 gotw_ms=35 ema=63988
batch_size=390 resolved=390 edges=0   gotw_ms=25 ema=64147
batch_size=389 resolved=389 edges=37  gotw_ms=20 ema=61881
batch_size=404 resolved=404 edges=0   gotw_ms=26 ema=62518
batch_size=399 resolved=399 edges=3   gotw_ms=24 ema=62317
batch_size=401 resolved=401 edges=227 gotw_ms=27 ema=63628
batch_size=392 resolved=391 edges=330 gotw_ms=26 ema=64219
batch_size=389 resolved=388 edges=0   gotw_ms=28 ema=66038
```

## Per-pass throughput

```
runPass done: edges_admitted=593 truncated=1 frontierSize=52724
runPass done: edges_admitted=648 truncated=1 frontierSize=53372
runPass done: edges_admitted=971 truncated=1 frontierSize=54343
runPass done: edges_admitted=456 truncated=1 frontierSize=54799
```

**Before fix**: 3-4 edges/pass. **After fix**: 456-971 edges/pass.
~100-200x throughput improvement.

## Candidate status

0 candidates at time of verification — JVM restarted (PID 263646), liveness
tracker needs warmup (`heapFloorRising=0`, `required_hysteresis=5`).
Leak still growing (`simulated-memory-leak: allocated 75 MB`).
