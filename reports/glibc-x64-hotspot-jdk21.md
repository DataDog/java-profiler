---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:16:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 76-84 cores)</summary>

```
1794582674 76
1794582679 76
1794582684 76
1794582689 76
1794582694 78
1794582699 78
1794582704 78
1794582709 78
1794582714 78
1794582719 78
1794582724 84
1794582729 84
1794582734 82
1794582739 82
1794582744 82
1794582749 82
1794582754 82
1794582759 82
1794582764 82
1794582769 82
```
</details>

---

