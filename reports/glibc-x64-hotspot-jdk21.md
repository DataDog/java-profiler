---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-23 04:28:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 31 |
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
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (4 unique values: 29-35 cores)</summary>

```
1776932404 33
1776932409 33
1776932414 33
1776932419 35
1776932424 35
1776932429 35
1776932434 35
1776932439 35
1776932444 35
1776932449 35
1776932454 35
1776932459 35
1776932464 35
1776932469 35
1776932474 35
1776932479 35
1776932484 35
1776932489 29
1776932494 29
1776932499 31
```
</details>

---

