---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-30 21:21:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 937 |
| Sample Rate | 15.62/sec |
| Health Score | 976% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (3 unique values: 76-96 cores)</summary>

```
1788138988 76
1788138993 76
1788138998 76
1788139003 76
1788139008 76
1788139013 76
1788139018 76
1788139023 76
1788139028 96
1788139033 96
1788139038 96
1788139043 94
1788139048 94
1788139053 94
1788139058 94
1788139063 94
1788139068 94
1788139073 96
1788139078 96
1788139083 96
```
</details>

---

