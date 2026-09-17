---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 13:55:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 11 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1789667351 73
1789667356 73
1789667361 73
1789667366 73
1789667371 73
1789667376 73
1789667381 73
1789667386 73
1789667391 73
1789667396 73
1789667401 73
1789667406 73
1789667411 73
1789667416 73
1789667421 73
1789667426 73
1789667431 71
1789667436 71
1789667441 71
1789667446 71
```
</details>

---

