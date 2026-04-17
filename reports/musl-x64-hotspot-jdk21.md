---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-17 11:46:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 40-42 cores)</summary>

```
1776440566 40
1776440571 40
1776440576 40
1776440581 40
1776440586 40
1776440591 40
1776440596 40
1776440601 40
1776440606 42
1776440611 42
1776440616 42
1776440621 42
1776440627 42
1776440632 42
1776440637 42
1776440642 42
1776440647 42
1776440652 42
1776440657 42
1776440662 42
```
</details>

---

