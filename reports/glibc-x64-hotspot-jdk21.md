---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-23 15:46:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 12.48/sec |
| Health Score | 780% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (5 unique values: 73-89 cores)</summary>

```
1776973311 87
1776973316 89
1776973321 89
1776973326 89
1776973331 89
1776973336 89
1776973341 89
1776973346 89
1776973351 89
1776973356 89
1776973361 76
1776973366 76
1776973371 76
1776973376 76
1776973381 76
1776973386 76
1776973391 76
1776973396 73
1776973401 73
1776973406 73
```
</details>

---

