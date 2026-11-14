---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-14 13:09:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
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
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 87-96 cores)</summary>

```
1794679420 96
1794679425 96
1794679430 96
1794679435 96
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
1794679495 87
1794679500 87
1794679505 87
1794679510 87
1794679515 87
```
</details>

---

