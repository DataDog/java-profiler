---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-06 11:20:37 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (6 unique values: 74-83 cores)</summary>

```
1786029388 76
1786029393 74
1786029398 74
1786029403 77
1786029408 77
1786029413 79
1786029418 79
1786029423 79
1786029428 81
1786029433 81
1786029438 81
1786029443 81
1786029448 83
1786029453 83
1786029458 83
1786029463 83
1786029468 81
1786029473 81
1786029478 81
1786029483 81
```
</details>

---

