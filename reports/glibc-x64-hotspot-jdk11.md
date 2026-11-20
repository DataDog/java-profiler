---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 14:01:20 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 85 |
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
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 83-87 cores)</summary>

```
1795200961 83
1795200966 83
1795200971 83
1795200976 83
1795200981 83
1795200986 84
1795200991 84
1795200996 84
1795201001 84
1795201006 84
1795201011 84
1795201016 87
1795201021 87
1795201026 83
1795201031 83
1795201036 83
1795201041 83
1795201046 83
1795201051 83
1795201056 83
```
</details>

---

