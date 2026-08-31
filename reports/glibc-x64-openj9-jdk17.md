---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-31 00:49:31 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 299 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (5 unique values: 50-63 cores)</summary>

```
1788151545 58
1788151550 58
1788151555 58
1788151560 63
1788151565 63
1788151570 63
1788151575 63
1788151580 61
1788151585 61
1788151590 61
1788151595 61
1788151600 61
1788151605 61
1788151610 61
1788151615 61
1788151620 61
1788151625 61
1788151630 50
1788151635 50
1788151640 52
```
</details>

---

