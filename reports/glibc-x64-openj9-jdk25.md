---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 07:41:15 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 59-68 cores)</summary>

```
1793709462 59
1793709467 59
1793709473 59
1793709478 66
1793709483 66
1793709488 66
1793709493 66
1793709498 66
1793709503 66
1793709508 66
1793709513 66
1793709518 66
1793709523 66
1793709528 66
1793709533 66
1793709538 68
1793709543 68
1793709548 68
1793709553 68
1793709558 68
```
</details>

---

