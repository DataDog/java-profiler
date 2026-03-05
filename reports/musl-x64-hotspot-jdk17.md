---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-05 13:29:55 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 9 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (4 unique values: 19-27 cores)</summary>

```
1772735119 19
1772735124 19
1772735129 19
1772735134 19
1772735139 19
1772735144 19
1772735149 19
1772735154 19
1772735159 19
1772735164 19
1772735169 21
1772735174 21
1772735179 23
1772735184 23
1772735189 23
1772735194 23
1772735199 23
1772735204 23
1772735209 23
1772735214 23
```
</details>

---

