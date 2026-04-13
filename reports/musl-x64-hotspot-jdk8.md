---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-13 11:55:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 74-84 cores)</summary>

```
1776095506 84
1776095511 84
1776095516 84
1776095521 84
1776095526 84
1776095531 79
1776095536 79
1776095541 79
1776095546 79
1776095551 79
1776095556 77
1776095561 77
1776095566 77
1776095571 77
1776095576 77
1776095581 77
1776095586 77
1776095591 77
1776095596 77
1776095601 77
```
</details>

---

