---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-04 14:55:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 348 |
| Sample Rate | 5.80/sec |
| Health Score | 362% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 68-76 cores)</summary>

```
1788547918 68
1788547923 68
1788547928 68
1788547933 68
1788547938 68
1788547943 68
1788547948 68
1788547953 70
1788547958 70
1788547963 76
1788547968 76
1788547973 76
1788547978 76
1788547983 76
1788547988 76
1788547993 76
1788547998 76
1788548003 76
1788548008 76
1788548013 76
```
</details>

---

