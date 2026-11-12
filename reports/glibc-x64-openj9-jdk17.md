---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 12:07:08 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 9 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794502913 32
1794502918 32
1794502923 32
1794502928 32
1794502933 32
1794502938 32
1794502943 32
1794502948 32
1794502953 32
1794502958 32
1794502963 32
1794502968 32
1794502973 32
1794502978 32
1794502983 32
1794502988 30
1794502993 30
1794502998 30
1794503003 30
1794503008 30
```
</details>

---

