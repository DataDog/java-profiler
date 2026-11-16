---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 15:45:16 EST

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
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 10 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (4 unique values: 56-75 cores)</summary>

```
1794861603 75
1794861608 75
1794861613 75
1794861618 75
1794861623 75
1794861628 75
1794861633 71
1794861638 71
1794861643 71
1794861648 71
1794861653 73
1794861658 73
1794861663 73
1794861668 73
1794861673 73
1794861678 73
1794861683 56
1794861688 56
1794861693 56
1794861698 56
```
</details>

---

