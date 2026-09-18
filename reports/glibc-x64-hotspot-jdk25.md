---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:10:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (7 unique values: 30-92 cores)</summary>

```
1789743444 30
1789743449 30
1789743454 51
1789743459 51
1789743464 51
1789743469 51
1789743474 51
1789743479 51
1789743484 92
1789743489 92
1789743494 92
1789743499 92
1789743504 72
1789743509 72
1789743514 73
1789743519 73
1789743524 73
1789743529 75
1789743534 75
1789743539 75
```
</details>

---

