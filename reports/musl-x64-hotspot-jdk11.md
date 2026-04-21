---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-21 06:58:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 10 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1776768660 30
1776768665 30
1776768670 30
1776768675 30
1776768680 30
1776768685 30
1776768690 30
1776768695 30
1776768700 30
1776768705 30
1776768710 30
1776768715 30
1776768720 32
1776768725 32
1776768731 32
1776768736 32
1776768741 32
1776768746 32
1776768751 32
1776768756 32
```
</details>

---

