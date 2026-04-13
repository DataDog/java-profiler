---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-13 11:55:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 56-62 cores)</summary>

```
1776095583 62
1776095588 62
1776095593 62
1776095598 62
1776095603 62
1776095608 62
1776095613 62
1776095618 62
1776095623 62
1776095628 62
1776095633 62
1776095638 62
1776095643 62
1776095648 62
1776095653 62
1776095658 62
1776095663 62
1776095668 62
1776095673 62
1776095678 56
```
</details>

---

