---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-17 11:08:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 313 |
| Sample Rate | 5.22/sec |
| Health Score | 326% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 69-75 cores)</summary>

```
1794931388 72
1794931393 72
1794931398 70
1794931403 70
1794931408 70
1794931413 72
1794931418 72
1794931423 72
1794931428 72
1794931433 72
1794931438 72
1794931443 72
1794931448 74
1794931453 74
1794931458 74
1794931463 74
1794931468 75
1794931473 75
1794931478 75
1794931483 73
```
</details>

---

