---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:03:12 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 825 |
| Sample Rate | 13.75/sec |
| Health Score | 859% |
| Threads | 11 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1789743420 96
1789743425 96
1789743430 96
1789743436 96
1789743441 96
1789743446 96
1789743451 96
1789743456 96
1789743461 96
1789743466 96
1789743471 96
1789743476 96
1789743481 96
1789743486 96
1789743491 96
1789743496 96
1789743501 96
1789743506 96
1789743511 96
1789743516 94
```
</details>

---

