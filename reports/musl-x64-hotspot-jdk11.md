---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-13 16:15:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 846 |
| Sample Rate | 14.10/sec |
| Health Score | 881% |
| Threads | 10 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1786651849 96
1786651854 96
1786651859 96
1786651864 96
1786651869 96
1786651874 96
1786651879 96
1786651884 96
1786651889 96
1786651894 96
1786651899 96
1786651904 96
1786651909 96
1786651914 96
1786651919 96
1786651924 96
1786651929 96
1786651934 96
1786651939 96
1786651944 76
```
</details>

---

