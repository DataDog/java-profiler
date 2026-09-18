---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:11:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 10 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789743441 43
1789743446 43
1789743451 43
1789743456 48
1789743461 48
1789743466 48
1789743471 48
1789743476 48
1789743481 48
1789743486 48
1789743491 48
1789743496 48
1789743501 48
1789743506 48
1789743511 48
1789743516 48
1789743521 48
1789743526 48
1789743531 48
1789743536 48
```
</details>

---

