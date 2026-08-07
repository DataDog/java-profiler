---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-07 12:23:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 331 |
| Sample Rate | 5.52/sec |
| Health Score | 345% |
| Threads | 11 |
| Allocations | 153 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1786119595 53
1786119600 53
1786119605 64
1786119610 64
1786119615 64
1786119620 64
1786119625 64
1786119630 53
1786119635 53
1786119640 53
1786119645 53
1786119650 53
1786119655 53
1786119660 53
1786119665 53
1786119670 53
1786119675 53
1786119680 53
1786119685 53
1786119690 53
```
</details>

---

