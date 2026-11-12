---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 10:09:36 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 9 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (6 unique values: 80-88 cores)</summary>

```
1794495911 88
1794495916 88
1794495921 88
1794495926 88
1794495931 88
1794495936 88
1794495941 86
1794495946 86
1794495951 86
1794495956 86
1794495961 86
1794495966 84
1794495971 84
1794495976 84
1794495981 84
1794495986 84
1794495991 84
1794495996 81
1794496001 81
1794496006 80
```
</details>

---

