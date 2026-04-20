---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 10:20:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (6 unique values: 73-90 cores)</summary>

```
1776694368 90
1776694373 85
1776694378 85
1776694383 85
1776694388 85
1776694393 85
1776694398 85
1776694403 80
1776694408 80
1776694413 80
1776694418 80
1776694423 80
1776694428 80
1776694433 80
1776694438 73
1776694443 73
1776694448 73
1776694453 73
1776694458 73
1776694463 73
```
</details>

---

