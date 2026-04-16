---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-16 12:01:42 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (6 unique values: 50-86 cores)</summary>

```
1776355040 62
1776355045 62
1776355050 62
1776355055 62
1776355060 62
1776355065 62
1776355070 67
1776355075 67
1776355080 80
1776355085 80
1776355090 80
1776355095 80
1776355100 86
1776355105 86
1776355110 55
1776355115 55
1776355120 55
1776355125 50
1776355130 50
1776355135 50
```
</details>

---

