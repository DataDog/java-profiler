---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 05:16:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 14-32 cores)</summary>

```
1770113294 32
1770113299 32
1770113304 32
1770113309 32
1770113314 32
1770113319 32
1770113324 32
1770113329 32
1770113334 32
1770113339 32
1770113344 32
1770113349 32
1770113354 32
1770113359 23
1770113364 23
1770113369 23
1770113374 23
1770113379 23
1770113384 23
1770113389 23
```
</details>

---

