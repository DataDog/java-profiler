---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:21:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1794507326 62
1794507331 62
1794507336 62
1794507341 62
1794507346 62
1794507351 62
1794507356 62
1794507361 60
1794507366 60
1794507371 60
1794507376 60
1794507381 60
1794507386 60
1794507391 60
1794507396 60
1794507401 60
1794507406 60
1794507411 60
1794507416 60
1794507421 62
```
</details>

---

