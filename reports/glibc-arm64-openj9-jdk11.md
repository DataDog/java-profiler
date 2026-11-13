---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 09:21:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (4 unique values: 35-44 cores)</summary>

```
1794579391 42
1794579396 44
1794579401 44
1794579406 44
1794579411 44
1794579416 44
1794579421 44
1794579426 44
1794579431 44
1794579436 44
1794579441 44
1794579446 44
1794579451 44
1794579456 44
1794579461 44
1794579466 36
1794579471 36
1794579476 36
1794579481 36
1794579486 36
```
</details>

---

