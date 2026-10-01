---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-01 08:26:30 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 32 |
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
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (4 unique values: 32-52 cores)</summary>

```
1790857341 43
1790857346 43
1790857351 43
1790857356 43
1790857361 43
1790857366 43
1790857371 43
1790857376 43
1790857381 43
1790857386 43
1790857391 43
1790857396 43
1790857401 35
1790857406 35
1790857411 35
1790857416 52
1790857421 52
1790857426 52
1790857431 52
1790857436 32
```
</details>

---

