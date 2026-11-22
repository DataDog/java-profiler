---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 16:32:53 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (6 unique values: 45-81 cores)</summary>

```
1795382884 45
1795382889 45
1795382894 45
1795382899 45
1795382904 47
1795382909 47
1795382914 49
1795382919 49
1795382924 47
1795382929 47
1795382934 47
1795382939 47
1795382944 47
1795382949 47
1795382954 47
1795382959 47
1795382964 47
1795382969 49
1795382974 49
1795382979 58
```
</details>

---

