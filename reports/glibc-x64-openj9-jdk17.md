---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-26 06:37:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 65-81 cores)</summary>

```
1787740417 65
1787740422 65
1787740427 65
1787740432 65
1787740437 65
1787740442 65
1787740447 65
1787740452 65
1787740457 73
1787740462 73
1787740467 73
1787740472 73
1787740477 73
1787740482 73
1787740487 73
1787740492 73
1787740497 73
1787740502 73
1787740507 73
1787740512 73
```
</details>

---

