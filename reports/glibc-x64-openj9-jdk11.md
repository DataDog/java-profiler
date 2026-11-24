---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 12:58:06 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 47 |
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
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 47-79 cores)</summary>

```
1795542793 77
1795542798 77
1795542803 77
1795542808 77
1795542813 79
1795542818 79
1795542823 79
1795542828 79
1795542833 79
1795542838 79
1795542843 79
1795542848 79
1795542853 79
1795542858 79
1795542863 79
1795542868 79
1795542873 77
1795542878 77
1795542883 77
1795542888 77
```
</details>

---

