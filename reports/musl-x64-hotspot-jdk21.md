---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:34:35 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (6 unique values: 51-69 cores)</summary>

```
1789716433 65
1789716438 67
1789716443 67
1789716448 67
1789716453 67
1789716458 67
1789716463 69
1789716468 69
1789716473 53
1789716478 53
1789716483 55
1789716488 55
1789716493 55
1789716498 53
1789716503 53
1789716508 55
1789716513 55
1789716518 53
1789716523 53
1789716528 53
```
</details>

---

