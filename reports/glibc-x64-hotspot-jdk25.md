---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 11:52:08 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 51-74 cores)</summary>

```
1790091814 51
1790091819 51
1790091824 51
1790091829 74
1790091834 74
1790091839 51
1790091844 51
1790091849 51
1790091854 51
1790091859 51
1790091864 51
1790091869 51
1790091874 51
1790091879 53
1790091884 53
1790091889 53
1790091894 53
1790091899 53
1790091904 53
1790091909 53
```
</details>

---

