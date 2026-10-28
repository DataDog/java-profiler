---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 12:39:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 71-79 cores)</summary>

```
1793205299 79
1793205304 79
1793205309 79
1793205314 79
1793205319 79
1793205324 79
1793205329 71
1793205334 71
1793205339 71
1793205344 71
1793205349 71
1793205354 71
1793205359 71
1793205364 71
1793205369 71
1793205374 71
1793205379 71
1793205384 71
1793205389 71
1793205394 71
```
</details>

---

