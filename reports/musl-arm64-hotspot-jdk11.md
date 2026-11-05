---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 00:07:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 40 |

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

