---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 16:32:02 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 941 |
| Sample Rate | 15.68/sec |
| Health Score | 980% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1795382916 72
1795382921 74
1795382926 74
1795382931 72
1795382936 72
1795382941 72
1795382946 72
1795382951 72
1795382956 72
1795382961 72
1795382966 72
1795382971 72
1795382976 72
1795382981 72
1795382986 72
1795382991 72
1795382996 72
1795383001 72
1795383006 72
1795383011 72
```
</details>

---

