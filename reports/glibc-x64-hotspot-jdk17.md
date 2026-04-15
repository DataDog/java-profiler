---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-15 13:26:57 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (8 unique values: 43-77 cores)</summary>

```
1776273662 49
1776273667 45
1776273672 45
1776273677 45
1776273682 43
1776273687 43
1776273692 43
1776273697 43
1776273702 47
1776273707 47
1776273712 47
1776273717 49
1776273722 49
1776273727 49
1776273732 49
1776273737 75
1776273742 75
1776273747 75
1776273752 70
1776273757 70
```
</details>

---

