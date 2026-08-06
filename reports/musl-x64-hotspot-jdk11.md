---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-06 11:20:39 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 919 |
| Sample Rate | 15.32/sec |
| Health Score | 957% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (5 unique values: 75-84 cores)</summary>

```
1786029381 84
1786029386 84
1786029391 84
1786029396 82
1786029401 82
1786029406 82
1786029411 82
1786029416 79
1786029421 79
1786029426 79
1786029431 79
1786029436 79
1786029441 77
1786029446 77
1786029451 77
1786029456 77
1786029461 75
1786029466 75
1786029471 75
1786029476 75
```
</details>

---

