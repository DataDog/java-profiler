---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 05:36:44 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 9 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1776677368 27
1776677373 27
1776677378 27
1776677383 27
1776677388 27
1776677393 27
1776677398 27
1776677403 27
1776677408 27
1776677413 27
1776677418 27
1776677423 27
1776677428 27
1776677433 27
1776677438 27
1776677443 27
1776677448 27
1776677453 27
1776677458 27
1776677463 32
```
</details>

---

