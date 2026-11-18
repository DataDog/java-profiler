---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 05:30:28 EST

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 11 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (3 unique values: 23-47 cores)</summary>

```
1794997474 23
1794997479 23
1794997484 45
1794997489 45
1794997494 45
1794997499 45
1794997504 45
1794997510 45
1794997515 45
1794997520 45
1794997525 47
1794997530 47
1794997535 47
1794997540 47
1794997545 47
1794997550 47
1794997555 47
1794997560 47
1794997565 47
1794997570 47
```
</details>

---

