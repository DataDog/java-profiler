---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 06:26:09 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (4 unique values: 29-49 cores)</summary>

```
1786357282 30
1786357287 30
1786357292 30
1786357297 30
1786357302 30
1786357307 38
1786357312 38
1786357317 38
1786357322 38
1786357327 38
1786357332 38
1786357337 38
1786357342 38
1786357347 38
1786357352 38
1786357357 49
1786357362 49
1786357367 49
1786357372 49
1786357377 29
```
</details>

---

