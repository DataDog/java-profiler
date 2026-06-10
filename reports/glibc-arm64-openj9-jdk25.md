---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-06-10 05:13:37 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 297 |
| Sample Rate | 4.95/sec |
| Health Score | 309% |
| Threads | 14 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1781082574 52
1781082579 52
1781082584 52
1781082589 52
1781082594 52
1781082600 52
1781082605 52
1781082610 52
1781082615 52
1781082620 52
1781082625 52
1781082630 64
1781082635 64
1781082640 64
1781082645 64
1781082650 64
1781082655 64
1781082660 64
1781082665 64
1781082670 64
```
</details>

---

