---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 03:05:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 10 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 26-43 cores)</summary>

```
1790665324 43
1790665329 43
1790665334 43
1790665339 43
1790665344 43
1790665349 43
1790665354 43
1790665359 43
1790665364 35
1790665369 35
1790665374 35
1790665379 35
1790665384 35
1790665389 35
1790665394 35
1790665399 35
1790665404 35
1790665409 35
1790665414 35
1790665419 35
```
</details>

---

