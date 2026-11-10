---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 10:31:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 12 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (5 unique values: 56-74 cores)</summary>

```
1794324437 72
1794324442 56
1794324447 56
1794324452 56
1794324457 56
1794324462 65
1794324467 65
1794324472 65
1794324477 65
1794324482 65
1794324487 65
1794324493 74
1794324498 74
1794324503 74
1794324508 57
1794324513 57
1794324518 57
1794324523 57
1794324528 57
1794324533 57
```
</details>

---

