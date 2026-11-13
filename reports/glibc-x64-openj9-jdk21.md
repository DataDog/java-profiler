---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:15:29 EST

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
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 58-84 cores)</summary>

```
1794582709 58
1794582714 58
1794582719 58
1794582724 58
1794582729 58
1794582734 58
1794582739 58
1794582744 58
1794582749 58
1794582754 58
1794582759 58
1794582764 58
1794582769 58
1794582774 58
1794582779 76
1794582784 76
1794582789 82
1794582794 82
1794582799 84
1794582804 84
```
</details>

---

