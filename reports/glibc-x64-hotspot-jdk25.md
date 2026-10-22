---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 08:38:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (5 unique values: 25-29 cores)</summary>

```
1792672439 26
1792672444 26
1792672449 26
1792672454 28
1792672459 28
1792672464 28
1792672469 28
1792672474 28
1792672479 28
1792672484 28
1792672489 28
1792672494 29
1792672499 29
1792672504 29
1792672509 29
1792672514 27
1792672519 27
1792672524 27
1792672529 27
1792672534 27
```
</details>

---

