---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-06 15:13:43 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (6 unique values: 64-87 cores)</summary>

```
1793995719 87
1793995724 87
1793995729 87
1793995734 87
1793995739 85
1793995744 85
1793995749 85
1793995754 85
1793995759 65
1793995764 65
1793995769 67
1793995774 67
1793995779 67
1793995784 72
1793995789 72
1793995794 72
1793995799 72
1793995804 72
1793995809 72
1793995814 72
```
</details>

---

