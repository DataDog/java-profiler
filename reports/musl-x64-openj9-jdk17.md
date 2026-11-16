---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-11-16 07:25:16 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 73-77 cores)</summary>

```
1794831558 75
1794831563 75
1794831568 77
1794831573 77
1794831578 77
1794831583 75
1794831588 75
1794831593 75
1794831598 75
1794831603 75
1794831608 75
1794831613 75
1794831618 75
1794831623 75
1794831628 75
1794831633 75
1794831638 75
1794831643 75
1794831648 75
1794831653 73
```
</details>

---

