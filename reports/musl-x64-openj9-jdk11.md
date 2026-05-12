---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:45:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 49-59 cores)</summary>

```
1778582443 59
1778582448 59
1778582453 59
1778582458 59
1778582463 59
1778582468 59
1778582473 49
1778582478 49
1778582483 49
1778582488 54
1778582493 54
1778582498 54
1778582503 54
1778582508 54
1778582513 54
1778582518 54
1778582523 54
1778582528 54
1778582533 54
1778582538 54
```
</details>

---

