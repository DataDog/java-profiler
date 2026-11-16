---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 11:32:06 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (4 unique values: 75-86 cores)</summary>

```
1794846387 77
1794846392 75
1794846397 75
1794846402 77
1794846407 77
1794846412 77
1794846417 77
1794846422 77
1794846427 77
1794846432 77
1794846437 77
1794846442 77
1794846447 75
1794846452 75
1794846457 75
1794846462 75
1794846467 84
1794846472 84
1794846477 84
1794846482 84
```
</details>

---

