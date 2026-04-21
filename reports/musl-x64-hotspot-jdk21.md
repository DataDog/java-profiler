---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-21 06:58:14 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 874 |
| Sample Rate | 14.57/sec |
| Health Score | 911% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (5 unique values: 72-78 cores)</summary>

```
1776768667 77
1776768672 77
1776768677 77
1776768682 77
1776768687 77
1776768692 77
1776768697 77
1776768702 77
1776768707 75
1776768712 75
1776768717 75
1776768722 75
1776768727 75
1776768732 75
1776768737 75
1776768742 75
1776768747 75
1776768752 72
1776768757 72
1776768762 76
```
</details>

---

