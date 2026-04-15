---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-15 07:24:18 EDT

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (7 unique values: 41-72 cores)</summary>

```
1776252036 69
1776252041 69
1776252046 72
1776252051 72
1776252056 72
1776252061 72
1776252066 67
1776252071 67
1776252076 71
1776252081 71
1776252086 71
1776252091 71
1776252096 41
1776252101 41
1776252106 41
1776252111 41
1776252116 42
1776252121 42
1776252126 42
1776252131 42
```
</details>

---

