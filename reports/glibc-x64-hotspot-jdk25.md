---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 05:59:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 11 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (4 unique values: 65-87 cores)</summary>

```
1794999346 85
1794999351 85
1794999356 87
1794999361 87
1794999366 87
1794999371 81
1794999376 81
1794999381 81
1794999386 81
1794999391 65
1794999396 65
1794999401 65
1794999406 65
1794999411 65
1794999416 65
1794999421 65
1794999426 65
1794999431 65
1794999436 65
1794999441 65
```
</details>

---

