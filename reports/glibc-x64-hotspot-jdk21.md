---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 11:11:47 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 10 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 12 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 75-89 cores)</summary>

```
1770134729 89
1770134734 89
1770134739 89
1770134744 89
1770134749 79
1770134754 79
1770134759 79
1770134764 79
1770134769 79
1770134774 79
1770134779 79
1770134784 79
1770134789 79
1770134794 79
1770134799 79
1770134804 79
1770134809 75
1770134814 75
1770134819 75
1770134824 75
```
</details>

---

