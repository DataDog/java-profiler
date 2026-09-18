---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:03:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 309 |
| Sample Rate | 5.15/sec |
| Health Score | 322% |
| Threads | 11 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1789743459 35
1789743464 35
1789743469 35
1789743474 35
1789743479 35
1789743484 35
1789743489 35
1789743494 35
1789743499 35
1789743504 35
1789743509 35
1789743514 35
1789743519 30
1789743524 30
1789743529 30
1789743534 30
1789743539 30
1789743544 30
1789743549 30
1789743554 30
```
</details>

---

