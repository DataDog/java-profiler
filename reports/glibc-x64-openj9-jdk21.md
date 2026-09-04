---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-04 14:55:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1788547923 94
1788547928 94
1788547933 94
1788547938 94
1788547943 92
1788547948 92
1788547953 92
1788547958 92
1788547963 92
1788547968 92
1788547973 92
1788547978 92
1788547983 96
1788547988 96
1788547993 96
1788547998 96
1788548003 96
1788548008 96
1788548013 96
1788548018 96
```
</details>

---

