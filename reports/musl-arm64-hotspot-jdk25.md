---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-04 22:42:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 12 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1788575859 14
1788575864 14
1788575869 14
1788575874 34
1788575879 34
1788575884 34
1788575889 34
1788575894 34
1788575899 34
1788575904 34
1788575909 34
1788575914 34
1788575919 34
1788575924 34
1788575930 34
1788575935 34
1788575940 34
1788575945 34
1788575950 34
1788575955 34
```
</details>

---

