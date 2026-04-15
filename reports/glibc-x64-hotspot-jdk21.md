---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-15 13:26:58 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (7 unique values: 43-75 cores)</summary>

```
1776273650 49
1776273655 49
1776273660 49
1776273665 49
1776273670 45
1776273675 45
1776273680 43
1776273685 43
1776273690 43
1776273695 43
1776273701 43
1776273706 47
1776273711 47
1776273716 49
1776273721 49
1776273726 49
1776273731 49
1776273736 49
1776273741 75
1776273746 75
```
</details>

---

