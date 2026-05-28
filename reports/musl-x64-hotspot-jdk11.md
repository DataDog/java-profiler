---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-28 11:27:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 886 |
| Sample Rate | 14.77/sec |
| Health Score | 923% |
| Threads | 10 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (7 unique values: 75-88 cores)</summary>

```
1779981607 75
1779981612 75
1779981617 75
1779981622 81
1779981627 81
1779981632 83
1779981637 83
1779981642 83
1779981647 83
1779981652 83
1779981657 87
1779981662 87
1779981667 88
1779981672 88
1779981677 84
1779981682 84
1779981687 84
1779981692 84
1779981697 84
1779981702 79
```
</details>

---

