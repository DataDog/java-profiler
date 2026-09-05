---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-04 22:42:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1788575849 59
1788575854 59
1788575859 59
1788575864 59
1788575869 59
1788575874 59
1788575879 59
1788575884 61
1788575889 61
1788575894 61
1788575899 61
1788575904 61
1788575909 61
1788575914 61
1788575919 61
1788575924 61
1788575929 61
1788575934 61
1788575939 61
1788575944 61
```
</details>

---

