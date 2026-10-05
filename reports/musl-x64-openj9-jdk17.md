---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-05 16:36:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 821 |
| Sample Rate | 13.68/sec |
| Health Score | 855% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1791232271 64
1791232276 64
1791232281 64
1791232287 64
1791232292 64
1791232297 64
1791232302 64
1791232307 64
1791232312 64
1791232317 66
1791232322 66
1791232327 66
1791232332 66
1791232337 66
1791232342 66
1791232347 66
1791232352 66
1791232357 66
1791232362 66
1791232367 66
```
</details>

---

