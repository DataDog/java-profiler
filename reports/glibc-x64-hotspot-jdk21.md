---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-21 10:50:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 319 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 852 |
| Sample Rate | 14.20/sec |
| Health Score | 887% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (3 unique values: 83-87 cores)</summary>

```
1776782669 85
1776782674 85
1776782679 85
1776782684 85
1776782689 85
1776782694 85
1776782699 83
1776782704 83
1776782709 83
1776782714 83
1776782719 83
1776782724 83
1776782729 83
1776782734 83
1776782739 85
1776782744 85
1776782749 85
1776782754 85
1776782759 85
1776782764 87
```
</details>

---

