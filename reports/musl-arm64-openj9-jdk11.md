---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:08:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 13 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 33-44 cores)</summary>

```
1795618916 33
1795618921 33
1795618926 33
1795618931 33
1795618936 33
1795618941 33
1795618946 44
1795618951 44
1795618956 44
1795618961 44
1795618966 44
1795618971 44
1795618976 44
1795618981 44
1795618986 44
1795618991 44
1795618996 44
1795619001 44
1795619006 44
1795619011 44
```
</details>

---

