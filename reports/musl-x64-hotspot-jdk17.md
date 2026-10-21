---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 16:37:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (5 unique values: 73-89 cores)</summary>

```
1792614690 87
1792614695 87
1792614700 89
1792614705 89
1792614710 89
1792614715 89
1792614720 89
1792614725 89
1792614730 89
1792614735 73
1792614740 73
1792614745 73
1792614750 73
1792614755 73
1792614760 73
1792614765 73
1792614770 73
1792614775 78
1792614780 78
1792614785 78
```
</details>

---

