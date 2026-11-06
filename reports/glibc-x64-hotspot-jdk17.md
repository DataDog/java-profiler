---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-06 16:49:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (4 unique values: 62-70 cores)</summary>

```
1794001480 66
1794001485 70
1794001490 70
1794001495 70
1794001500 70
1794001505 70
1794001510 70
1794001515 70
1794001520 70
1794001525 68
1794001530 68
1794001535 68
1794001540 68
1794001545 68
1794001550 68
1794001555 70
1794001560 70
1794001565 70
1794001570 70
1794001575 70
```
</details>

---

