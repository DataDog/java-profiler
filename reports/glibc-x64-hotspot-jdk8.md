---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-17 11:46:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 40-57 cores)</summary>

```
1776440641 57
1776440646 57
1776440651 57
1776440656 57
1776440661 57
1776440666 57
1776440671 57
1776440676 57
1776440681 57
1776440686 57
1776440691 57
1776440696 57
1776440701 40
1776440706 40
1776440711 40
1776440716 40
1776440721 40
1776440726 40
1776440731 40
1776440736 40
```
</details>

---

