---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 12:19:50 EST

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 18.10/sec |
| Health Score | 1131% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 26.17/sec |
| Health Score | 1636% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (4 unique values: 19-44 cores)</summary>

```
1769706805 20
1769706810 20
1769706815 20
1769706820 20
1769706825 20
1769706830 20
1769706835 20
1769706840 20
1769706845 20
1769706850 44
1769706855 44
1769706860 24
1769706865 24
1769706870 19
1769706875 19
1769706880 19
1769706885 19
1769706890 19
1769706895 19
1769706900 19
```
</details>

---

