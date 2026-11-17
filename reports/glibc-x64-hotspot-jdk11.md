---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 05:51:49 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 63-89 cores)</summary>

```
1794912454 63
1794912459 63
1794912464 63
1794912469 63
1794912474 63
1794912479 63
1794912484 63
1794912489 63
1794912494 63
1794912499 63
1794912504 63
1794912509 83
1794912514 83
1794912519 83
1794912524 83
1794912529 83
1794912534 83
1794912539 89
1794912544 89
1794912549 87
```
</details>

---

