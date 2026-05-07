---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 12:39:49 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 73-83 cores)</summary>

```
1778171725 73
1778171730 73
1778171735 73
1778171740 73
1778171745 73
1778171750 73
1778171755 73
1778171760 73
1778171765 83
1778171770 83
1778171775 83
1778171780 83
1778171785 83
1778171790 83
1778171795 83
1778171800 83
1778171805 83
1778171810 83
1778171815 83
1778171820 83
```
</details>

---

