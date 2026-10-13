---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-13 01:03:51 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 27-31 cores)</summary>

```
1791867583 29
1791867588 29
1791867593 29
1791867598 29
1791867603 29
1791867608 29
1791867613 29
1791867618 29
1791867623 29
1791867628 29
1791867633 29
1791867638 29
1791867643 29
1791867648 31
1791867653 31
1791867658 31
1791867663 31
1791867668 29
1791867673 29
1791867678 29
```
</details>

---

