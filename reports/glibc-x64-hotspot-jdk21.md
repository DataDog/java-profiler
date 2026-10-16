---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-16 06:16:39 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1792145521 30
1792145526 32
1792145531 32
1792145536 32
1792145541 32
1792145546 32
1792145551 32
1792145556 32
1792145561 32
1792145566 32
1792145571 32
1792145576 32
1792145581 32
1792145586 32
1792145591 32
1792145596 32
1792145601 27
1792145606 27
1792145611 27
1792145616 27
```
</details>

---

