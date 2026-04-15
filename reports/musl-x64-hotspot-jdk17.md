---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-15 15:54:58 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (6 unique values: 16-45 cores)</summary>

```
1776282584 27
1776282589 25
1776282594 25
1776282599 45
1776282604 45
1776282609 34
1776282614 34
1776282619 34
1776282624 25
1776282629 25
1776282634 25
1776282639 25
1776282644 25
1776282649 25
1776282654 25
1776282659 25
1776282664 25
1776282669 25
1776282674 25
1776282679 25
```
</details>

---

