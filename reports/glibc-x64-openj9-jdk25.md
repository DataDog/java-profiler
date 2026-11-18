---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 08:22:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 60-81 cores)</summary>

```
1795007925 76
1795007930 76
1795007935 81
1795007940 81
1795007945 81
1795007950 81
1795007955 81
1795007960 81
1795007965 60
1795007970 60
1795007975 60
1795007980 60
1795007985 60
1795007990 60
1795007995 60
1795008000 60
1795008005 60
1795008010 60
1795008015 60
1795008020 60
```
</details>

---

