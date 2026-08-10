---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 05:03:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 11 |
| Allocations | 596 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1786352341 61
1786352346 61
1786352351 61
1786352356 61
1786352361 61
1786352366 61
1786352371 61
1786352376 61
1786352381 61
1786352386 61
1786352391 61
1786352396 61
1786352401 61
1786352406 61
1786352411 61
1786352416 61
1786352421 61
1786352426 59
1786352431 59
1786352436 59
```
</details>

---

