---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-30 05:41:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 9 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 89-92 cores)</summary>

```
1769769326 89
1769769331 89
1769769336 92
1769769341 92
1769769346 92
1769769351 92
1769769356 92
1769769361 92
1769769366 92
1769769371 92
1769769376 92
1769769381 92
1769769386 91
1769769391 91
1769769396 91
1769769401 91
1769769406 91
1769769411 91
1769769416 91
1769769421 91
```
</details>

---

