---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-27 21:23:50 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 421 |

<details>
<summary>CPU Timeline (2 unique values: 19-49 cores)</summary>

```
1790558297 19
1790558302 19
1790558307 19
1790558312 19
1790558317 19
1790558322 19
1790558327 19
1790558332 19
1790558337 19
1790558342 49
1790558347 49
1790558352 49
1790558357 49
1790558362 49
1790558367 49
1790558372 49
1790558377 49
1790558382 49
1790558387 49
1790558392 49
```
</details>

---

