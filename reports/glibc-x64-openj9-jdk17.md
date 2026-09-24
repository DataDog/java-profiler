---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 06:19:00 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (3 unique values: 44-73 cores)</summary>

```
1790244818 49
1790244823 49
1790244828 49
1790244833 49
1790244838 49
1790244843 49
1790244849 49
1790244854 49
1790244859 49
1790244864 73
1790244869 73
1790244874 44
1790244879 44
1790244884 44
1790244889 44
1790244894 44
1790244899 44
1790244904 44
1790244909 44
1790244914 44
```
</details>

---

