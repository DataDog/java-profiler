---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 07:45:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 12 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (5 unique values: 60-69 cores)</summary>

```
1794573578 64
1794573583 64
1794573588 64
1794573593 64
1794573598 64
1794573603 64
1794573608 60
1794573613 60
1794573618 60
1794573623 60
1794573628 60
1794573633 62
1794573638 62
1794573643 62
1794573648 62
1794573653 62
1794573658 62
1794573663 62
1794573668 62
1794573673 62
```
</details>

---

