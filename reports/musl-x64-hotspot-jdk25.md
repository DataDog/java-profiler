---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 10:54:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 78-86 cores)</summary>

```
1778165312 78
1778165317 78
1778165322 78
1778165327 78
1778165332 78
1778165337 78
1778165342 78
1778165347 78
1778165352 78
1778165357 78
1778165362 81
1778165367 81
1778165372 81
1778165377 81
1778165382 85
1778165387 85
1778165392 86
1778165397 86
1778165402 86
1778165407 86
```
</details>

---

