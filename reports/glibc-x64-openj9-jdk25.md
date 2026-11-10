---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 15:03:06 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (5 unique values: 66-81 cores)</summary>

```
1794340558 72
1794340563 72
1794340568 72
1794340573 72
1794340578 72
1794340583 72
1794340588 66
1794340593 66
1794340598 66
1794340603 66
1794340608 66
1794340613 66
1794340618 66
1794340623 71
1794340628 71
1794340633 81
1794340638 81
1794340643 81
1794340648 81
1794340653 81
```
</details>

---

