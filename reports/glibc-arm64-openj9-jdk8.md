---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-20 06:18:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 37 |
| Sample Rate | 0.62/sec |
| Health Score | 39% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1787220896 59
1787220901 59
1787220907 59
1787220912 59
1787220917 59
1787220922 59
1787220927 59
1787220932 59
1787220937 59
1787220942 59
1787220947 59
1787220952 59
1787220957 59
1787220962 59
1787220967 59
1787220972 59
1787220977 59
1787220982 59
1787220987 59
1787220992 54
```
</details>

---

