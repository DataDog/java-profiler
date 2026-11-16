---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 08:52:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 366 |
| Sample Rate | 6.10/sec |
| Health Score | 381% |
| Threads | 10 |
| Allocations | 192 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 14 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794836813 48
1794836818 48
1794836823 48
1794836828 48
1794836833 43
1794836839 43
1794836844 43
1794836849 43
1794836854 43
1794836859 43
1794836864 43
1794836869 43
1794836874 43
1794836879 43
1794836884 43
1794836889 43
1794836894 43
1794836899 43
1794836904 43
1794836909 48
```
</details>

---

