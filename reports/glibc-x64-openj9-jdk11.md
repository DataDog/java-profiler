---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 13:06:30 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 817 |
| Sample Rate | 13.62/sec |
| Health Score | 851% |
| Threads | 9 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (3 unique values: 75-87 cores)</summary>

```
1795197728 87
1795197733 87
1795197738 87
1795197744 87
1795197749 87
1795197754 87
1795197759 87
1795197764 87
1795197769 78
1795197774 78
1795197779 78
1795197784 78
1795197789 78
1795197794 78
1795197799 78
1795197804 78
1795197809 78
1795197814 78
1795197819 78
1795197824 78
```
</details>

---

