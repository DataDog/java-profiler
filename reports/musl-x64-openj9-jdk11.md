---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:10:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (2 unique values: 53-70 cores)</summary>

```
1795107948 70
1795107953 70
1795107958 70
1795107963 70
1795107968 70
1795107973 70
1795107978 70
1795107983 70
1795107988 70
1795107993 70
1795107998 70
1795108003 70
1795108008 70
1795108014 53
1795108019 53
1795108024 53
1795108029 53
1795108034 53
1795108039 53
1795108044 53
```
</details>

---

