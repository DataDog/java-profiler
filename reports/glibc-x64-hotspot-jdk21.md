---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-01 10:24:27 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 9 |
| Allocations | 319 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (5 unique values: 83-96 cores)</summary>

```
1790864357 89
1790864362 89
1790864367 89
1790864372 91
1790864377 91
1790864382 91
1790864387 91
1790864392 96
1790864397 96
1790864402 96
1790864407 94
1790864412 94
1790864417 94
1790864422 94
1790864427 94
1790864432 94
1790864437 91
1790864442 91
1790864447 91
1790864452 91
```
</details>

---

