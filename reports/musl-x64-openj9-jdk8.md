---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-22 08:14:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1787400583 81
1787400588 81
1787400593 81
1787400598 81
1787400603 81
1787400608 81
1787400613 81
1787400618 79
1787400623 79
1787400628 79
1787400633 79
1787400638 79
1787400643 79
1787400648 79
1787400653 79
1787400658 79
1787400663 79
1787400668 79
1787400673 81
1787400678 81
```
</details>

---

