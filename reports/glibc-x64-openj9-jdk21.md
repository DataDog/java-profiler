---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 05:03:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 12 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 90-92 cores)</summary>

```
1786352352 90
1786352357 92
1786352362 92
1786352367 92
1786352372 92
1786352377 92
1786352382 92
1786352387 92
1786352392 92
1786352397 92
1786352402 92
1786352407 92
1786352412 92
1786352417 90
1786352422 90
1786352427 90
1786352432 90
1786352437 90
1786352442 90
1786352447 90
```
</details>

---

