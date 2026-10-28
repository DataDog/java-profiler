---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 12:27:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 53-64 cores)</summary>

```
1793204555 53
1793204560 53
1793204565 53
1793204570 53
1793204575 53
1793204580 53
1793204585 53
1793204590 53
1793204595 53
1793204600 53
1793204605 62
1793204610 62
1793204615 62
1793204620 62
1793204625 62
1793204630 62
1793204635 62
1793204640 62
1793204645 62
1793204650 62
```
</details>

---

