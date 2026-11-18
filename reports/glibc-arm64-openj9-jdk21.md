---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 08:22:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795007974 64
1795007979 64
1795007984 64
1795007989 64
1795007994 64
1795007999 64
1795008004 64
1795008009 64
1795008014 64
1795008019 64
1795008024 64
1795008029 64
1795008034 64
1795008039 64
1795008044 64
1795008049 64
1795008054 64
1795008059 64
1795008064 64
1795008069 64
```
</details>

---

