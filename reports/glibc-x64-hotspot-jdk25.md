---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 10:20:31 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 24-28 cores)</summary>

```
1776694328 24
1776694333 24
1776694338 24
1776694343 28
1776694348 28
1776694353 28
1776694358 28
1776694363 28
1776694368 28
1776694373 28
1776694378 28
1776694383 28
1776694388 28
1776694393 28
1776694398 28
1776694403 28
1776694408 28
1776694413 28
1776694418 28
1776694423 28
```
</details>

---

