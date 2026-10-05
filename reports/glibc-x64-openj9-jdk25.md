---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-05 05:52:34 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 42-62 cores)</summary>

```
1791193615 42
1791193620 42
1791193625 42
1791193630 42
1791193635 42
1791193640 42
1791193645 42
1791193650 42
1791193655 42
1791193660 42
1791193665 42
1791193670 42
1791193675 42
1791193680 42
1791193685 42
1791193690 62
1791193695 62
1791193700 62
1791193705 62
1791193710 62
```
</details>

---

