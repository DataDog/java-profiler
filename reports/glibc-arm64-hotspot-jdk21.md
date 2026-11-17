---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 10:37:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 8 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 14 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (3 unique values: 28-51 cores)</summary>

```
1794929361 51
1794929366 51
1794929371 51
1794929376 51
1794929381 51
1794929386 51
1794929391 51
1794929396 51
1794929401 51
1794929406 51
1794929411 51
1794929416 33
1794929421 33
1794929426 28
1794929431 28
1794929436 28
1794929441 28
1794929446 28
1794929451 28
1794929456 28
```
</details>

---

