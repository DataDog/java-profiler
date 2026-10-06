---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-06 10:08:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 306 |
| Sample Rate | 5.10/sec |
| Health Score | 319% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 41-48 cores)</summary>

```
1791295351 41
1791295356 41
1791295361 41
1791295366 41
1791295371 43
1791295376 43
1791295381 43
1791295386 43
1791295391 48
1791295396 48
1791295401 48
1791295406 48
1791295411 48
1791295416 48
1791295421 47
1791295426 47
1791295431 47
1791295436 47
1791295441 47
1791295446 47
```
</details>

---

