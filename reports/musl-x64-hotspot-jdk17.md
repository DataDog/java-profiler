---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-20 13:18:14 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 951 |
| Sample Rate | 15.85/sec |
| Health Score | 991% |
| Threads | 12 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 88-94 cores)</summary>

```
1792516441 90
1792516446 90
1792516451 90
1792516456 90
1792516461 90
1792516466 90
1792516471 88
1792516476 88
1792516481 88
1792516486 88
1792516491 88
1792516496 88
1792516501 88
1792516506 88
1792516511 88
1792516516 90
1792516521 90
1792516526 90
1792516531 90
1792516536 92
```
</details>

---

