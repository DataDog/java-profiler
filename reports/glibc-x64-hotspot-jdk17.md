---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 15:45:15 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 85-89 cores)</summary>

```
1794861604 85
1794861609 85
1794861614 85
1794861619 87
1794861624 87
1794861629 87
1794861634 87
1794861639 87
1794861644 87
1794861649 87
1794861654 89
1794861659 89
1794861664 89
1794861669 89
1794861674 89
1794861679 89
1794861684 86
1794861689 86
1794861694 86
1794861699 86
```
</details>

---

