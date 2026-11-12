---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:09:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (5 unique values: 82-89 cores)</summary>

```
1794495896 84
1794495901 84
1794495906 84
1794495911 84
1794495916 89
1794495921 89
1794495926 89
1794495931 89
1794495936 89
1794495941 89
1794495946 89
1794495951 87
1794495956 87
1794495961 87
1794495966 87
1794495971 87
1794495976 85
1794495981 85
1794495986 85
1794495991 87
```
</details>

---

