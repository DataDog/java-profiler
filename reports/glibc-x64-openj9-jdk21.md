---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:28:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 66-68 cores)</summary>

```
1795630969 66
1795630974 68
1795630979 68
1795630984 68
1795630989 68
1795630994 68
1795630999 68
1795631004 68
1795631009 68
1795631014 68
1795631019 68
1795631024 66
1795631029 66
1795631034 66
1795631039 66
1795631044 66
1795631049 66
1795631054 66
1795631059 66
1795631064 66
```
</details>

---

