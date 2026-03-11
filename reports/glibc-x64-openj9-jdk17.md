---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-11 13:39:50 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 11 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1773250205 74
1773250210 74
1773250215 74
1773250220 74
1773250225 72
1773250230 72
1773250235 72
1773250240 72
1773250245 72
1773250250 72
1773250255 72
1773250260 72
1773250265 72
1773250270 72
1773250275 72
1773250280 72
1773250285 72
1773250290 72
1773250295 72
1773250300 72
```
</details>

---

