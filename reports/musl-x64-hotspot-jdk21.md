---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-29 08:17:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 536 |
| Sample Rate | 17.87/sec |
| Health Score | 1117% |
| Threads | 10 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 25.00/sec |
| Health Score | 1562% |
| Threads | 13 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 78-86 cores)</summary>

```
1769692391 78
1769692396 78
1769692401 78
1769692406 78
1769692411 78
1769692417 78
1769692422 78
1769692427 78
1769692432 78
1769692437 78
1769692442 78
1769692447 78
1769692452 78
1769692457 78
1769692462 78
1769692467 78
1769692472 81
1769692477 81
1769692482 81
1769692487 81
```
</details>

---

