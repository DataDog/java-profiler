---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-05 16:36:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 954 |
| Sample Rate | 15.90/sec |
| Health Score | 994% |
| Threads | 9 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 16-24 cores)</summary>

```
1791232276 24
1791232281 24
1791232286 24
1791232291 24
1791232296 16
1791232301 16
1791232306 16
1791232311 16
1791232316 16
1791232321 16
1791232326 16
1791232331 16
1791232336 16
1791232341 16
1791232346 16
1791232351 16
1791232356 16
1791232361 16
1791232366 16
1791232371 16
```
</details>

---

