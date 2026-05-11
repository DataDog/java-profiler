---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-11 11:23:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 954 |
| Sample Rate | 15.90/sec |
| Health Score | 994% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (6 unique values: 72-84 cores)</summary>

```
1778512719 84
1778512724 84
1778512729 84
1778512734 74
1778512739 74
1778512744 74
1778512749 74
1778512754 74
1778512759 72
1778512764 72
1778512769 72
1778512774 72
1778512779 72
1778512784 74
1778512789 74
1778512794 74
1778512799 73
1778512804 73
1778512809 73
1778512814 73
```
</details>

---

