---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 05:15:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 52-61 cores)</summary>

```
1795514974 61
1795514979 52
1795514984 52
1795514989 52
1795514994 52
1795514999 52
1795515004 52
1795515009 52
1795515014 52
1795515019 52
1795515024 52
1795515029 54
1795515034 54
1795515039 52
1795515044 52
1795515049 55
1795515054 55
1795515059 55
1795515064 55
1795515069 55
```
</details>

---

