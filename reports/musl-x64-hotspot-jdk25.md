---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-15 08:57:51 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 51-70 cores)</summary>

```
1776257545 70
1776257550 70
1776257555 51
1776257560 51
1776257565 51
1776257570 51
1776257575 51
1776257580 51
1776257585 51
1776257590 51
1776257595 51
1776257600 51
1776257605 51
1776257610 51
1776257615 51
1776257620 51
1776257625 51
1776257630 51
1776257635 51
1776257640 51
```
</details>

---

