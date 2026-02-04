---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-04 10:23:39 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 11 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 13 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (9 unique values: 67-83 cores)</summary>

```
1770218397 70
1770218402 70
1770218407 67
1770218412 67
1770218417 69
1770218422 69
1770218427 69
1770218432 73
1770218437 73
1770218442 73
1770218447 73
1770218452 77
1770218457 77
1770218462 77
1770218467 79
1770218472 79
1770218477 75
1770218482 75
1770218487 79
1770218492 79
```
</details>

---

