---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-22 04:39:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 10 |
| Allocations | 412 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1776846887 32
1776846892 32
1776846897 32
1776846902 32
1776846907 32
1776846912 32
1776846917 32
1776846922 32
1776846927 32
1776846932 32
1776846937 32
1776846942 27
1776846947 27
1776846952 27
1776846957 27
1776846962 27
1776846967 27
1776846973 32
1776846978 32
1776846983 32
```
</details>

---

