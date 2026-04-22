---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-22 12:02:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 81-88 cores)</summary>

```
1776873464 88
1776873469 88
1776873474 86
1776873479 86
1776873484 86
1776873489 86
1776873494 86
1776873499 86
1776873504 86
1776873509 86
1776873514 86
1776873519 86
1776873524 81
1776873529 81
1776873534 81
1776873539 81
1776873544 81
1776873549 83
1776873554 83
1776873559 83
```
</details>

---

