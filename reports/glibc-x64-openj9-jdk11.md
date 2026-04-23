---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 10:04:14 EDT

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 948 |
| Sample Rate | 15.80/sec |
| Health Score | 988% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (7 unique values: 61-74 cores)</summary>

```
1776952744 69
1776952749 69
1776952754 69
1776952759 69
1776952764 69
1776952769 69
1776952774 69
1776952779 67
1776952784 67
1776952789 61
1776952794 61
1776952799 61
1776952804 61
1776952809 61
1776952814 65
1776952819 65
1776952824 65
1776952829 66
1776952834 66
1776952839 66
```
</details>

---

