---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 04:47:04 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 363 |
| Sample Rate | 6.05/sec |
| Health Score | 378% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 66-73 cores)</summary>

```
1789979929 68
1789979934 68
1789979939 68
1789979944 68
1789979949 68
1789979954 68
1789979959 68
1789979964 68
1789979969 68
1789979974 68
1789979979 66
1789979984 66
1789979989 66
1789979994 66
1789979999 66
1789980004 66
1789980009 66
1789980014 66
1789980019 66
1789980024 68
```
</details>

---

