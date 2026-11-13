---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 06:01:49 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 24-30 cores)</summary>

```
1794567338 29
1794567343 29
1794567348 29
1794567353 29
1794567358 29
1794567363 29
1794567368 29
1794567373 29
1794567378 27
1794567383 27
1794567388 30
1794567393 30
1794567398 30
1794567403 30
1794567408 24
1794567413 24
1794567418 24
1794567423 24
1794567428 24
1794567434 24
```
</details>

---

