---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 10:18:51 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 44-46 cores)</summary>

```
1795706006 46
1795706011 46
1795706016 46
1795706021 44
1795706026 44
1795706031 44
1795706036 44
1795706041 44
1795706046 44
1795706051 44
1795706056 44
1795706061 44
1795706066 44
1795706071 44
1795706076 44
1795706081 44
1795706086 44
1795706091 44
1795706096 44
1795706101 44
```
</details>

---

