---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:10:56 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 65-67 cores)</summary>

```
1795107948 66
1795107953 66
1795107958 66
1795107963 65
1795107968 65
1795107973 65
1795107978 65
1795107983 65
1795107988 65
1795107993 65
1795107998 65
1795108003 65
1795108008 65
1795108013 65
1795108018 65
1795108023 67
1795108028 67
1795108033 67
1795108039 67
1795108044 65
```
</details>

---

