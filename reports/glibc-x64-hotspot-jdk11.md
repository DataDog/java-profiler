---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 10:28:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 23-26 cores)</summary>

```
1794842620 26
1794842625 26
1794842630 24
1794842635 24
1794842640 24
1794842645 24
1794842650 24
1794842655 24
1794842660 24
1794842665 24
1794842670 24
1794842675 24
1794842680 24
1794842685 24
1794842690 24
1794842695 24
1794842700 23
1794842705 23
1794842710 23
1794842715 23
```
</details>

---

