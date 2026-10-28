---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:43:20 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 14 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1793187415 47
1793187420 47
1793187425 47
1793187430 47
1793187435 47
1793187440 47
1793187445 48
1793187450 48
1793187455 48
1793187460 48
1793187465 48
1793187470 48
1793187475 48
1793187480 48
1793187485 48
1793187490 48
1793187495 48
1793187500 48
1793187505 48
1793187510 48
```
</details>

---

