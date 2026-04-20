---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-20 10:20:32 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 10 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (5 unique values: 51-91 cores)</summary>

```
1776694476 51
1776694481 51
1776694486 51
1776694491 51
1776694496 51
1776694501 51
1776694506 51
1776694511 51
1776694516 51
1776694521 51
1776694526 51
1776694531 51
1776694536 69
1776694541 69
1776694546 87
1776694551 87
1776694556 87
1776694561 87
1776694566 91
1776694571 91
```
</details>

---

