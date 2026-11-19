---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 11:31:11 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 9 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 46-50 cores)</summary>

```
1795105603 46
1795105608 46
1795105613 46
1795105618 46
1795105623 48
1795105628 48
1795105633 48
1795105638 50
1795105643 50
1795105648 50
1795105653 50
1795105658 50
1795105663 50
1795105668 50
1795105673 50
1795105678 50
1795105683 50
1795105688 50
1795105693 50
1795105698 50
```
</details>

---

