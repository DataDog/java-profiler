---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:10:54 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 75-80 cores)</summary>

```
1795107982 80
1795107987 80
1795107992 80
1795107997 80
1795108002 80
1795108007 80
1795108012 80
1795108017 80
1795108022 80
1795108027 80
1795108032 80
1795108037 80
1795108042 77
1795108047 77
1795108052 77
1795108057 79
1795108062 79
1795108067 79
1795108072 79
1795108077 77
```
</details>

---

