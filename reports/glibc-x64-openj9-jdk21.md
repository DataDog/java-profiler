---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 05:47:33 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 11 |
| Allocations | 412 |

<details>
<summary>CPU Timeline (2 unique values: 67-69 cores)</summary>

```
1793788963 67
1793788968 67
1793788973 67
1793788978 67
1793788983 67
1793788988 67
1793788993 67
1793788998 67
1793789003 67
1793789008 67
1793789013 67
1793789018 67
1793789023 67
1793789028 67
1793789033 67
1793789038 69
1793789043 69
1793789048 69
1793789053 69
1793789058 69
```
</details>

---

