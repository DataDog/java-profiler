---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-20 06:18:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1787220887 18
1787220892 18
1787220897 18
1787220902 18
1787220907 18
1787220912 18
1787220917 18
1787220922 18
1787220927 18
1787220932 18
1787220937 18
1787220942 18
1787220947 18
1787220952 18
1787220957 18
1787220962 18
1787220967 18
1787220972 18
1787220977 18
1787220982 13
```
</details>

---

