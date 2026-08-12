---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 04:18:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1786522506 61
1786522511 61
1786522516 61
1786522521 61
1786522526 61
1786522532 61
1786522537 61
1786522542 61
1786522547 61
1786522552 61
1786522557 61
1786522562 59
1786522567 59
1786522572 59
1786522577 59
1786522582 61
1786522587 61
1786522592 61
1786522597 61
1786522602 61
```
</details>

---

