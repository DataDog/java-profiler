---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 19:07:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 50-62 cores)</summary>

```
1793836960 62
1793836965 62
1793836970 62
1793836975 62
1793836980 62
1793836985 62
1793836990 50
1793836995 50
1793837000 50
1793837005 50
1793837010 50
1793837015 50
1793837020 50
1793837025 50
1793837030 50
1793837035 50
1793837040 50
1793837045 50
1793837050 50
1793837055 50
```
</details>

---

