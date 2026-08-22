---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-22 08:14:28 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 10 |
| Allocations | 420 |

<details>
<summary>CPU Timeline (2 unique values: 62-66 cores)</summary>

```
1787400588 62
1787400593 62
1787400598 62
1787400603 62
1787400608 62
1787400613 62
1787400618 62
1787400623 62
1787400628 62
1787400633 62
1787400638 62
1787400643 66
1787400648 66
1787400653 66
1787400658 66
1787400663 66
1787400668 66
1787400673 66
1787400678 66
1787400683 66
```
</details>

---

