---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-07 10:01:25 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 801 |
| Sample Rate | 13.35/sec |
| Health Score | 834% |
| Threads | 10 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (3 unique values: 75-79 cores)</summary>

```
1794063406 77
1794063411 77
1794063416 79
1794063421 79
1794063426 75
1794063431 75
1794063436 77
1794063441 77
1794063446 77
1794063451 77
1794063456 77
1794063461 77
1794063466 77
1794063471 77
1794063476 77
1794063481 77
1794063486 75
1794063491 75
1794063496 75
1794063501 75
```
</details>

---

