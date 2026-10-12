---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-12 03:21:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (4 unique values: 43-51 cores)</summary>

```
1791789389 49
1791789394 49
1791789399 49
1791789404 49
1791789409 51
1791789414 51
1791789419 51
1791789424 51
1791789429 51
1791789434 51
1791789439 51
1791789444 51
1791789449 51
1791789454 49
1791789459 49
1791789464 49
1791789469 49
1791789474 49
1791789479 49
1791789484 43
```
</details>

---

