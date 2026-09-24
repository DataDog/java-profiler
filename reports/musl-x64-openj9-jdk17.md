---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 00:59:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 46-50 cores)</summary>

```
1790225603 46
1790225608 46
1790225613 46
1790225618 46
1790225623 46
1790225628 48
1790225633 48
1790225638 48
1790225643 48
1790225648 48
1790225653 48
1790225658 50
1790225663 50
1790225668 50
1790225673 50
1790225678 50
1790225683 50
1790225688 48
1790225693 48
1790225698 48
```
</details>

---

