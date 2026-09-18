---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:08:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 953 |
| Sample Rate | 15.88/sec |
| Health Score | 993% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1789743431 70
1789743436 70
1789743441 70
1789743446 70
1789743451 70
1789743456 70
1789743461 70
1789743466 70
1789743471 70
1789743476 70
1789743481 70
1789743486 70
1789743491 72
1789743496 72
1789743501 72
1789743506 72
1789743511 72
1789743516 72
1789743521 72
1789743526 72
```
</details>

---

