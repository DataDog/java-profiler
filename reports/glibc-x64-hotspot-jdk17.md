---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 12:06:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 10 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1794848423 94
1794848428 94
1794848433 94
1794848438 94
1794848443 94
1794848448 96
1794848453 96
1794848458 96
1794848463 96
1794848468 96
1794848473 96
1794848478 96
1794848483 96
1794848488 96
1794848493 96
1794848498 96
1794848503 96
1794848508 96
1794848513 96
1794848518 96
```
</details>

---

