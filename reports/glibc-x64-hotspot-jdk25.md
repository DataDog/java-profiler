---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 18:20:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 32-56 cores)</summary>

```
1794438918 52
1794438923 52
1794438928 32
1794438933 32
1794438938 32
1794438943 32
1794438948 32
1794438953 32
1794438958 54
1794438963 54
1794438968 56
1794438973 56
1794438978 56
1794438983 56
1794438988 56
1794438993 56
1794438998 56
1794439003 56
1794439008 56
1794439013 56
```
</details>

---

