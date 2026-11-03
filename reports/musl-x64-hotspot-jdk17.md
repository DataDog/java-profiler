---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 11:22:17 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 54-56 cores)</summary>

```
1793722578 56
1793722583 56
1793722588 56
1793722593 56
1793722598 56
1793722603 56
1793722608 56
1793722613 56
1793722618 56
1793722623 56
1793722628 56
1793722633 56
1793722638 56
1793722643 56
1793722648 54
1793722653 54
1793722658 54
1793722663 54
1793722668 54
1793722673 54
```
</details>

---

