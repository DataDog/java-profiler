---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-22 14:04:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (5 unique values: 74-89 cores)</summary>

```
1776880862 74
1776880867 76
1776880872 76
1776880877 76
1776880882 76
1776880887 76
1776880892 76
1776880897 76
1776880902 76
1776880907 81
1776880912 81
1776880917 81
1776880922 86
1776880927 86
1776880932 86
1776880937 86
1776880942 86
1776880947 86
1776880952 86
1776880957 86
```
</details>

---

