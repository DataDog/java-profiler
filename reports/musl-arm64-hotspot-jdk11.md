---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 19:07:43 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 13 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 39-43 cores)</summary>

```
1793836963 43
1793836968 43
1793836973 43
1793836978 43
1793836983 43
1793836988 43
1793836993 43
1793836998 43
1793837003 43
1793837008 43
1793837013 43
1793837018 43
1793837023 43
1793837028 43
1793837033 43
1793837038 43
1793837043 43
1793837048 43
1793837053 43
1793837058 43
```
</details>

---

