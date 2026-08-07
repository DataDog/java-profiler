---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-07 14:42:22 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (4 unique values: 20-32 cores)</summary>

```
1786127876 27
1786127881 27
1786127886 27
1786127891 27
1786127896 27
1786127901 27
1786127906 29
1786127911 29
1786127916 29
1786127921 29
1786127926 29
1786127931 29
1786127936 29
1786127941 29
1786127946 32
1786127951 32
1786127956 32
1786127961 32
1786127966 32
1786127971 32
```
</details>

---

