---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-14 20:02:53 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 71-77 cores)</summary>

```
1794704309 77
1794704314 73
1794704319 73
1794704324 73
1794704329 73
1794704334 73
1794704339 73
1794704344 73
1794704349 75
1794704354 75
1794704359 75
1794704364 75
1794704369 75
1794704374 75
1794704379 75
1794704384 75
1794704389 73
1794704394 73
1794704399 73
1794704404 73
```
</details>

---

