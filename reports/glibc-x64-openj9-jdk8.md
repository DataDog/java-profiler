---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-03 12:51:40 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 165 |
| Sample Rate | 2.75/sec |
| Health Score | 172% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 73-77 cores)</summary>

```
1793727963 75
1793727968 75
1793727973 73
1793727978 73
1793727983 73
1793727988 73
1793727993 73
1793727998 73
1793728003 77
1793728008 77
1793728013 77
1793728018 77
1793728023 77
1793728028 77
1793728033 77
1793728038 77
1793728043 77
1793728048 77
1793728053 77
1793728058 77
```
</details>

---

