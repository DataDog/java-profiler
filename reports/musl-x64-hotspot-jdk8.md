---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-02 21:59:32 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 309 |
| Sample Rate | 5.15/sec |
| Health Score | 322% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 32-39 cores)</summary>

```
1793674428 34
1793674433 34
1793674438 34
1793674443 34
1793674448 34
1793674453 34
1793674458 34
1793674463 34
1793674468 34
1793674473 34
1793674478 36
1793674483 36
1793674488 32
1793674493 32
1793674498 32
1793674503 32
1793674508 32
1793674513 32
1793674518 37
1793674523 37
```
</details>

---

