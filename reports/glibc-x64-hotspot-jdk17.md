---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-23 15:03:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 11 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (6 unique values: 62-74 cores)</summary>

```
1776970688 66
1776970693 66
1776970698 74
1776970703 74
1776970708 74
1776970713 72
1776970718 72
1776970723 69
1776970728 69
1776970733 69
1776970738 69
1776970743 69
1776970748 69
1776970753 69
1776970758 64
1776970763 64
1776970768 64
1776970773 64
1776970778 64
1776970783 64
```
</details>

---

