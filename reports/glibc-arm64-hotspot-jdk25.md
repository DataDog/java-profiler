---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 05:26:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789982433 43
1789982438 43
1789982443 43
1789982448 43
1789982453 43
1789982458 43
1789982463 43
1789982468 43
1789982473 43
1789982478 43
1789982483 48
1789982488 48
1789982493 48
1789982498 48
1789982503 48
1789982508 48
1789982513 48
1789982518 48
1789982523 48
1789982528 48
```
</details>

---

