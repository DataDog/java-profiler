---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 11:54:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 829 |
| Sample Rate | 13.82/sec |
| Health Score | 864% |
| Threads | 12 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 27-30 cores)</summary>

```
1770137326 27
1770137331 27
1770137336 27
1770137341 27
1770137346 27
1770137351 27
1770137356 27
1770137361 27
1770137366 27
1770137371 27
1770137376 27
1770137381 27
1770137386 30
1770137391 30
1770137396 30
1770137401 30
1770137406 30
1770137411 30
1770137416 30
1770137421 30
```
</details>

---

