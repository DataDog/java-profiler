---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-27 07:00:15 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (4 unique values: 59-69 cores)</summary>

```
1793098440 59
1793098445 59
1793098450 59
1793098455 59
1793098460 59
1793098465 69
1793098470 69
1793098475 69
1793098480 69
1793098485 69
1793098490 69
1793098495 69
1793098500 69
1793098505 69
1793098510 69
1793098515 69
1793098520 69
1793098525 67
1793098530 67
1793098535 67
```
</details>

---

