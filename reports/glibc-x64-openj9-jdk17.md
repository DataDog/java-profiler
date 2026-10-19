---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 07:26:49 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 12-17 cores)</summary>

```
1792408963 12
1792408968 12
1792408973 12
1792408978 12
1792408983 17
1792408988 17
1792408993 17
1792408998 17
1792409003 17
1792409008 17
1792409013 17
1792409018 17
1792409023 17
1792409028 17
1792409033 17
1792409038 17
1792409043 17
1792409048 17
1792409053 17
1792409058 17
```
</details>

---

