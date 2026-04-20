---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-20 10:05:06 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (4 unique values: 13-73 cores)</summary>

```
1776693485 13
1776693490 13
1776693495 13
1776693500 13
1776693505 13
1776693510 45
1776693515 45
1776693520 68
1776693525 68
1776693530 73
1776693535 73
1776693540 73
1776693545 73
1776693550 73
1776693555 73
1776693560 73
1776693565 73
1776693570 73
1776693575 73
1776693580 73
```
</details>

---

