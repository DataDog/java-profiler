---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:02:29 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (5 unique values: 68-94 cores)</summary>

```
1794405438 70
1794405443 68
1794405448 68
1794405453 68
1794405458 68
1794405463 68
1794405468 68
1794405473 68
1794405478 68
1794405483 68
1794405488 90
1794405493 90
1794405498 90
1794405503 90
1794405508 92
1794405513 92
1794405518 92
1794405523 92
1794405528 92
1794405533 92
```
</details>

---

