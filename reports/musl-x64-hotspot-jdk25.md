---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 10:36:50 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (4 unique values: 24-30 cores)</summary>

```
1794497392 30
1794497397 30
1794497402 30
1794497407 30
1794497412 30
1794497417 30
1794497422 25
1794497427 25
1794497432 25
1794497437 25
1794497442 25
1794497447 25
1794497452 25
1794497457 25
1794497462 25
1794497467 25
1794497472 25
1794497477 25
1794497482 25
1794497487 27
```
</details>

---

