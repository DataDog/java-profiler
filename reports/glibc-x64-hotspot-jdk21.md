---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 08:27:57 EDT

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
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (5 unique values: 28-54 cores)</summary>

```
1776687640 28
1776687645 28
1776687650 32
1776687655 32
1776687660 32
1776687665 32
1776687670 30
1776687675 30
1776687680 30
1776687685 30
1776687690 30
1776687695 30
1776687700 30
1776687705 30
1776687710 30
1776687715 30
1776687720 54
1776687725 54
1776687730 49
1776687735 49
```
</details>

---

