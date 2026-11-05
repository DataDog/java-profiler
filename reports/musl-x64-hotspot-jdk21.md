---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-05 07:42:26 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 780 |
| Sample Rate | 13.00/sec |
| Health Score | 812% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (6 unique values: 62-92 cores)</summary>

```
1793882333 74
1793882338 74
1793882343 74
1793882348 74
1793882353 74
1793882358 74
1793882363 74
1793882368 64
1793882373 64
1793882378 64
1793882383 62
1793882388 62
1793882393 82
1793882398 82
1793882403 82
1793882408 82
1793882413 87
1793882418 87
1793882423 87
1793882428 92
```
</details>

---

