---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 08:38:35 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (5 unique values: 48-57 cores)</summary>

```
1770125468 52
1770125473 52
1770125478 52
1770125483 48
1770125488 48
1770125493 48
1770125498 48
1770125503 48
1770125508 53
1770125513 53
1770125518 53
1770125523 53
1770125528 53
1770125533 53
1770125538 57
1770125543 57
1770125548 57
1770125553 57
1770125558 57
1770125563 55
```
</details>

---

