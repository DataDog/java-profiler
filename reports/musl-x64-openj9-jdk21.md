---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-10 13:36:41 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 12 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 957 |
| Sample Rate | 15.95/sec |
| Health Score | 997% |
| Threads | 13 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (5 unique values: 64-75 cores)</summary>

```
1773163864 64
1773163869 68
1773163874 68
1773163879 68
1773163884 68
1773163889 68
1773163894 68
1773163899 68
1773163904 68
1773163909 68
1773163914 68
1773163919 68
1773163924 70
1773163929 70
1773163934 70
1773163939 70
1773163944 71
1773163949 71
1773163954 71
1773163959 71
```
</details>

---

