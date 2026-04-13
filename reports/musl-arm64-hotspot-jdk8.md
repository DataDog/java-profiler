---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-13 11:55:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776095492 59
1776095497 59
1776095502 59
1776095507 64
1776095512 64
1776095517 64
1776095522 64
1776095527 64
1776095532 64
1776095537 64
1776095542 64
1776095547 64
1776095552 64
1776095557 64
1776095562 64
1776095567 64
1776095572 64
1776095577 64
1776095582 64
1776095587 64
```
</details>

---

