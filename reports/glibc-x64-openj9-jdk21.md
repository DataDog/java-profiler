---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 18:02:46 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (4 unique values: 46-82 cores)</summary>

```
1794783568 46
1794783573 46
1794783578 46
1794783583 46
1794783588 46
1794783593 46
1794783598 46
1794783603 46
1794783608 46
1794783613 46
1794783618 71
1794783623 71
1794783628 71
1794783633 71
1794783638 71
1794783643 71
1794783648 71
1794783653 63
1794783658 63
1794783663 82
```
</details>

---

