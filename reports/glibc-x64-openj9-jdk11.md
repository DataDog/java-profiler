---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 12:07:08 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (5 unique values: 81-89 cores)</summary>

```
1794502881 85
1794502886 85
1794502891 85
1794502896 85
1794502901 81
1794502906 81
1794502911 81
1794502916 81
1794502921 81
1794502926 84
1794502931 84
1794502936 86
1794502941 86
1794502946 86
1794502951 86
1794502956 86
1794502961 86
1794502966 86
1794502971 86
1794502976 86
```
</details>

---

