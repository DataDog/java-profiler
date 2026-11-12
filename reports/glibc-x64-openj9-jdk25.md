---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 13:21:25 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 10 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (4 unique values: 84-90 cores)</summary>

```
1794507351 90
1794507356 90
1794507361 90
1794507366 90
1794507371 90
1794507376 90
1794507381 90
1794507386 90
1794507391 88
1794507396 88
1794507401 88
1794507407 88
1794507412 88
1794507417 88
1794507422 88
1794507427 88
1794507432 86
1794507437 86
1794507442 86
1794507447 84
```
</details>

---

