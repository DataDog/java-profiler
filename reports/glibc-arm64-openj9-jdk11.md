---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-08 09:20:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 364 |
| Sample Rate | 6.07/sec |
| Health Score | 379% |
| Threads | 13 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1791465293 51
1791465298 51
1791465303 51
1791465308 51
1791465313 51
1791465318 51
1791465323 51
1791465328 51
1791465333 51
1791465338 51
1791465343 51
1791465348 51
1791465353 51
1791465358 51
1791465363 51
1791465368 51
1791465373 51
1791465379 51
1791465384 51
1791465389 64
```
</details>

---

