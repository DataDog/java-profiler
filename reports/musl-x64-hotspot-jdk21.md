---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-13 11:55:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 56-61 cores)</summary>

```
1776095486 56
1776095491 56
1776095496 56
1776095501 61
1776095506 61
1776095511 61
1776095516 61
1776095521 61
1776095526 61
1776095531 61
1776095536 61
1776095541 61
1776095546 61
1776095551 61
1776095556 61
1776095561 61
1776095566 61
1776095571 61
1776095576 61
1776095581 61
```
</details>

---

