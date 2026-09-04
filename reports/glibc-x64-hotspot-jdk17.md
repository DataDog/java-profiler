---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-04 14:55:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1788547918 94
1788547923 94
1788547928 96
1788547933 96
1788547938 96
1788547943 96
1788547948 96
1788547953 96
1788547958 96
1788547963 96
1788547968 96
1788547973 96
1788547978 96
1788547983 96
1788547988 96
1788547993 96
1788547998 96
1788548003 96
1788548008 96
1788548013 96
```
</details>

---

