---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-20 13:25:46 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 61-83 cores)</summary>

```
1787246456 61
1787246461 61
1787246466 83
1787246471 83
1787246476 83
1787246481 83
1787246486 83
1787246491 83
1787246496 83
1787246501 83
1787246506 83
1787246511 83
1787246516 83
1787246521 83
1787246526 83
1787246531 83
1787246536 83
1787246541 83
1787246546 83
1787246551 83
```
</details>

---

