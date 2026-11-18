---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 08:22:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1795007933 70
1795007938 70
1795007943 70
1795007948 70
1795007953 70
1795007958 70
1795007963 70
1795007968 70
1795007973 70
1795007978 72
1795007983 72
1795007988 72
1795007993 72
1795007998 72
1795008003 72
1795008008 72
1795008013 72
1795008018 72
1795008023 72
1795008028 72
```
</details>

---

