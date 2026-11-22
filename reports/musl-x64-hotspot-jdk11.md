---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-22 16:32:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 9 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 54-87 cores)</summary>

```
1795382909 54
1795382914 54
1795382919 54
1795382924 54
1795382929 87
1795382934 87
1795382939 87
1795382944 87
1795382949 87
1795382954 87
1795382959 87
1795382964 87
1795382969 87
1795382974 87
1795382979 87
1795382984 87
1795382989 87
1795382994 87
1795382999 87
1795383004 87
```
</details>

---

