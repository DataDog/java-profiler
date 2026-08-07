---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-07 05:50:44 EDT

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
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1786095973 96
1786095978 96
1786095983 96
1786095988 96
1786095993 96
1786095998 96
1786096003 96
1786096008 96
1786096013 96
1786096018 96
1786096023 96
1786096028 96
1786096033 96
1786096038 96
1786096043 96
1786096048 96
1786096053 96
1786096058 88
1786096063 88
1786096068 88
```
</details>

---

