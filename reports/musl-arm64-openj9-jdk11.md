---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:10:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 8 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 18-38 cores)</summary>

```
1789743406 18
1789743411 18
1789743416 38
1789743421 38
1789743426 38
1789743431 38
1789743436 38
1789743441 38
1789743446 38
1789743451 38
1789743456 38
1789743461 38
1789743466 38
1789743471 38
1789743476 38
1789743481 38
1789743486 33
1789743491 33
1789743496 33
1789743501 33
```
</details>

---

