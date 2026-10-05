---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-05 05:22:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 71-81 cores)</summary>

```
1791191818 71
1791191823 71
1791191828 71
1791191833 71
1791191838 71
1791191843 71
1791191848 81
1791191853 81
1791191858 81
1791191863 81
1791191868 78
1791191873 78
1791191878 78
1791191883 78
1791191888 78
1791191893 78
1791191898 78
1791191903 78
1791191908 78
1791191913 78
```
</details>

---

