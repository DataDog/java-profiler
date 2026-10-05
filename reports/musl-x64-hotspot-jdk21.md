---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-05 16:36:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 61-70 cores)</summary>

```
1791232272 61
1791232277 61
1791232282 70
1791232287 70
1791232292 70
1791232297 70
1791232302 70
1791232307 70
1791232312 70
1791232317 70
1791232322 70
1791232327 70
1791232332 70
1791232337 70
1791232342 70
1791232347 70
1791232352 70
1791232357 70
1791232362 70
1791232367 70
```
</details>

---

