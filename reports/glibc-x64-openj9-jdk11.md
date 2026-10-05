---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-05 16:36:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 901 |
| Sample Rate | 15.02/sec |
| Health Score | 939% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 76-86 cores)</summary>

```
1791232283 84
1791232288 84
1791232293 84
1791232298 84
1791232303 84
1791232308 84
1791232313 86
1791232318 86
1791232323 86
1791232328 86
1791232333 86
1791232338 86
1791232343 86
1791232348 86
1791232353 86
1791232358 78
1791232363 78
1791232368 78
1791232373 78
1791232378 78
```
</details>

---

