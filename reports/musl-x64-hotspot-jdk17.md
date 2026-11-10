---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 14:54:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (4 unique values: 66-93 cores)</summary>

```
1794340098 76
1794340103 93
1794340108 93
1794340113 68
1794340118 68
1794340123 68
1794340128 68
1794340133 68
1794340138 68
1794340143 68
1794340148 68
1794340153 68
1794340158 68
1794340163 66
1794340168 66
1794340173 66
1794340178 66
1794340183 66
1794340188 66
1794340193 66
```
</details>

---

