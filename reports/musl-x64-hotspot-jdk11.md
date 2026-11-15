---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 16:40:28 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 8 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 59-84 cores)</summary>

```
1794778443 59
1794778448 59
1794778453 59
1794778458 59
1794778463 59
1794778468 59
1794778473 59
1794778478 59
1794778483 79
1794778488 79
1794778493 79
1794778498 79
1794778503 79
1794778508 79
1794778513 84
1794778518 84
1794778523 84
1794778528 84
1794778533 84
1794778538 84
```
</details>

---

