---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-16 06:02:55 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (4 unique values: 46-54 cores)</summary>

```
1776333323 54
1776333328 54
1776333333 54
1776333338 54
1776333343 52
1776333348 52
1776333353 52
1776333358 52
1776333363 52
1776333368 52
1776333373 48
1776333378 48
1776333383 48
1776333388 48
1776333393 48
1776333398 48
1776333403 46
1776333408 46
1776333413 52
1776333418 52
```
</details>

---

