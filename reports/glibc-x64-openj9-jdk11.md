---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:15:29 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1794582659 29
1794582664 29
1794582669 29
1794582674 29
1794582679 29
1794582684 29
1794582689 29
1794582694 29
1794582699 29
1794582704 27
1794582709 27
1794582714 27
1794582719 27
1794582724 27
1794582729 27
1794582734 27
1794582739 27
1794582744 27
1794582749 27
1794582754 27
```
</details>

---

