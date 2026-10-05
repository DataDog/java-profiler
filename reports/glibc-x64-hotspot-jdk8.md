---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-05 05:22:38 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 357 |
| Sample Rate | 5.95/sec |
| Health Score | 372% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 73-81 cores)</summary>

```
1791191837 81
1791191842 81
1791191847 81
1791191852 73
1791191857 73
1791191862 73
1791191867 73
1791191872 73
1791191877 73
1791191882 73
1791191887 73
1791191892 73
1791191897 73
1791191902 73
1791191907 73
1791191912 73
1791191917 73
1791191922 73
1791191927 73
1791191932 73
```
</details>

---

