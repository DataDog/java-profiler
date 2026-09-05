---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-04 22:42:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 73-81 cores)</summary>

```
1788575849 81
1788575854 81
1788575859 81
1788575864 81
1788575869 81
1788575874 81
1788575879 81
1788575884 81
1788575889 81
1788575894 81
1788575899 81
1788575904 81
1788575909 81
1788575914 81
1788575919 81
1788575924 81
1788575929 73
1788575934 73
1788575939 73
1788575944 73
```
</details>

---

