---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-14 04:32:40 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 10 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (4 unique values: 63-92 cores)</summary>

```
1791966544 92
1791966549 92
1791966554 92
1791966559 66
1791966564 66
1791966569 66
1791966574 66
1791966579 66
1791966584 66
1791966589 66
1791966594 66
1791966599 66
1791966604 66
1791966609 63
1791966614 63
1791966619 63
1791966624 63
1791966629 63
1791966634 63
1791966639 63
```
</details>

---

