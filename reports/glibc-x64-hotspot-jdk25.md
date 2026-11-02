---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 10:00:24 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 76-84 cores)</summary>

```
1793631331 84
1793631336 84
1793631341 84
1793631346 84
1793631351 84
1793631356 84
1793631361 84
1793631366 84
1793631371 84
1793631376 84
1793631381 84
1793631387 84
1793631392 84
1793631397 84
1793631402 84
1793631407 84
1793631412 76
1793631417 76
1793631422 76
1793631427 76
```
</details>

---

