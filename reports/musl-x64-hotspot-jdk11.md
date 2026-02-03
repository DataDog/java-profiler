---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 08:20:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 916 |
| Sample Rate | 15.27/sec |
| Health Score | 954% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1770124346 27
1770124351 27
1770124356 27
1770124361 27
1770124366 27
1770124371 27
1770124376 27
1770124381 27
1770124386 27
1770124391 27
1770124396 27
1770124401 27
1770124406 32
1770124411 32
1770124416 32
1770124421 32
1770124426 32
1770124431 32
1770124436 32
1770124441 32
```
</details>

---

