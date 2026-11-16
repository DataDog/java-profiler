---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 19:49:08 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 880 |
| Sample Rate | 14.67/sec |
| Health Score | 917% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 73-94 cores)</summary>

```
1794789909 76
1794789914 76
1794789919 76
1794789924 76
1794789929 76
1794789934 76
1794789939 76
1794789944 76
1794789949 76
1794789954 76
1794789959 76
1794789964 76
1794789969 76
1794789974 94
1794789979 94
1794789984 94
1794789989 94
1794789995 94
1794790000 94
1794790005 94
```
</details>

---

