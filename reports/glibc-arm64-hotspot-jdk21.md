---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 20:01:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1793145521 14
1793145526 14
1793145531 14
1793145536 14
1793145541 14
1793145546 14
1793145551 14
1793145556 14
1793145561 14
1793145566 14
1793145571 34
1793145576 34
1793145581 34
1793145586 34
1793145591 34
1793145596 34
1793145601 34
1793145606 34
1793145611 34
1793145616 34
```
</details>

---

