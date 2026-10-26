---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-26 11:06:15 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1793026772 30
1793026777 30
1793026782 30
1793026787 30
1793026792 30
1793026797 30
1793026802 30
1793026807 30
1793026812 30
1793026817 30
1793026822 30
1793026827 30
1793026832 30
1793026837 32
1793026842 32
1793026847 29
1793026852 29
1793026857 29
1793026862 29
1793026867 29
```
</details>

---

