---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 13:32:32 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 46-71 cores)</summary>

```
1793816895 71
1793816901 71
1793816906 71
1793816911 71
1793816916 65
1793816921 65
1793816926 67
1793816931 67
1793816936 67
1793816941 46
1793816946 46
1793816951 46
1793816956 46
1793816961 46
1793816966 46
1793816971 46
1793816976 46
1793816981 46
1793816986 46
1793816991 46
```
</details>

---

