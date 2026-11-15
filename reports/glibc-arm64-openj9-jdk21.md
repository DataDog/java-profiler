---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 16:13:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 11 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1794776939 38
1794776944 38
1794776949 38
1794776954 38
1794776959 38
1794776964 38
1794776969 38
1794776974 38
1794776979 38
1794776984 38
1794776989 38
1794776994 38
1794776999 38
1794777004 38
1794777009 38
1794777014 38
1794777019 38
1794777024 38
1794777029 51
1794777034 51
```
</details>

---

