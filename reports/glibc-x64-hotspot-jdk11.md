---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 09:26:37 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 49-59 cores)</summary>

```
1795702942 52
1795702947 49
1795702952 49
1795702957 49
1795702962 49
1795702967 49
1795702972 49
1795702977 49
1795702982 49
1795702987 49
1795702992 49
1795702997 49
1795703002 49
1795703007 49
1795703012 49
1795703017 49
1795703022 49
1795703027 49
1795703032 49
1795703037 49
```
</details>

---

