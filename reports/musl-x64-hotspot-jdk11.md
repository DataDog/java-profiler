---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-21 10:50:25 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (5 unique values: 69-85 cores)</summary>

```
1776782621 76
1776782626 72
1776782631 72
1776782636 72
1776782641 72
1776782646 72
1776782651 72
1776782656 69
1776782661 69
1776782666 85
1776782671 85
1776782676 85
1776782681 85
1776782686 85
1776782691 85
1776782696 85
1776782701 85
1776782706 85
1776782711 85
1776782716 85
```
</details>

---

