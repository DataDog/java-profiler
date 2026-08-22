---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-22 05:27:13 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 8 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 35-51 cores)</summary>

```
1787390488 51
1787390493 51
1787390498 43
1787390503 43
1787390508 43
1787390513 43
1787390518 43
1787390523 43
1787390528 43
1787390533 43
1787390538 43
1787390543 43
1787390548 43
1787390553 43
1787390558 43
1787390563 43
1787390568 43
1787390573 43
1787390578 35
1787390583 35
```
</details>

---

