---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 10:15:29 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 82-92 cores)</summary>

```
1794582644 82
1794582649 82
1794582654 82
1794582659 82
1794582664 82
1794582669 82
1794582674 82
1794582679 82
1794582684 92
1794582689 92
1794582694 92
1794582699 92
1794582704 92
1794582709 92
1794582714 92
1794582719 92
1794582724 92
1794582729 92
1794582734 92
1794582739 92
```
</details>

---

