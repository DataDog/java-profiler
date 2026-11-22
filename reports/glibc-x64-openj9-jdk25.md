---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 15:55:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 366 |
| Sample Rate | 6.10/sec |
| Health Score | 381% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 25-66 cores)</summary>

```
1795380695 25
1795380700 25
1795380705 25
1795380710 58
1795380715 58
1795380720 58
1795380725 58
1795380730 58
1795380735 58
1795380740 66
1795380745 66
1795380750 66
1795380755 66
1795380760 66
1795380765 66
1795380770 66
1795380775 66
1795380780 66
1795380785 66
1795380790 66
```
</details>

---

