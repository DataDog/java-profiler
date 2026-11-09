---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 15:05:39 EST

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (2 unique values: 19-21 cores)</summary>

```
1794254430 21
1794254435 21
1794254440 19
1794254445 19
1794254450 19
1794254455 19
1794254460 19
1794254465 19
1794254470 19
1794254475 19
1794254480 19
1794254485 19
1794254490 19
1794254495 19
1794254500 19
1794254505 19
1794254510 19
1794254515 19
1794254520 19
1794254525 19
```
</details>

---

