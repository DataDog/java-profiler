---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 10:00:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 10 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1793631337 72
1793631342 72
1793631347 72
1793631352 72
1793631357 72
1793631362 72
1793631367 70
1793631372 70
1793631377 70
1793631382 70
1793631387 70
1793631392 70
1793631397 70
1793631402 70
1793631407 70
1793631412 70
1793631417 70
1793631422 70
1793631427 70
1793631432 70
```
</details>

---

