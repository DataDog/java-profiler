---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-20 05:36:46 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 39-42 cores)</summary>

```
1776677398 42
1776677403 42
1776677408 42
1776677413 42
1776677418 41
1776677423 41
1776677428 41
1776677433 41
1776677438 41
1776677443 41
1776677448 41
1776677453 41
1776677458 39
1776677463 39
1776677468 39
1776677473 39
1776677478 39
1776677483 39
1776677488 39
1776677493 39
```
</details>

---

