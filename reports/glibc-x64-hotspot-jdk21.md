---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-23 04:32:54 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (5 unique values: 15-26 cores)</summary>

```
1776933005 22
1776933010 22
1776933015 22
1776933020 24
1776933025 24
1776933030 24
1776933035 24
1776933040 24
1776933045 24
1776933050 24
1776933055 24
1776933060 24
1776933065 24
1776933070 24
1776933075 24
1776933080 15
1776933085 15
1776933090 16
1776933095 16
1776933100 16
```
</details>

---

