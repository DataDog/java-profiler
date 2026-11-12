---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 12:07:08 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 10 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (5 unique values: 81-89 cores)</summary>

```
1794502899 81
1794502904 81
1794502909 81
1794502914 81
1794502919 84
1794502924 84
1794502929 84
1794502934 84
1794502939 86
1794502944 86
1794502949 86
1794502954 86
1794502959 86
1794502964 86
1794502969 86
1794502974 86
1794502979 89
1794502984 89
1794502989 89
1794502994 89
```
</details>

---

