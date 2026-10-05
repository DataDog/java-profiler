---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-05 16:36:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1791232297 46
1791232302 46
1791232307 46
1791232312 46
1791232317 46
1791232322 51
1791232327 51
1791232332 51
1791232337 51
1791232342 51
1791232347 51
1791232352 51
1791232357 51
1791232362 51
1791232367 51
1791232372 51
1791232377 51
1791232382 51
1791232387 51
1791232392 51
```
</details>

---

