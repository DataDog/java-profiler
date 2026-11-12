---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:57:34 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (4 unique values: 82-88 cores)</summary>

```
1794498749 82
1794498754 82
1794498759 82
1794498764 82
1794498769 82
1794498774 82
1794498779 82
1794498784 82
1794498789 84
1794498794 84
1794498799 84
1794498804 84
1794498809 84
1794498814 86
1794498819 86
1794498824 88
1794498829 88
1794498834 86
1794498839 86
1794498844 86
```
</details>

---

