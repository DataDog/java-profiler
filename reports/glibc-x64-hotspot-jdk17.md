---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 10:37:08 EST

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 16-27 cores)</summary>

```
1794929321 21
1794929326 21
1794929331 21
1794929336 16
1794929341 16
1794929346 16
1794929351 16
1794929356 16
1794929361 16
1794929366 16
1794929371 16
1794929376 16
1794929381 16
1794929386 16
1794929391 16
1794929396 18
1794929401 18
1794929406 27
1794929411 27
1794929416 27
```
</details>

---

