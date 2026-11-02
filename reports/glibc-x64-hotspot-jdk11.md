---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 09:51:40 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 817 |
| Sample Rate | 13.62/sec |
| Health Score | 851% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (5 unique values: 59-73 cores)</summary>

```
1793630819 71
1793630824 71
1793630829 71
1793630834 71
1793630839 71
1793630844 71
1793630849 71
1793630854 71
1793630859 71
1793630864 71
1793630869 71
1793630874 73
1793630879 73
1793630884 73
1793630889 70
1793630894 70
1793630899 70
1793630904 70
1793630909 70
1793630914 70
```
</details>

---

