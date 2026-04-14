---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-14 08:00:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776167487 64
1776167492 64
1776167497 64
1776167502 64
1776167508 64
1776167513 64
1776167518 64
1776167523 64
1776167528 64
1776167533 64
1776167538 64
1776167543 64
1776167548 64
1776167553 64
1776167558 64
1776167563 64
1776167568 64
1776167573 64
1776167578 64
1776167583 64
```
</details>

---

