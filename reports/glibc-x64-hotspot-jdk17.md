---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 05:26:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (2 unique values: 62-72 cores)</summary>

```
1789982419 72
1789982424 72
1789982429 72
1789982434 72
1789982439 72
1789982444 72
1789982449 72
1789982454 72
1789982459 72
1789982464 72
1789982469 72
1789982474 72
1789982479 72
1789982484 62
1789982489 62
1789982494 62
1789982499 62
1789982504 62
1789982509 62
1789982514 62
```
</details>

---

