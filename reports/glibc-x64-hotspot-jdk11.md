---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 04:32:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (4 unique values: 20-24 cores)</summary>

```
1776932953 21
1776932958 21
1776932963 21
1776932968 21
1776932973 21
1776932978 21
1776932983 24
1776932988 24
1776932993 20
1776932998 20
1776933003 22
1776933008 22
1776933013 22
1776933018 22
1776933023 22
1776933028 22
1776933033 24
1776933038 24
1776933043 24
1776933048 24
```
</details>

---

