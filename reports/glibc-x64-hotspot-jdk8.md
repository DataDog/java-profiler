---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-16 11:32:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 78-86 cores)</summary>

```
1794846382 83
1794846387 83
1794846392 83
1794846397 83
1794846402 83
1794846407 83
1794846412 83
1794846417 83
1794846422 81
1794846427 81
1794846432 81
1794846437 81
1794846442 84
1794846447 84
1794846452 84
1794846457 84
1794846462 84
1794846467 84
1794846472 84
1794846477 86
```
</details>

---

