---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-07 12:48:07 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1791391370 30
1791391375 30
1791391380 30
1791391385 30
1791391390 30
1791391395 30
1791391400 30
1791391405 28
1791391410 28
1791391415 28
1791391420 28
1791391425 28
1791391430 28
1791391435 28
1791391440 28
1791391445 28
1791391450 28
1791391455 28
1791391460 28
1791391465 28
```
</details>

---

