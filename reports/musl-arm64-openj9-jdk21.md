---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-04 22:42:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1788575849 29
1788575854 29
1788575859 29
1788575864 29
1788575869 29
1788575874 29
1788575879 29
1788575884 29
1788575889 29
1788575894 29
1788575899 29
1788575904 29
1788575909 29
1788575914 29
1788575919 29
1788575924 29
1788575929 29
1788575934 34
1788575939 34
1788575944 34
```
</details>

---

