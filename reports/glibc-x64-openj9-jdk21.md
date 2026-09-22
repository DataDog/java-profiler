---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 17:00:43 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 23-31 cores)</summary>

```
1790110493 30
1790110498 30
1790110503 31
1790110508 31
1790110513 31
1790110518 31
1790110523 31
1790110528 31
1790110533 31
1790110538 31
1790110543 31
1790110548 31
1790110553 31
1790110558 31
1790110563 31
1790110568 31
1790110573 31
1790110578 31
1790110583 31
1790110588 31
```
</details>

---

