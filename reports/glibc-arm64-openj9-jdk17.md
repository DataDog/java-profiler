---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 14:37:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1786386839 34
1786386844 34
1786386849 34
1786386854 34
1786386859 34
1786386864 34
1786386869 34
1786386874 34
1786386879 34
1786386884 34
1786386889 34
1786386894 34
1786386899 34
1786386904 34
1786386909 34
1786386914 14
1786386919 14
1786386924 14
1786386929 14
1786386934 14
```
</details>

---

