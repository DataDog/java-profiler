---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 10:37:09 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 304 |
| Sample Rate | 5.07/sec |
| Health Score | 317% |
| Threads | 14 |
| Allocations | 130 |

<details>
<summary>CPU Timeline (3 unique values: 48-64 cores)</summary>

```
1794929306 48
1794929311 48
1794929316 48
1794929321 48
1794929326 48
1794929331 48
1794929336 51
1794929341 51
1794929346 51
1794929351 51
1794929356 51
1794929361 51
1794929366 51
1794929371 51
1794929376 64
1794929381 64
1794929386 64
1794929391 51
1794929396 51
1794929401 51
```
</details>

---

