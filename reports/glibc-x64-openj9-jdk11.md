---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-22 14:02:52 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 8 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (5 unique values: 11-56 cores)</summary>

```
1776880779 47
1776880784 56
1776880789 56
1776880794 11
1776880799 11
1776880804 11
1776880809 11
1776880814 11
1776880819 11
1776880824 11
1776880829 11
1776880834 11
1776880839 11
1776880844 16
1776880849 16
1776880854 14
1776880859 14
1776880864 14
1776880869 14
1776880874 16
```
</details>

---

