---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-30 05:41:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 10 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 808 |
| Sample Rate | 13.47/sec |
| Health Score | 842% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 51-57 cores)</summary>

```
1769769326 51
1769769331 51
1769769336 51
1769769341 57
1769769346 57
1769769351 57
1769769356 57
1769769361 57
1769769366 57
1769769371 57
1769769376 57
1769769381 57
1769769386 57
1769769391 57
1769769396 57
1769769401 57
1769769406 57
1769769411 57
1769769416 57
1769769421 57
```
</details>

---

