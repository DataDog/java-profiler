---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 11:47:27 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 86-96 cores)</summary>

```
1793374895 96
1793374900 96
1793374905 86
1793374910 86
1793374915 86
1793374920 86
1793374925 86
1793374930 86
1793374935 86
1793374940 86
1793374945 86
1793374950 86
1793374955 86
1793374960 86
1793374965 86
1793374970 86
1793374975 86
1793374980 86
1793374985 86
1793374990 86
```
</details>

---

