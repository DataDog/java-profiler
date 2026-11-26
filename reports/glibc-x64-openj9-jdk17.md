---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 06:07:04 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 11 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 6 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (2 unique values: 76-78 cores)</summary>

```
1795690889 76
1795690894 76
1795690899 76
1795690904 76
1795690909 76
1795690914 76
1795690919 76
1795690924 76
1795690929 76
1795690934 76
1795690939 76
1795690944 76
1795690949 76
1795690954 76
1795690959 76
1795690964 78
1795690969 78
1795690974 78
1795690979 78
1795690984 78
```
</details>

---

