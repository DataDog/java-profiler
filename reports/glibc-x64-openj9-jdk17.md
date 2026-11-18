---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:20:03 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 11 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (2 unique values: 76-78 cores)</summary>

```
1795014934 78
1795014939 78
1795014944 78
1795014949 78
1795014954 78
1795014959 78
1795014964 78
1795014969 78
1795014974 78
1795014979 78
1795014984 78
1795014989 78
1795014994 78
1795014999 78
1795015004 76
1795015009 76
1795015014 76
1795015019 76
1795015024 76
1795015029 76
```
</details>

---

