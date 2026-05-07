---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 10:54:17 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (4 unique values: 81-89 cores)</summary>

```
1778165483 81
1778165488 83
1778165493 83
1778165498 83
1778165503 83
1778165508 85
1778165513 85
1778165518 85
1778165523 83
1778165528 83
1778165533 83
1778165538 85
1778165543 85
1778165548 85
1778165553 85
1778165558 85
1778165563 85
1778165568 83
1778165573 83
1778165578 83
```
</details>

---

