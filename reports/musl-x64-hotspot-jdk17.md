---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-07 10:01:25 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 28-61 cores)</summary>

```
1794063404 61
1794063409 61
1794063414 61
1794063419 61
1794063424 61
1794063429 61
1794063434 61
1794063439 61
1794063444 61
1794063449 61
1794063454 61
1794063459 61
1794063464 61
1794063469 61
1794063474 28
1794063479 28
1794063484 28
1794063489 28
1794063494 28
1794063499 28
```
</details>

---

