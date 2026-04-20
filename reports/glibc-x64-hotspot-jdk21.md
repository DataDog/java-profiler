---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 11:57:51 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 980 |
| Sample Rate | 16.33/sec |
| Health Score | 1021% |
| Threads | 12 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 54-68 cores)</summary>

```
1776699885 55
1776699890 55
1776699895 55
1776699900 55
1776699905 55
1776699910 55
1776699915 55
1776699920 54
1776699925 54
1776699930 54
1776699935 54
1776699940 54
1776699945 54
1776699950 54
1776699955 54
1776699960 54
1776699965 54
1776699970 54
1776699975 68
1776699980 68
```
</details>

---

