---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 08:00:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 72-96 cores)</summary>

```
1795006519 96
1795006524 96
1795006529 96
1795006534 96
1795006539 96
1795006544 96
1795006549 96
1795006554 96
1795006559 96
1795006564 74
1795006569 74
1795006574 74
1795006579 74
1795006584 72
1795006589 72
1795006594 72
1795006599 72
1795006604 72
1795006609 72
1795006614 72
```
</details>

---

