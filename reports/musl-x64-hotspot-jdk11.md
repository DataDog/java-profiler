---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-14 13:09:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 780 |
| Sample Rate | 13.00/sec |
| Health Score | 812% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 79-87 cores)</summary>

```
1794679395 79
1794679400 79
1794679405 79
1794679410 79
1794679415 87
1794679420 87
1794679425 87
1794679430 87
1794679435 87
1794679440 87
1794679445 87
1794679450 87
1794679455 87
1794679460 87
1794679465 87
1794679470 87
1794679475 87
1794679480 87
1794679485 87
1794679490 87
```
</details>

---

