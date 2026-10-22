---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 13:10:14 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 831 |
| Sample Rate | 13.85/sec |
| Health Score | 866% |
| Threads | 11 |
| Allocations | 552 |

<details>
<summary>CPU Timeline (3 unique values: 91-94 cores)</summary>

```
1792688670 94
1792688675 94
1792688680 94
1792688685 94
1792688690 94
1792688695 94
1792688700 93
1792688705 93
1792688710 93
1792688715 93
1792688720 93
1792688725 93
1792688730 93
1792688735 93
1792688740 93
1792688745 93
1792688750 91
1792688755 91
1792688760 91
1792688765 91
```
</details>

---

