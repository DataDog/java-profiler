---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-06 11:20:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (6 unique values: 74-83 cores)</summary>

```
1786029368 83
1786029373 83
1786029378 76
1786029383 76
1786029388 74
1786029393 74
1786029398 74
1786029403 77
1786029408 77
1786029413 79
1786029418 79
1786029423 79
1786029428 81
1786029433 81
1786029438 81
1786029443 81
1786029448 83
1786029453 83
1786029458 83
1786029463 83
```
</details>

---

