---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 12:51:40 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 38-64 cores)</summary>

```
1793727963 38
1793727968 38
1793727973 51
1793727978 51
1793727983 51
1793727988 51
1793727993 51
1793727998 51
1793728003 51
1793728008 51
1793728013 51
1793728018 51
1793728023 51
1793728028 51
1793728033 51
1793728038 51
1793728043 64
1793728048 64
1793728053 64
1793728058 64
```
</details>

---

