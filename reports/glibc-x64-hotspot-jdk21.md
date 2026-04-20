---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 10:20:31 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 24-28 cores)</summary>

```
1776694637 28
1776694642 28
1776694647 24
1776694652 24
1776694657 24
1776694662 24
1776694667 24
1776694672 24
1776694677 24
1776694682 24
1776694687 24
1776694692 24
1776694697 28
1776694702 28
1776694707 28
1776694712 28
1776694717 28
1776694722 28
1776694727 28
1776694732 28
```
</details>

---

