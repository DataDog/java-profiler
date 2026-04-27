---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-27 05:15:07 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (6 unique values: 70-79 cores)</summary>

```
1777281040 71
1777281045 70
1777281050 70
1777281055 75
1777281060 75
1777281065 75
1777281070 75
1777281075 75
1777281080 70
1777281085 70
1777281090 70
1777281095 70
1777281100 75
1777281105 75
1777281110 75
1777281115 75
1777281120 73
1777281125 73
1777281130 73
1777281135 77
```
</details>

---

