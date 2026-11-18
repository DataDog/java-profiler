---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 13:43:06 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 59-83 cores)</summary>

```
1795027100 61
1795027105 61
1795027110 61
1795027115 61
1795027120 61
1795027125 61
1795027130 61
1795027135 61
1795027140 61
1795027145 61
1795027150 59
1795027155 59
1795027160 59
1795027165 59
1795027170 61
1795027175 61
1795027180 61
1795027185 61
1795027190 61
1795027195 61
```
</details>

---

