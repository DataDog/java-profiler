---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-12 06:45:06 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 833 |
| Sample Rate | 13.88/sec |
| Health Score | 868% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 56-59 cores)</summary>

```
1778582532 56
1778582537 56
1778582542 56
1778582547 56
1778582552 56
1778582557 56
1778582562 56
1778582567 56
1778582572 56
1778582577 56
1778582582 59
1778582587 59
1778582592 59
1778582597 59
1778582602 59
1778582607 59
1778582612 59
1778582617 59
1778582622 59
1778582627 59
```
</details>

---

