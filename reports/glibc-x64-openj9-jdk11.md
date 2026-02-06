---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-06 09:39:28 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 850 |
| Sample Rate | 14.17/sec |
| Health Score | 886% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 53-57 cores)</summary>

```
1770388400 53
1770388405 53
1770388410 57
1770388415 57
1770388420 57
1770388425 57
1770388430 57
1770388435 57
1770388440 57
1770388445 57
1770388450 57
1770388455 57
1770388460 57
1770388465 57
1770388470 57
1770388475 57
1770388480 57
1770388485 57
1770388490 57
1770388495 57
```
</details>

---

