---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 07:04:04 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 9 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 65-73 cores)</summary>

```
1795175969 65
1795175974 65
1795175979 65
1795175984 68
1795175989 68
1795175994 68
1795175999 68
1795176004 68
1795176009 68
1795176014 66
1795176019 66
1795176024 66
1795176029 66
1795176034 66
1795176039 66
1795176044 66
1795176049 66
1795176054 66
1795176059 66
1795176064 66
```
</details>

---

