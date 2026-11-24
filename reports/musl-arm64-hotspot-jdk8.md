---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-24 09:14:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 344 |
| Sample Rate | 5.73/sec |
| Health Score | 358% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 47-51 cores)</summary>

```
1795529302 49
1795529307 49
1795529312 49
1795529317 49
1795529322 49
1795529327 49
1795529332 49
1795529337 48
1795529342 48
1795529347 48
1795529352 48
1795529357 48
1795529362 48
1795529367 47
1795529372 47
1795529377 47
1795529382 49
1795529388 49
1795529393 49
1795529398 49
```
</details>

---

