---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-11 10:07:43 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 13 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (4 unique values: 84-91 cores)</summary>

```
1773237568 91
1773237573 91
1773237578 91
1773237583 91
1773237588 91
1773237593 91
1773237598 91
1773237603 91
1773237608 90
1773237613 90
1773237618 90
1773237623 90
1773237628 90
1773237633 90
1773237638 90
1773237643 86
1773237648 86
1773237653 86
1773237658 86
1773237663 86
```
</details>

---

