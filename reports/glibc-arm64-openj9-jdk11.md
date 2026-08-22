---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-22 08:14:27 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 317 |
| Sample Rate | 5.28/sec |
| Health Score | 330% |
| Threads | 8 |
| Allocations | 189 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 279 |
| Sample Rate | 4.65/sec |
| Health Score | 291% |
| Threads | 10 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787400645 48
1787400650 48
1787400655 48
1787400660 48
1787400665 48
1787400670 48
1787400675 48
1787400680 48
1787400685 48
1787400690 48
1787400695 48
1787400700 48
1787400705 48
1787400710 48
1787400715 48
1787400720 48
1787400725 48
1787400730 43
1787400735 43
1787400740 43
```
</details>

---

