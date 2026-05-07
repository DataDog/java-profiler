---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-07 17:34:38 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 10 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (3 unique values: 49-53 cores)</summary>

```
1778189420 53
1778189425 53
1778189430 53
1778189435 53
1778189440 53
1778189445 53
1778189450 53
1778189455 53
1778189460 49
1778189465 49
1778189470 51
1778189475 51
1778189480 51
1778189485 51
1778189490 51
1778189495 51
1778189500 51
1778189505 51
1778189510 51
1778189515 51
```
</details>

---

