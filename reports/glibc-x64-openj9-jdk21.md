---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 05:15:28 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (3 unique values: 49-53 cores)</summary>

```
1795514989 53
1795514994 53
1795514999 53
1795515004 51
1795515009 51
1795515014 51
1795515019 51
1795515024 51
1795515029 51
1795515034 51
1795515039 49
1795515044 49
1795515049 49
1795515054 49
1795515059 51
1795515064 51
1795515069 51
1795515074 51
1795515079 51
1795515084 51
```
</details>

---

