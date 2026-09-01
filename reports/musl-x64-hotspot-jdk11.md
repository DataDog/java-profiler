---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-01 12:28:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 810 |
| Sample Rate | 13.50/sec |
| Health Score | 844% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 64-84 cores)</summary>

```
1788279625 64
1788279630 64
1788279635 64
1788279640 64
1788279645 64
1788279650 64
1788279655 64
1788279660 64
1788279665 64
1788279670 64
1788279675 64
1788279680 64
1788279685 64
1788279690 64
1788279695 64
1788279700 64
1788279705 84
1788279710 84
1788279715 84
1788279720 84
```
</details>

---

