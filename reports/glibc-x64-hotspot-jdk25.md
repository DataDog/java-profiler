---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 09:24:34 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (5 unique values: 25-87 cores)</summary>

```
1795702839 25
1795702844 42
1795702849 42
1795702854 42
1795702859 42
1795702864 59
1795702869 59
1795702874 59
1795702879 59
1795702884 59
1795702889 59
1795702894 59
1795702899 59
1795702904 59
1795702909 59
1795702914 59
1795702919 87
1795702924 87
1795702929 87
1795702934 87
```
</details>

---

