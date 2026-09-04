---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-04 14:55:25 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 80-96 cores)</summary>

```
1788547932 96
1788547937 96
1788547943 96
1788547948 80
1788547953 80
1788547958 80
1788547963 80
1788547968 80
1788547973 80
1788547978 80
1788547983 80
1788547988 80
1788547993 80
1788547998 80
1788548003 80
1788548008 80
1788548013 80
1788548018 80
1788548023 80
1788548028 80
```
</details>

---

