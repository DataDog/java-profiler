---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-22 05:27:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 35-51 cores)</summary>

```
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
1787390588 35
```
</details>

---

