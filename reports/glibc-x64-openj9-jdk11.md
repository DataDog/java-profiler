---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 10:28:12 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1794842599 72
1794842604 72
1794842609 74
1794842614 74
1794842619 74
1794842624 74
1794842630 74
1794842635 74
1794842640 74
1794842645 74
1794842650 74
1794842655 74
1794842660 74
1794842665 74
1794842670 74
1794842675 74
1794842680 74
1794842685 74
1794842690 74
1794842695 74
```
</details>

---

