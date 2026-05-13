---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-13 09:58:42 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (6 unique values: 70-78 cores)</summary>

```
1778680381 75
1778680386 75
1778680391 75
1778680396 71
1778680401 71
1778680406 71
1778680411 70
1778680416 70
1778680421 70
1778680426 71
1778680431 71
1778680436 71
1778680441 78
1778680446 78
1778680451 78
1778680456 76
1778680461 76
1778680466 76
1778680471 76
1778680476 76
```
</details>

---

