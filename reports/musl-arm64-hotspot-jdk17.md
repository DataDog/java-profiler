---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 05:57:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 312 |
| Sample Rate | 5.20/sec |
| Health Score | 325% |
| Threads | 9 |
| Allocations | 134 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 39-59 cores)</summary>

```
1794826366 46
1794826371 46
1794826376 46
1794826381 46
1794826386 46
1794826391 46
1794826396 46
1794826401 46
1794826406 46
1794826411 46
1794826416 59
1794826421 59
1794826426 59
1794826431 59
1794826436 39
1794826441 39
1794826446 39
1794826451 39
1794826456 39
1794826461 39
```
</details>

---

