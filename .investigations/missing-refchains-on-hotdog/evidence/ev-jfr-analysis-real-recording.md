---
id: ev-jfr-analysis-real-recording
type: evidence
source: ~/Downloads/20260828-094323_prof-analyzer-hotdog_AaBHwZLWAAAayqog74k1iwAA/main.jfr
collected: 2026-08-28
tags: [jfr, jafar, on-pod, ddprof-jfr, analysis, NEW-THIS-SESSION]
---

# JFR analysis of real ddprof recording

## Source

Real ddprof JFR (NOT jcmd dump — jcmd only dumps JDK's built-in JFR, not
ddprof's native JFR writer). Obtained via profiling toolkit download.py
from uploaded profiles.

## Event types found

```
  105 - datadog.HeapLiveObject
  129 - datadog.ReferenceChain
  130 - datadog.ReferenceChainAbandoned
```

## ReferenceChain events (2)

1. `targetTag=-4611686018427387906` (marker tag, slot 0) — depth=14,
   totalHops=15, rootKind=unknown
   → Canary chain for [B candidate. rootKind="unknown" means chain
   reconstruction didn't find a proper root.

2. `targetTag=5940` — depth=1, totalHops=2,
   rootKind=first_observed_via:jni_local
   → Auto-mark chain for the **noise** [B (136B, s3-netty-2 thread,
   JNI local root). BFS reached this shallow instance before the deep
   leaking instances.

## HeapLiveObject events (17 total)

### [B instances (13)

| Age | Size | Thread | Stack top | Description |
|-----|------|--------|-----------|-------------|
| 168 | 78MB | simulated-memory-leak | lambda$static$1 | LEAK (has stack) |
| 161 | 78MB | simulated-memory-leak | no-stack | LEAK |
| 133 | 78MB | simulated-memory-leak | no-stack | LEAK |
| 124 | 78MB | simulated-memory-leak | no-stack | LEAK |
| 118 | 78MB | simulated-memory-leak | no-stack | LEAK |
| 106 | 78MB | simulated-memory-leak | no-stack | LEAK |
| 97 | 78MB | simulated-memory-leak | no-stack | LEAK |
| 81 | 78MB | simulated-memory-leak | no-stack | LEAK |
| 77 | 78MB | simulated-memory-leak | no-stack | LEAK |
| 69 | 78MB | simulated-memory-leak | no-stack | LEAK |
| 61 | 78MB | simulated-memory-leak | no-stack | LEAK |
| 33 | 78MB | simulated-memory-leak | no-stack | LEAK |
| 172 | 136B | s3-netty-2 | initClassName | NOISE |

### Other classes (4)

- `[Ljava.lang.Object;` × 2 (ages 49, 91, 1040B each, netty threads)
- `PSWMS` × 1 (age 103, 48B, cpu-intensive-8)
- `ArrayList` × 1 (age 172, 24B, s3-netty-2 — the container holding the leak)
- `IntPriorityQueue` × 1 (age 168, 24B, grpc worker)

## Key findings

1. The noise [B (age=172, 136B) is the oldest — age heuristic picks it
   first as representative.
2. The leaking [B instances are all tid=172 (simulated-memory-leak),
   all 78MB, ages 33-168. 12 instances from the same allocation site.
3. The noise [B is tid=284 (s3-netty-2), 136B, different allocation
   site entirely.
4. The auto-mark chain (depth=1, jni_local) was for the noise [B.
   The leaking [B at depth=14 was never reached by BFS before the
   chain was cached (per-class caching blocked it).
