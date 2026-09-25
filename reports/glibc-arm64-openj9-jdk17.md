---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-25 07:37:31 EDT

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
| CPU Cores (start) | 7 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 11 |
| Allocations | 193 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 5 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 7-27 cores)</summary>

```
1790336003 7
1790336008 7
1790336013 7
1790336018 7
1790336023 7
1790336028 7
1790336033 7
1790336038 7
1790336043 7
1790336048 7
1790336053 7
1790336058 7
1790336063 7
1790336068 7
1790336073 27
1790336078 27
1790336083 27
1790336088 27
1790336093 27
1790336098 27
```
</details>

---

