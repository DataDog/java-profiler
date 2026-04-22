---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-22 14:02:52 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (6 unique values: 53-70 cores)</summary>

```
1776880798 53
1776880803 53
1776880808 53
1776880813 53
1776880818 53
1776880823 53
1776880828 53
1776880833 53
1776880838 53
1776880843 53
1776880848 53
1776880853 53
1776880858 61
1776880863 61
1776880868 61
1776880873 61
1776880878 59
1776880883 59
1776880888 59
1776880893 65
```
</details>

---

