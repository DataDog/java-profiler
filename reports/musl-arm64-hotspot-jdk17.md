---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-05 16:36:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 278 |
| Sample Rate | 4.63/sec |
| Health Score | 289% |
| Threads | 10 |
| Allocations | 131 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1791232266 39
1791232271 39
1791232276 39
1791232281 39
1791232286 39
1791232291 44
1791232296 44
1791232301 44
1791232306 44
1791232311 44
1791232316 44
1791232321 44
1791232326 44
1791232331 44
1791232336 44
1791232341 44
1791232346 44
1791232351 44
1791232356 44
1791232361 44
```
</details>

---

