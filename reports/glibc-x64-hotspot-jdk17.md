---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-17 08:49:14 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 9 |
| Allocations | 415 |

<details>
<summary>CPU Timeline (5 unique values: 19-24 cores)</summary>

```
1776429814 24
1776429819 24
1776429824 24
1776429829 24
1776429834 24
1776429839 22
1776429844 22
1776429849 22
1776429854 22
1776429859 22
1776429864 22
1776429869 20
1776429874 20
1776429879 19
1776429884 19
1776429889 21
1776429894 21
1776429899 21
1776429904 21
1776429909 21
```
</details>

---

