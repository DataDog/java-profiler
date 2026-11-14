---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-14 13:09:16 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 9 |
| Allocations | 588 |

<details>
<summary>CPU Timeline (2 unique values: 66-75 cores)</summary>

```
1794679373 75
1794679378 75
1794679383 75
1794679388 75
1794679393 75
1794679398 75
1794679403 75
1794679408 75
1794679413 66
1794679418 66
1794679423 66
1794679428 66
1794679433 66
1794679438 66
1794679443 66
1794679448 66
1794679453 66
1794679458 66
1794679463 66
1794679468 66
```
</details>

---

