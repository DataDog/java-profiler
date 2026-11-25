---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 05:36:49 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 13 |
| Allocations | 99 |

<details>
<summary>CPU Timeline (3 unique values: 27-48 cores)</summary>

```
1795602675 32
1795602680 32
1795602685 32
1795602690 32
1795602695 32
1795602700 32
1795602705 32
1795602710 32
1795602715 32
1795602720 32
1795602725 32
1795602730 32
1795602735 32
1795602740 32
1795602745 32
1795602750 48
1795602755 48
1795602760 32
1795602765 32
1795602770 32
```
</details>

---

