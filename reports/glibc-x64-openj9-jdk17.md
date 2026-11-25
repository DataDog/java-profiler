---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:08:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 10 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 75-78 cores)</summary>

```
1795618901 75
1795618906 75
1795618911 75
1795618916 75
1795618921 75
1795618926 75
1795618931 75
1795618936 75
1795618941 78
1795618946 78
1795618951 78
1795618956 78
1795618961 78
1795618966 78
1795618971 78
1795618976 78
1795618981 78
1795618986 78
1795618991 78
1795618996 78
```
</details>

---

