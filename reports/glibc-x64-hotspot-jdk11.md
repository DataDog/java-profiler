---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-20 04:28:58 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 25-32 cores)</summary>

```
1776673442 25
1776673447 25
1776673452 25
1776673457 25
1776673462 27
1776673467 27
1776673472 27
1776673477 27
1776673482 27
1776673487 27
1776673492 27
1776673497 27
1776673502 27
1776673507 27
1776673512 27
1776673517 27
1776673522 27
1776673527 32
1776673532 32
1776673537 28
```
</details>

---

