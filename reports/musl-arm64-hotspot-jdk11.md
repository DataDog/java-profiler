---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 05:20:31 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 14 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1786526210 53
1786526215 53
1786526220 53
1786526225 53
1786526230 53
1786526235 53
1786526240 53
1786526245 53
1786526250 53
1786526255 48
1786526260 48
1786526265 48
1786526270 48
1786526275 48
1786526280 48
1786526285 48
1786526290 48
1786526295 48
1786526300 48
1786526305 48
```
</details>

---

