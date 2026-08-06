---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-06 11:20:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1786029390 41
1786029395 41
1786029400 41
1786029405 41
1786029410 46
1786029415 46
1786029420 46
1786029425 46
1786029430 46
1786029435 46
1786029440 46
1786029445 46
1786029450 46
1786029455 46
1786029460 46
1786029465 46
1786029470 46
1786029475 46
1786029480 46
1786029485 46
```
</details>

---

