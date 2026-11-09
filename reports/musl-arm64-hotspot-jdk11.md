---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 15:36:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 211 |
| Sample Rate | 3.52/sec |
| Health Score | 220% |
| Threads | 14 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794256329 43
1794256334 43
1794256339 43
1794256344 43
1794256349 43
1794256354 43
1794256359 43
1794256364 43
1794256369 43
1794256374 43
1794256379 48
1794256384 48
1794256389 48
1794256394 48
1794256399 48
1794256404 48
1794256409 48
1794256414 48
1794256419 48
1794256424 48
```
</details>

---

