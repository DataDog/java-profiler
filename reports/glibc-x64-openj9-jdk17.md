---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 08:26:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (5 unique values: 73-85 cores)</summary>

```
1794489689 79
1794489694 79
1794489699 79
1794489704 79
1794489709 79
1794489714 79
1794489719 79
1794489724 81
1794489729 81
1794489734 81
1794489739 81
1794489744 81
1794489749 83
1794489754 83
1794489759 83
1794489764 83
1794489770 85
1794489775 85
1794489780 73
1794489785 73
```
</details>

---

