---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 14:30:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 9 |
| Allocations | 140 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (4 unique values: 28-38 cores)</summary>

```
1794943505 29
1794943510 29
1794943515 29
1794943520 29
1794943525 29
1794943530 29
1794943535 29
1794943540 29
1794943545 29
1794943550 29
1794943555 29
1794943560 29
1794943565 29
1794943570 29
1794943575 29
1794943580 29
1794943585 38
1794943590 38
1794943595 38
1794943600 33
```
</details>

---

