---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 08:25:43 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 78-81 cores)</summary>

```
1795094406 78
1795094411 78
1795094416 78
1795094421 78
1795094426 78
1795094431 78
1795094436 78
1795094441 78
1795094446 78
1795094451 78
1795094456 81
1795094461 81
1795094466 81
1795094471 81
1795094476 81
1795094481 81
1795094486 81
1795094491 79
1795094496 79
1795094501 79
```
</details>

---

