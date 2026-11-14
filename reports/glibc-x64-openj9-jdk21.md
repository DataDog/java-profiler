---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-14 13:09:13 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (4 unique values: 51-60 cores)</summary>

```
1794679409 60
1794679414 60
1794679419 60
1794679424 60
1794679430 60
1794679435 60
1794679440 60
1794679445 60
1794679450 51
1794679455 51
1794679460 51
1794679465 51
1794679470 51
1794679475 51
1794679480 51
1794679485 53
1794679490 53
1794679495 53
1794679500 53
1794679505 53
```
</details>

---

