---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:19:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 5 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795641312 29
1795641317 29
1795641322 29
1795641327 29
1795641332 29
1795641337 29
1795641342 34
1795641347 34
1795641352 34
1795641357 34
1795641362 34
1795641367 34
1795641372 34
1795641377 34
1795641382 34
1795641387 34
1795641392 34
1795641397 34
1795641402 34
1795641407 34
```
</details>

---

