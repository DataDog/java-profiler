---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 13:21:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1794507353 94
1794507358 94
1794507363 94
1794507368 94
1794507373 92
1794507378 92
1794507383 92
1794507388 92
1794507393 92
1794507398 92
1794507403 92
1794507408 92
1794507413 92
1794507418 92
1794507423 92
1794507428 92
1794507433 92
1794507438 92
1794507443 92
1794507448 92
```
</details>

---

