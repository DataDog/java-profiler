---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-05-06 14:42:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 47-52 cores)</summary>

```
1778092675 52
1778092680 52
1778092685 47
1778092690 47
1778092695 47
1778092700 47
1778092705 47
1778092710 47
1778092715 47
1778092720 47
1778092725 47
1778092730 47
1778092735 47
1778092740 47
1778092745 47
1778092750 47
1778092755 47
1778092760 51
1778092765 51
1778092770 51
```
</details>

---

