---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:08:09 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 805 |
| Sample Rate | 13.42/sec |
| Health Score | 839% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (4 unique values: 53-67 cores)</summary>

```
1795618876 53
1795618881 53
1795618886 53
1795618891 58
1795618896 58
1795618901 58
1795618906 58
1795618911 58
1795618916 58
1795618921 58
1795618926 58
1795618931 58
1795618936 58
1795618941 58
1795618946 58
1795618951 58
1795618956 58
1795618961 58
1795618966 67
1795618971 67
```
</details>

---

