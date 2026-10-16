---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-16 06:16:39 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (4 unique values: 79-86 cores)</summary>

```
1792145531 84
1792145536 84
1792145541 84
1792145546 84
1792145551 84
1792145556 84
1792145561 84
1792145566 84
1792145571 84
1792145576 84
1792145581 86
1792145586 86
1792145591 86
1792145596 81
1792145601 81
1792145606 81
1792145611 81
1792145616 81
1792145621 81
1792145626 79
```
</details>

---

