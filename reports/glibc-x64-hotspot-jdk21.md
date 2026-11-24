---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:14:32 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 12.73/sec |
| Health Score | 796% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 50-55 cores)</summary>

```
1795529378 53
1795529383 53
1795529388 53
1795529393 53
1795529398 53
1795529403 53
1795529408 53
1795529414 53
1795529419 53
1795529424 53
1795529429 53
1795529434 53
1795529439 55
1795529444 55
1795529449 55
1795529454 50
1795529459 50
1795529464 50
1795529469 50
1795529474 50
```
</details>

---

