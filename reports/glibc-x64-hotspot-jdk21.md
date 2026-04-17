---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-17 11:46:54 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 53-65 cores)</summary>

```
1776440582 53
1776440587 53
1776440592 53
1776440597 65
1776440602 65
1776440607 65
1776440612 65
1776440617 65
1776440622 65
1776440627 65
1776440632 65
1776440638 65
1776440643 65
1776440648 65
1776440653 65
1776440658 65
1776440663 65
1776440668 65
1776440673 65
1776440678 65
```
</details>

---

