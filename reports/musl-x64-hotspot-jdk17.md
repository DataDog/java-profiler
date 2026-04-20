---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-20 10:05:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 63-83 cores)</summary>

```
1776693468 63
1776693473 63
1776693478 63
1776693483 63
1776693488 63
1776693493 63
1776693498 63
1776693503 78
1776693508 78
1776693513 78
1776693518 83
1776693523 83
1776693528 83
1776693533 83
1776693538 83
1776693543 83
1776693548 83
1776693553 83
1776693558 83
1776693563 83
```
</details>

---

