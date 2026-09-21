---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 09:02:24 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 62-86 cores)</summary>

```
1789995416 62
1789995421 62
1789995426 62
1789995431 62
1789995436 62
1789995441 62
1789995446 62
1789995451 62
1789995456 62
1789995461 62
1789995466 62
1789995471 62
1789995476 62
1789995482 62
1789995487 62
1789995492 86
1789995497 86
1789995502 86
1789995507 86
1789995512 86
```
</details>

---

