---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:09:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 261 |
| Sample Rate | 4.35/sec |
| Health Score | 272% |
| Threads | 12 |
| Allocations | 155 |

<details>
<summary>CPU Timeline (1 unique values: 31-31 cores)</summary>

```
1789743436 31
1789743441 31
1789743446 31
1789743451 31
1789743456 31
1789743461 31
1789743466 31
1789743471 31
1789743476 31
1789743481 31
1789743486 31
1789743491 31
1789743496 31
1789743501 31
1789743506 31
1789743511 31
1789743516 31
1789743521 31
1789743526 31
1789743531 31
```
</details>

---

