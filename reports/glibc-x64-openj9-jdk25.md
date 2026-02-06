---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-06 09:39:28 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 10 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 974 |
| Sample Rate | 16.23/sec |
| Health Score | 1014% |
| Threads | 12 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 53-57 cores)</summary>

```
1770388386 53
1770388391 57
1770388396 57
1770388401 53
1770388406 53
1770388411 57
1770388416 57
1770388421 57
1770388426 57
1770388431 57
1770388436 57
1770388441 57
1770388446 57
1770388451 57
1770388456 57
1770388461 57
1770388466 57
1770388471 57
1770388476 57
1770388481 57
```
</details>

---

