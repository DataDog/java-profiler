---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 00:03:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (6 unique values: 28-68 cores)</summary>

```
1795496337 40
1795496342 40
1795496347 40
1795496352 68
1795496357 68
1795496362 68
1795496367 68
1795496372 68
1795496377 68
1795496382 47
1795496387 47
1795496392 30
1795496397 30
1795496402 30
1795496407 30
1795496412 30
1795496417 30
1795496422 28
1795496427 28
1795496432 28
```
</details>

---

