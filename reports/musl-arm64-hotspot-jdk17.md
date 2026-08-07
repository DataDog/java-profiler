---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-07 16:14:07 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 13 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (5 unique values: 16-27 cores)</summary>

```
1786133333 19
1786133338 19
1786133343 19
1786133348 19
1786133353 19
1786133358 21
1786133363 21
1786133368 21
1786133373 16
1786133378 16
1786133384 27
1786133389 27
1786133394 27
1786133399 27
1786133404 27
1786133409 27
1786133414 27
1786133419 27
1786133424 24
1786133429 24
```
</details>

---

