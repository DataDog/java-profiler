---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 10:28:13 EST

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
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (4 unique values: 68-76 cores)</summary>

```
1794842597 70
1794842602 70
1794842607 74
1794842612 74
1794842617 74
1794842622 74
1794842627 74
1794842632 74
1794842637 74
1794842642 74
1794842647 76
1794842652 76
1794842657 76
1794842662 76
1794842667 76
1794842672 76
1794842677 76
1794842682 76
1794842687 76
1794842692 76
```
</details>

---

