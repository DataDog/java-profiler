---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 09:26:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 9 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 57-59 cores)</summary>

```
1795702946 57
1795702951 57
1795702956 57
1795702961 57
1795702966 57
1795702971 57
1795702976 57
1795702981 57
1795702986 57
1795702991 57
1795702996 57
1795703001 57
1795703006 57
1795703011 59
1795703016 59
1795703021 59
1795703026 59
1795703031 59
1795703036 59
1795703041 59
```
</details>

---

