---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 11:01:30 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 20-32 cores)</summary>

```
1794585443 29
1794585448 29
1794585453 29
1794585458 29
1794585463 29
1794585468 29
1794585473 29
1794585478 29
1794585483 29
1794585488 32
1794585493 32
1794585498 20
1794585503 20
1794585508 20
1794585513 20
1794585518 20
1794585523 20
1794585528 20
1794585533 20
1794585538 20
```
</details>

---

