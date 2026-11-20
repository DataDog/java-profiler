---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 05:56:27 EST

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
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (5 unique values: 73-81 cores)</summary>

```
1795171842 81
1795171847 81
1795171852 79
1795171857 79
1795171862 77
1795171867 77
1795171872 77
1795171877 77
1795171882 77
1795171887 77
1795171892 77
1795171897 77
1795171902 77
1795171907 77
1795171912 77
1795171917 77
1795171922 77
1795171927 77
1795171932 77
1795171937 75
```
</details>

---

