---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 07:00:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1793098595 30
1793098600 30
1793098605 30
1793098610 30
1793098615 30
1793098620 32
1793098625 32
1793098630 32
1793098635 32
1793098640 32
1793098645 30
1793098650 30
1793098655 30
1793098660 30
1793098665 30
1793098670 30
1793098675 30
1793098680 30
1793098685 30
1793098690 30
```
</details>

---

