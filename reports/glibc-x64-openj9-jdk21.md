---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 10:58:03 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 58-60 cores)</summary>

```
1794930697 58
1794930702 60
1794930708 60
1794930713 60
1794930718 60
1794930723 60
1794930728 60
1794930733 60
1794930738 60
1794930743 60
1794930748 60
1794930753 60
1794930758 60
1794930763 60
1794930768 60
1794930773 60
1794930778 60
1794930783 60
1794930788 60
1794930793 60
```
</details>

---

