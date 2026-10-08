---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-08 12:33:19 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (5 unique values: 87-94 cores)</summary>

```
1791476932 92
1791476937 92
1791476942 92
1791476947 92
1791476952 92
1791476957 92
1791476962 92
1791476967 94
1791476972 94
1791476977 91
1791476982 91
1791476988 91
1791476993 91
1791476998 91
1791477003 91
1791477008 91
1791477013 89
1791477018 89
1791477023 89
1791477028 89
```
</details>

---

