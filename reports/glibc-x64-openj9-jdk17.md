---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 06:03:38 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 39-52 cores)</summary>

```
1794567555 50
1794567560 50
1794567565 48
1794567570 48
1794567575 48
1794567580 48
1794567585 48
1794567590 48
1794567595 48
1794567600 48
1794567605 48
1794567610 48
1794567615 50
1794567620 50
1794567625 50
1794567630 50
1794567635 50
1794567640 50
1794567645 52
1794567650 52
```
</details>

---

