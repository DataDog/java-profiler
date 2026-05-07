---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 10:54:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 13 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 51-59 cores)</summary>

```
1778165316 51
1778165321 51
1778165326 51
1778165331 51
1778165336 51
1778165341 51
1778165346 51
1778165351 51
1778165356 51
1778165361 51
1778165367 51
1778165372 55
1778165377 55
1778165382 55
1778165387 55
1778165392 59
1778165397 59
1778165402 59
1778165407 59
1778165412 59
```
</details>

---

