---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:48:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1038 |
| Sample Rate | 17.30/sec |
| Health Score | 1081% |
| Threads | 12 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 68-70 cores)</summary>

```
1794595276 68
1794595281 68
1794595286 68
1794595291 68
1794595296 68
1794595301 68
1794595306 68
1794595311 68
1794595316 68
1794595321 68
1794595326 68
1794595331 68
1794595336 68
1794595341 70
1794595346 70
1794595352 70
1794595357 70
1794595362 70
1794595367 70
1794595372 70
```
</details>

---

