---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-14 13:09:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 12 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 87-96 cores)</summary>

```
1794679423 96
1794679428 96
1794679433 96
1794679438 96
1794679443 87
1794679448 87
1794679453 87
1794679458 87
1794679463 87
1794679468 87
1794679473 87
1794679478 87
1794679483 87
1794679488 87
1794679493 87
1794679498 87
1794679503 87
1794679508 87
1794679513 87
1794679518 87
```
</details>

---

