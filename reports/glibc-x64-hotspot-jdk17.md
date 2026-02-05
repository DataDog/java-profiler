---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-05 15:03:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 90-92 cores)</summary>

```
1770321567 92
1770321572 92
1770321577 92
1770321582 92
1770321587 92
1770321592 92
1770321597 92
1770321602 92
1770321607 92
1770321612 92
1770321617 92
1770321622 92
1770321627 92
1770321632 92
1770321637 90
1770321642 90
1770321647 90
1770321652 90
1770321657 90
1770321662 90
```
</details>

---

