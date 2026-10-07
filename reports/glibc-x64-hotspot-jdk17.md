---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-07 12:48:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (5 unique values: 57-74 cores)</summary>

```
1791391418 74
1791391423 74
1791391428 74
1791391433 74
1791391438 64
1791391443 64
1791391448 64
1791391453 64
1791391458 64
1791391463 62
1791391468 62
1791391473 62
1791391478 62
1791391483 62
1791391488 57
1791391493 57
1791391498 59
1791391503 59
1791391508 64
1791391513 64
```
</details>

---

