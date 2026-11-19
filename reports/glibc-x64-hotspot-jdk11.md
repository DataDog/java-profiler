---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:10:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (5 unique values: 58-69 cores)</summary>

```
1795107976 63
1795107981 63
1795107986 60
1795107991 60
1795107996 58
1795108001 58
1795108006 58
1795108011 58
1795108016 58
1795108021 58
1795108026 58
1795108031 58
1795108036 58
1795108041 60
1795108046 60
1795108051 67
1795108056 67
1795108061 67
1795108066 67
1795108071 69
```
</details>

---

