---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 13:29:10 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 55 |
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
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 55-58 cores)</summary>

```
1794939934 56
1794939939 56
1794939944 56
1794939949 56
1794939954 56
1794939959 56
1794939964 56
1794939969 56
1794939974 56
1794939979 56
1794939984 56
1794939989 58
1794939994 58
1794939999 58
1794940004 58
1794940009 58
1794940014 58
1794940019 58
1794940024 58
1794940029 58
```
</details>

---

