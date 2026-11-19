---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 09:29:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 10 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (4 unique values: 31-42 cores)</summary>

```
1795098382 35
1795098387 35
1795098392 35
1795098397 35
1795098402 35
1795098407 35
1795098412 35
1795098417 35
1795098422 35
1795098427 35
1795098432 35
1795098437 33
1795098442 33
1795098447 33
1795098452 33
1795098457 33
1795098462 33
1795098467 33
1795098472 33
1795098477 33
```
</details>

---

