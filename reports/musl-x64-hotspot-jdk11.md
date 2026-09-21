---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 05:26:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 8 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 74-96 cores)</summary>

```
1789982374 84
1789982379 84
1789982384 84
1789982389 84
1789982394 84
1789982399 90
1789982404 90
1789982409 96
1789982414 96
1789982419 96
1789982424 96
1789982429 96
1789982434 96
1789982439 96
1789982444 96
1789982449 96
1789982454 96
1789982459 96
1789982464 96
1789982469 96
```
</details>

---

