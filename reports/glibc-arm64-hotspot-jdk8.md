---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-14 04:32:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1791966443 51
1791966448 51
1791966453 51
1791966458 51
1791966463 51
1791966468 51
1791966473 51
1791966478 51
1791966483 51
1791966488 51
1791966493 51
1791966498 51
1791966503 51
1791966508 64
1791966513 64
1791966518 64
1791966523 64
1791966528 64
1791966533 64
1791966538 64
```
</details>

---

