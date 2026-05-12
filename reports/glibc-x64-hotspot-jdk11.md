---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:46:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 822 |
| Sample Rate | 13.70/sec |
| Health Score | 856% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 15-18 cores)</summary>

```
1778582433 15
1778582438 15
1778582443 15
1778582448 15
1778582453 15
1778582458 15
1778582463 16
1778582468 16
1778582473 16
1778582478 16
1778582483 16
1778582488 16
1778582493 16
1778582498 16
1778582503 16
1778582508 16
1778582513 18
1778582518 18
1778582523 18
1778582528 18
```
</details>

---

