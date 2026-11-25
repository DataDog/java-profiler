---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:00:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (5 unique values: 82-94 cores)</summary>

```
1795618443 84
1795618448 84
1795618453 84
1795618458 84
1795618463 84
1795618468 84
1795618473 84
1795618478 84
1795618483 84
1795618488 82
1795618493 82
1795618498 90
1795618503 90
1795618508 90
1795618513 90
1795618518 90
1795618523 90
1795618528 92
1795618533 92
1795618539 92
```
</details>

---

