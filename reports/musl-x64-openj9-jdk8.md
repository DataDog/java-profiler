---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-21 05:26:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 16-32 cores)</summary>

```
1789982394 32
1789982399 32
1789982404 32
1789982409 32
1789982414 16
1789982419 16
1789982424 16
1789982429 16
1789982434 16
1789982439 16
1789982444 16
1789982449 16
1789982454 16
1789982459 16
1789982464 16
1789982469 16
1789982474 16
1789982479 16
1789982484 16
1789982489 16
```
</details>

---

