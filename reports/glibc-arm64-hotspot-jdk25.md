---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 08:47:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 11 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1794922974 46
1794922979 46
1794922984 46
1794922989 46
1794922994 46
1794922999 46
1794923004 46
1794923009 46
1794923014 46
1794923019 46
1794923024 46
1794923029 46
1794923034 46
1794923039 46
1794923044 46
1794923049 46
1794923054 41
1794923059 41
1794923064 41
1794923069 41
```
</details>

---

