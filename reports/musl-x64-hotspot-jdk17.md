---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-22 12:39:21 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 905 |
| Sample Rate | 15.08/sec |
| Health Score | 942% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (6 unique values: 72-85 cores)</summary>

```
1776875626 72
1776875631 72
1776875636 72
1776875641 74
1776875646 74
1776875651 74
1776875656 74
1776875661 76
1776875666 76
1776875671 76
1776875676 80
1776875681 80
1776875686 80
1776875691 80
1776875696 80
1776875701 80
1776875706 80
1776875711 80
1776875716 80
1776875721 83
```
</details>

---

