---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 09:29:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 10 |
| Allocations | 309 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 72-77 cores)</summary>

```
1795098346 77
1795098351 77
1795098356 77
1795098361 77
1795098366 77
1795098371 77
1795098376 74
1795098381 74
1795098386 74
1795098391 74
1795098396 74
1795098401 74
1795098406 74
1795098411 74
1795098416 74
1795098421 74
1795098426 74
1795098431 74
1795098436 74
1795098441 74
```
</details>

---

