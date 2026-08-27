---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-27 09:40:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 68-96 cores)</summary>

```
1787837734 96
1787837739 96
1787837744 68
1787837749 68
1787837754 68
1787837759 68
1787837764 68
1787837769 68
1787837774 68
1787837779 68
1787837784 68
1787837789 68
1787837794 68
1787837799 68
1787837804 68
1787837809 68
1787837814 68
1787837819 68
1787837824 68
1787837829 68
```
</details>

---

