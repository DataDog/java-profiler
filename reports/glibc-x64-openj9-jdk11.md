---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 07:37:32 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 937 |
| Sample Rate | 15.62/sec |
| Health Score | 976% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 34-40 cores)</summary>

```
1790336008 34
1790336013 34
1790336018 40
1790336023 40
1790336028 40
1790336033 40
1790336038 38
1790336043 38
1790336048 38
1790336053 38
1790336058 38
1790336063 38
1790336068 38
1790336073 38
1790336078 38
1790336083 38
1790336088 40
1790336093 40
1790336098 40
1790336103 40
```
</details>

---

