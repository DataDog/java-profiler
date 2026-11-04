---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 17:22:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 878 |
| Sample Rate | 14.63/sec |
| Health Score | 914% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1793830741 48
1793830746 48
1793830751 48
1793830756 48
1793830761 48
1793830766 48
1793830771 48
1793830776 53
1793830781 53
1793830786 53
1793830791 53
1793830796 53
1793830801 53
1793830806 53
1793830811 53
1793830816 53
1793830821 53
1793830826 53
1793830831 53
1793830836 48
```
</details>

---

