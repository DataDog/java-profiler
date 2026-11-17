---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 13:29:10 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 68-70 cores)</summary>

```
1794939899 68
1794939904 68
1794939909 68
1794939914 68
1794939919 68
1794939924 68
1794939929 68
1794939934 70
1794939939 70
1794939944 68
1794939949 68
1794939954 68
1794939959 68
1794939964 68
1794939969 68
1794939974 68
1794939979 68
1794939984 68
1794939989 68
1794939994 70
```
</details>

---

