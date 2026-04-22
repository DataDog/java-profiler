---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-22 04:39:06 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 405 |

<details>
<summary>CPU Timeline (2 unique values: 13-21 cores)</summary>

```
1776846912 13
1776846917 13
1776846922 13
1776846927 13
1776846932 13
1776846937 13
1776846942 21
1776846947 21
1776846952 21
1776846957 21
1776846962 21
1776846967 21
1776846972 21
1776846977 21
1776846982 21
1776846987 21
1776846992 21
1776846997 21
1776847002 21
1776847007 21
```
</details>

---

