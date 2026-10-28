---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 12:39:36 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 90-92 cores)</summary>

```
1793205304 90
1793205309 90
1793205314 90
1793205319 90
1793205324 90
1793205329 90
1793205334 90
1793205339 90
1793205344 90
1793205349 90
1793205354 90
1793205359 90
1793205364 90
1793205369 90
1793205374 90
1793205379 90
1793205384 90
1793205389 92
1793205394 92
1793205399 92
```
</details>

---

