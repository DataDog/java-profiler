---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-04 04:47:51 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 869 |
| Sample Rate | 14.48/sec |
| Health Score | 905% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1777884076 32
1777884081 32
1777884086 32
1777884091 32
1777884096 32
1777884101 32
1777884106 32
1777884111 32
1777884116 32
1777884121 32
1777884126 32
1777884131 32
1777884136 32
1777884141 32
1777884146 32
1777884151 32
1777884156 32
1777884161 32
1777884166 32
1777884171 28
```
</details>

---

