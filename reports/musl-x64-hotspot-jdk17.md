---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 05:30:27 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (4 unique values: 41-62 cores)</summary>

```
1794997464 62
1794997469 41
1794997474 41
1794997479 41
1794997484 41
1794997489 41
1794997494 41
1794997499 41
1794997505 41
1794997510 41
1794997515 41
1794997520 43
1794997525 43
1794997530 45
1794997535 45
1794997540 45
1794997545 45
1794997550 45
1794997555 45
1794997560 45
```
</details>

---

