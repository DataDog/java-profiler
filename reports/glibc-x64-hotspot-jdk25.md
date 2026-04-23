---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-23 10:04:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (5 unique values: 56-67 cores)</summary>

```
1776952724 56
1776952729 56
1776952734 65
1776952739 65
1776952744 67
1776952749 67
1776952754 67
1776952759 67
1776952764 67
1776952769 67
1776952774 67
1776952779 67
1776952784 67
1776952789 67
1776952794 67
1776952799 67
1776952804 67
1776952809 67
1776952814 67
1776952819 63
```
</details>

---

