---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 10:16:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 78 |
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
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (4 unique values: 68-87 cores)</summary>

```
1794582699 68
1794582704 68
1794582709 68
1794582714 68
1794582719 68
1794582724 70
1794582729 70
1794582734 70
1794582739 70
1794582744 70
1794582749 70
1794582754 70
1794582759 70
1794582764 70
1794582769 70
1794582774 70
1794582779 70
1794582784 70
1794582789 87
1794582794 87
```
</details>

---

