---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:14:40 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 138 |
| Sample Rate | 2.30/sec |
| Health Score | 144% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 9 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1795630275 94
1795630281 94
1795630286 94
1795630291 94
1795630296 94
1795630301 94
1795630306 94
1795630311 94
1795630316 94
1795630321 96
1795630326 96
1795630331 96
1795630336 96
1795630341 96
1795630346 96
1795630351 96
1795630356 96
1795630361 94
1795630366 94
1795630371 94
```
</details>

---

