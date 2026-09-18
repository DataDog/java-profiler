---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:34:10 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 811 |
| Sample Rate | 13.52/sec |
| Health Score | 845% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 75-77 cores)</summary>

```
1789719884 75
1789719889 75
1789719894 75
1789719899 75
1789719904 77
1789719909 77
1789719914 77
1789719919 77
1789719924 77
1789719929 77
1789719934 77
1789719939 77
1789719944 77
1789719949 77
1789719954 77
1789719959 75
1789719964 75
1789719969 77
1789719974 77
1789719979 77
```
</details>

---

