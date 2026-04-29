---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-29 07:38:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 789 |
| Sample Rate | 13.15/sec |
| Health Score | 822% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 73-80 cores)</summary>

```
1777462480 73
1777462485 73
1777462490 73
1777462495 73
1777462500 73
1777462505 73
1777462510 73
1777462515 80
1777462520 80
1777462525 80
1777462530 80
1777462535 80
1777462540 80
1777462545 80
1777462550 80
1777462555 80
1777462560 80
1777462565 80
1777462570 80
1777462575 80
```
</details>

---

