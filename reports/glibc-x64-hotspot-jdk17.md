---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-26 11:06:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1793026808 49
1793026813 49
1793026818 49
1793026823 49
1793026828 51
1793026833 51
1793026838 51
1793026843 51
1793026848 51
1793026853 51
1793026858 51
1793026863 51
1793026868 51
1793026873 51
1793026878 51
1793026883 51
1793026888 51
1793026893 51
1793026898 51
1793026903 51
```
</details>

---

