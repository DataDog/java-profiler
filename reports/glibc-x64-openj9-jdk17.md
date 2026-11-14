---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-14 13:09:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 53-76 cores)</summary>

```
1794679382 53
1794679387 53
1794679392 53
1794679397 53
1794679402 53
1794679407 53
1794679412 53
1794679417 53
1794679422 53
1794679427 53
1794679432 53
1794679437 53
1794679442 53
1794679447 57
1794679452 57
1794679457 57
1794679462 57
1794679467 76
1794679472 76
1794679477 76
```
</details>

---

