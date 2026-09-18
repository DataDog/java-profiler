---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 04:28:56 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 10-30 cores)</summary>

```
1789719909 30
1789719914 30
1789719919 30
1789719924 30
1789719929 30
1789719934 10
1789719939 10
1789719944 12
1789719949 12
1789719954 12
1789719959 12
1789719964 12
1789719969 12
1789719974 12
1789719979 12
1789719984 12
1789719989 12
1789719994 12
1789719999 12
1789720004 12
```
</details>

---

