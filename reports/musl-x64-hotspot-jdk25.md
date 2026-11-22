---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 16:32:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (5 unique values: 31-92 cores)</summary>

```
1795382906 31
1795382911 31
1795382916 31
1795382921 78
1795382926 78
1795382931 74
1795382936 74
1795382941 74
1795382946 74
1795382951 74
1795382956 74
1795382961 74
1795382966 74
1795382971 74
1795382976 74
1795382981 74
1795382986 83
1795382991 83
1795382996 92
1795383001 92
```
</details>

---

