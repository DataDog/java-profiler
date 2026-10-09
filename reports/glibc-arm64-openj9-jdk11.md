---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-09 07:44:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 33-53 cores)</summary>

```
1791545967 33
1791545972 33
1791545977 33
1791545982 33
1791545987 33
1791545992 33
1791545997 33
1791546002 33
1791546007 33
1791546012 33
1791546017 33
1791546022 33
1791546027 33
1791546032 33
1791546037 33
1791546042 33
1791546047 33
1791546052 33
1791546057 33
1791546062 33
```
</details>

---

