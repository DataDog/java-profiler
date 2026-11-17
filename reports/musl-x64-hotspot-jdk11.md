---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 05:51:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 876 |
| Sample Rate | 14.60/sec |
| Health Score | 912% |
| Threads | 10 |
| Allocations | 550 |

<details>
<summary>CPU Timeline (4 unique values: 73-79 cores)</summary>

```
1794912429 73
1794912434 73
1794912439 73
1794912444 75
1794912449 75
1794912454 77
1794912459 77
1794912464 79
1794912469 79
1794912474 79
1794912479 79
1794912484 79
1794912489 79
1794912494 79
1794912499 79
1794912504 79
1794912509 79
1794912514 79
1794912520 79
1794912525 77
```
</details>

---

