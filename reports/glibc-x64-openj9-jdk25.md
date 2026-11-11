---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 16:24:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (5 unique values: 68-88 cores)</summary>

```
1794431677 70
1794431682 68
1794431687 68
1794431692 86
1794431697 86
1794431702 86
1794431707 86
1794431712 86
1794431717 86
1794431722 86
1794431727 88
1794431732 88
1794431737 88
1794431742 88
1794431747 88
1794431752 88
1794431757 88
1794431762 88
1794431767 88
1794431772 88
```
</details>

---

