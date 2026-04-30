---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-30 09:25:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 79 |
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
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 11 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (6 unique values: 70-79 cores)</summary>

```
1777555216 70
1777555221 70
1777555226 70
1777555231 75
1777555236 75
1777555241 75
1777555246 75
1777555251 75
1777555256 74
1777555261 74
1777555266 74
1777555271 73
1777555276 73
1777555281 74
1777555286 74
1777555291 72
1777555296 72
1777555301 72
1777555306 72
1777555311 72
```
</details>

---

