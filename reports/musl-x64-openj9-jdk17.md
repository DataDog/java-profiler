---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-27 09:40:19 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 73-81 cores)</summary>

```
1787837734 81
1787837739 81
1787837744 81
1787837749 81
1787837754 81
1787837759 81
1787837764 81
1787837769 81
1787837774 81
1787837779 81
1787837784 81
1787837789 81
1787837794 73
1787837799 73
1787837804 73
1787837809 73
1787837814 73
1787837819 73
1787837824 73
1787837829 73
```
</details>

---

