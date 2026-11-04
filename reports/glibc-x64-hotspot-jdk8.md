---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-04 05:47:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 44-54 cores)</summary>

```
1793788921 46
1793788926 46
1793788931 46
1793788936 44
1793788941 44
1793788946 44
1793788951 44
1793788956 44
1793788961 44
1793788966 44
1793788971 44
1793788976 44
1793788981 44
1793788986 44
1793788991 44
1793788996 44
1793789001 44
1793789006 44
1793789011 44
1793789016 44
```
</details>

---

