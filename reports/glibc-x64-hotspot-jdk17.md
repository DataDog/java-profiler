---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 09:14:32 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (4 unique values: 66-75 cores)</summary>

```
1795529325 66
1795529330 66
1795529335 75
1795529340 75
1795529345 75
1795529350 75
1795529355 75
1795529360 70
1795529365 70
1795529370 70
1795529375 70
1795529380 70
1795529385 70
1795529390 67
1795529395 67
1795529400 67
1795529405 67
1795529410 67
1795529415 67
1795529420 67
```
</details>

---

