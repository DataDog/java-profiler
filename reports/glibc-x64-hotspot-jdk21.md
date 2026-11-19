---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 09:29:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 37 |
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
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 37-57 cores)</summary>

```
1795098314 57
1795098319 57
1795098324 57
1795098329 57
1795098334 57
1795098339 57
1795098344 57
1795098349 57
1795098354 57
1795098359 57
1795098364 37
1795098369 37
1795098374 37
1795098379 37
1795098384 37
1795098389 37
1795098394 37
1795098399 37
1795098404 37
1795098409 37
```
</details>

---

