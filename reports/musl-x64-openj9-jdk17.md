---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 09:21:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 942 |
| Sample Rate | 15.70/sec |
| Health Score | 981% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 84-86 cores)</summary>

```
1794838619 86
1794838624 86
1794838629 86
1794838634 86
1794838639 86
1794838644 86
1794838649 86
1794838654 86
1794838659 86
1794838664 86
1794838669 86
1794838674 86
1794838679 84
1794838684 84
1794838689 84
1794838694 84
1794838699 84
1794838704 84
1794838709 84
1794838714 84
```
</details>

---

