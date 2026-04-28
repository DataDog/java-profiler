---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-28 11:22:31 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 10 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (5 unique values: 80-89 cores)</summary>

```
1777389439 89
1777389444 89
1777389449 89
1777389454 89
1777389459 89
1777389464 89
1777389469 87
1777389474 87
1777389479 83
1777389484 83
1777389489 83
1777389494 84
1777389499 84
1777389504 84
1777389509 84
1777389514 84
1777389519 80
1777389524 80
1777389529 80
1777389534 80
```
</details>

---

