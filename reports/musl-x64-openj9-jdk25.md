---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 04:47:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 11 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 75-78 cores)</summary>

```
1795426898 78
1795426903 78
1795426908 78
1795426913 78
1795426918 78
1795426923 78
1795426928 75
1795426933 75
1795426938 75
1795426943 75
1795426948 75
1795426953 75
1795426958 75
1795426963 75
1795426968 75
1795426973 75
1795426978 75
1795426983 75
1795426988 75
1795426993 75
```
</details>

---

