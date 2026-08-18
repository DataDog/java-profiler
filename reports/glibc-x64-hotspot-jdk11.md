---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-18 10:51:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 885 |
| Sample Rate | 14.75/sec |
| Health Score | 922% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1787064352 82
1787064357 82
1787064362 82
1787064367 82
1787064372 82
1787064377 82
1787064382 82
1787064387 82
1787064392 86
1787064397 86
1787064402 86
1787064407 86
1787064412 86
1787064417 86
1787064422 86
1787064427 86
1787064432 86
1787064437 86
1787064442 86
1787064447 82
```
</details>

---

