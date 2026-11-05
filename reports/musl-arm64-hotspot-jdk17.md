---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-05 00:07:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 11 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793854995 32
1793855000 32
1793855005 32
1793855010 32
1793855015 32
1793855020 32
1793855025 32
1793855030 32
1793855035 32
1793855040 32
1793855045 32
1793855050 32
1793855055 32
1793855060 32
1793855065 32
1793855070 32
1793855075 32
1793855080 32
1793855085 32
1793855090 32
```
</details>

---

