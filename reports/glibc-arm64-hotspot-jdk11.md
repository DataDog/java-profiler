---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 05:26:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 12 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789982379 48
1789982384 48
1789982389 48
1789982394 48
1789982399 43
1789982404 43
1789982409 43
1789982414 43
1789982419 43
1789982424 43
1789982429 43
1789982434 43
1789982439 43
1789982444 43
1789982449 43
1789982454 43
1789982459 43
1789982464 43
1789982469 43
1789982474 43
```
</details>

---

