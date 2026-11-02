---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 10:00:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (5 unique values: 83-91 cores)</summary>

```
1793631332 88
1793631337 86
1793631342 86
1793631347 91
1793631352 91
1793631357 91
1793631362 89
1793631367 89
1793631372 89
1793631377 89
1793631382 91
1793631387 91
1793631392 91
1793631397 88
1793631402 88
1793631407 88
1793631412 88
1793631417 88
1793631422 88
1793631427 83
```
</details>

---

