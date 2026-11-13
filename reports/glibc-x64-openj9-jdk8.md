---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-13 08:55:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 53-56 cores)</summary>

```
1794577846 56
1794577851 56
1794577856 56
1794577861 56
1794577866 56
1794577871 56
1794577876 56
1794577881 56
1794577886 56
1794577891 53
1794577896 53
1794577901 53
1794577906 53
1794577911 53
1794577916 53
1794577921 53
1794577926 53
1794577931 53
1794577936 53
1794577941 53
```
</details>

---

