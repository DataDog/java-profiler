---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-23 04:32:54 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (5 unique values: 21-36 cores)</summary>

```
1776932977 34
1776932982 34
1776932987 34
1776932992 34
1776932997 34
1776933002 34
1776933007 36
1776933012 36
1776933017 36
1776933022 36
1776933027 36
1776933032 36
1776933037 36
1776933042 36
1776933047 36
1776933052 36
1776933057 34
1776933062 34
1776933067 21
1776933072 21
```
</details>

---

