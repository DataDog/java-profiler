---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 12:51:40 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 805 |
| Sample Rate | 13.42/sec |
| Health Score | 839% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793727975 51
1793727980 51
1793727985 51
1793727990 51
1793727995 51
1793728000 51
1793728005 46
1793728010 46
1793728015 46
1793728020 46
1793728025 46
1793728030 46
1793728035 46
1793728040 46
1793728045 46
1793728050 46
1793728055 46
1793728060 46
1793728065 46
1793728070 46
```
</details>

---

