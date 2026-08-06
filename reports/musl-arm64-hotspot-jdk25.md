---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-06 11:20:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 9 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1786029407 51
1786029412 46
1786029417 46
1786029422 46
1786029427 46
1786029432 46
1786029437 46
1786029442 46
1786029447 46
1786029452 46
1786029457 46
1786029462 46
1786029467 51
1786029472 51
1786029477 46
1786029482 46
1786029487 46
1786029492 46
1786029497 46
1786029502 41
```
</details>

---

