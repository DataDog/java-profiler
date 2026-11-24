---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:14:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 80-85 cores)</summary>

```
1795529311 85
1795529316 85
1795529321 85
1795529326 85
1795529331 85
1795529336 82
1795529341 82
1795529346 82
1795529351 82
1795529356 82
1795529361 82
1795529366 82
1795529371 82
1795529376 82
1795529381 80
1795529386 80
1795529391 80
1795529396 80
1795529401 80
1795529406 80
```
</details>

---

