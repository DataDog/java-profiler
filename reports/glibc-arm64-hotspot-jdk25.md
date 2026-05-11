---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-11 18:32:10 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778538428 64
1778538433 64
1778538438 64
1778538443 64
1778538448 64
1778538453 64
1778538458 64
1778538463 64
1778538468 64
1778538473 64
1778538478 64
1778538483 64
1778538488 64
1778538493 64
1778538498 64
1778538503 64
1778538508 64
1778538513 64
1778538518 64
1778538523 64
```
</details>

---

