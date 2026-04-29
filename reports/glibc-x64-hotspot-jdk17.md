---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-29 12:24:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (5 unique values: 69-79 cores)</summary>

```
1777479492 73
1777479497 73
1777479502 75
1777479507 75
1777479512 75
1777479517 75
1777479522 75
1777479527 75
1777479532 71
1777479537 71
1777479542 71
1777479547 71
1777479552 71
1777479557 71
1777479562 71
1777479567 71
1777479572 71
1777479577 73
1777479582 73
1777479587 69
```
</details>

---

