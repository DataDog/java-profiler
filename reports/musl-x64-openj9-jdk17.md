---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:10:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 985 |
| Sample Rate | 16.42/sec |
| Health Score | 1026% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 66-87 cores)</summary>

```
1795107951 66
1795107956 66
1795107961 66
1795107966 66
1795107971 66
1795107976 66
1795107981 87
1795107986 87
1795107991 85
1795107996 85
1795108001 85
1795108006 85
1795108011 85
1795108016 85
1795108021 85
1795108026 85
1795108031 85
1795108036 85
1795108041 85
1795108046 85
```
</details>

---

