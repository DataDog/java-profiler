---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 09:29:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 12 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 65-67 cores)</summary>

```
1795098346 65
1795098351 65
1795098356 65
1795098361 65
1795098366 65
1795098371 67
1795098376 67
1795098381 67
1795098386 65
1795098391 65
1795098396 65
1795098401 65
1795098406 65
1795098411 65
1795098416 65
1795098421 65
1795098426 65
1795098431 65
1795098436 65
1795098441 65
```
</details>

---

