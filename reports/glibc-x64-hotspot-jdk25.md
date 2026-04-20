---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 10:05:06 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (5 unique values: 74-92 cores)</summary>

```
1776693490 92
1776693495 92
1776693500 92
1776693505 92
1776693510 92
1776693515 92
1776693520 92
1776693525 92
1776693530 85
1776693535 85
1776693540 81
1776693545 81
1776693550 81
1776693555 74
1776693560 74
1776693565 78
1776693570 78
1776693575 78
1776693580 78
1776693585 78
```
</details>

---

