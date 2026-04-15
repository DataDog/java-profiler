---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-15 14:28:18 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 75-83 cores)</summary>

```
1776277465 75
1776277470 75
1776277475 75
1776277480 75
1776277485 75
1776277490 75
1776277495 79
1776277500 79
1776277505 79
1776277510 79
1776277515 79
1776277520 79
1776277525 79
1776277530 79
1776277535 79
1776277540 79
1776277545 79
1776277550 77
1776277555 77
1776277560 77
```
</details>

---

