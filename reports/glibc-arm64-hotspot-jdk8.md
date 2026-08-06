---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ❌ FAIL

**Date:** 2026-08-06 11:20:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 3 |
| Sample Rate | 0.05/sec |
| Health Score | 3% |
| Threads | 2 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1786029386 27
1786029391 27
1786029396 27
1786029401 27
1786029406 29
1786029411 29
1786029416 29
1786029421 29
1786029426 29
1786029431 29
1786029436 29
1786029441 29
1786029446 29
1786029451 29
1786029456 29
1786029461 29
1786029466 29
1786029471 29
1786029476 29
1786029481 29
```
</details>

---

