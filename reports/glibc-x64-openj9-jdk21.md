---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:10:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 906 |
| Sample Rate | 15.10/sec |
| Health Score | 944% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 54-56 cores)</summary>

```
1795108031 56
1795108036 56
1795108041 56
1795108046 56
1795108051 56
1795108056 56
1795108061 56
1795108066 56
1795108071 56
1795108076 56
1795108082 56
1795108087 56
1795108092 56
1795108097 56
1795108102 56
1795108107 54
1795108112 54
1795108117 54
1795108122 54
1795108127 54
```
</details>

---

