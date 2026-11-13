---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 08:55:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 68-70 cores)</summary>

```
1794577857 70
1794577862 70
1794577867 70
1794577872 70
1794577877 70
1794577882 70
1794577887 70
1794577892 70
1794577897 70
1794577902 70
1794577907 70
1794577912 70
1794577917 68
1794577922 68
1794577927 68
1794577932 68
1794577937 68
1794577942 68
1794577947 68
1794577952 68
```
</details>

---

