---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 12:39:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 74-79 cores)</summary>

```
1778171729 79
1778171734 79
1778171739 74
1778171744 74
1778171749 74
1778171754 74
1778171759 74
1778171764 74
1778171769 74
1778171774 79
1778171779 79
1778171784 79
1778171789 79
1778171794 79
1778171799 79
1778171804 77
1778171809 77
1778171814 77
1778171819 79
1778171824 79
```
</details>

---

