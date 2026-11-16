---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 10:28:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 926 |
| Sample Rate | 15.43/sec |
| Health Score | 964% |
| Threads | 10 |
| Allocations | 550 |

<details>
<summary>CPU Timeline (3 unique values: 46-91 cores)</summary>

```
1794842589 46
1794842594 46
1794842599 46
1794842604 46
1794842609 76
1794842614 76
1794842620 76
1794842625 76
1794842630 76
1794842635 76
1794842640 91
1794842645 91
1794842650 91
1794842655 91
1794842660 91
1794842665 91
1794842670 91
1794842675 91
1794842680 91
1794842685 91
```
</details>

---

