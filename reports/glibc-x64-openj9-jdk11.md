---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-04 14:55:25 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 84-86 cores)</summary>

```
1788547933 86
1788547938 86
1788547943 86
1788547948 86
1788547953 84
1788547958 84
1788547963 84
1788547968 84
1788547973 84
1788547978 84
1788547983 84
1788547988 84
1788547993 84
1788547998 86
1788548003 86
1788548008 86
1788548013 86
1788548018 86
1788548023 86
1788548028 86
```
</details>

---

