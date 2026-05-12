---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-12 06:42:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 828 |
| Sample Rate | 13.80/sec |
| Health Score | 862% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (5 unique values: 51-65 cores)</summary>

```
1778582320 56
1778582325 56
1778582330 56
1778582335 56
1778582340 65
1778582345 65
1778582350 65
1778582355 51
1778582360 51
1778582365 53
1778582370 53
1778582375 53
1778582380 53
1778582385 56
1778582390 56
1778582395 56
1778582400 56
1778582405 56
1778582410 56
1778582415 56
```
</details>

---

