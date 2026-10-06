---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-06 08:29:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 9 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (3 unique values: 20-58 cores)</summary>

```
1791289463 20
1791289468 20
1791289473 20
1791289478 20
1791289483 20
1791289488 20
1791289493 20
1791289498 20
1791289503 20
1791289508 28
1791289513 28
1791289518 28
1791289523 28
1791289528 28
1791289533 28
1791289538 28
1791289543 28
1791289548 58
1791289553 58
1791289558 58
```
</details>

---

