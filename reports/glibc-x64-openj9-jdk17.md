---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 05:53:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 8 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (3 unique values: 25-33 cores)</summary>

```
1795603834 28
1795603839 28
1795603844 28
1795603849 28
1795603854 28
1795603859 28
1795603864 28
1795603869 28
1795603874 28
1795603879 28
1795603884 28
1795603889 28
1795603894 28
1795603899 28
1795603904 28
1795603909 28
1795603914 28
1795603919 25
1795603924 25
1795603929 25
```
</details>

---

