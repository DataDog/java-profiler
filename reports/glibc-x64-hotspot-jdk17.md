---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-28 14:02:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (5 unique values: 58-66 cores)</summary>

```
1787939896 66
1787939901 66
1787939906 66
1787939911 66
1787939916 66
1787939921 66
1787939926 66
1787939931 66
1787939936 66
1787939941 64
1787939946 64
1787939951 64
1787939956 60
1787939961 60
1787939966 58
1787939971 58
1787939976 58
1787939981 58
1787939986 58
1787939991 60
```
</details>

---

