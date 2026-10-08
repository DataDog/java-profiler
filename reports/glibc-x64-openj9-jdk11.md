---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-08 10:53:14 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 813 |
| Sample Rate | 13.55/sec |
| Health Score | 847% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1791470854 73
1791470859 73
1791470864 73
1791470869 71
1791470874 71
1791470879 71
1791470884 71
1791470889 71
1791470894 73
1791470899 73
1791470904 73
1791470909 73
1791470914 73
1791470919 73
1791470924 73
1791470929 73
1791470934 73
1791470939 73
1791470944 73
1791470949 73
```
</details>

---

