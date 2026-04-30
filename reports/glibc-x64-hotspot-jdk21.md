---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-30 09:02:44 EDT

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 10 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (6 unique values: 69-93 cores)</summary>

```
1777553844 69
1777553849 77
1777553854 77
1777553859 77
1777553864 77
1777553869 77
1777553874 89
1777553879 89
1777553884 89
1777553889 93
1777553894 93
1777553899 93
1777553904 93
1777553909 83
1777553914 83
1777553919 83
1777553924 83
1777553929 83
1777553934 83
1777553939 83
```
</details>

---

