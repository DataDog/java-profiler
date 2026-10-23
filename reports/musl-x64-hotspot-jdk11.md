---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 12:24:21 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 7 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1792772391 27
1792772396 27
1792772401 27
1792772406 27
1792772411 27
1792772416 27
1792772421 27
1792772426 27
1792772431 27
1792772436 27
1792772441 27
1792772446 27
1792772451 27
1792772456 27
1792772461 27
1792772466 25
1792772471 25
1792772476 25
1792772481 25
1792772486 25
```
</details>

---

