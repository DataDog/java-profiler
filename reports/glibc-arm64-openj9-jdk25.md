---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 16:39:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794346425 48
1794346430 48
1794346435 48
1794346440 48
1794346445 48
1794346450 48
1794346455 48
1794346460 48
1794346465 48
1794346470 48
1794346475 48
1794346480 48
1794346485 48
1794346490 48
1794346495 48
1794346500 48
1794346505 48
1794346510 43
1794346515 43
1794346520 43
```
</details>

---

