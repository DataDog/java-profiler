---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-13 11:55:57 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (3 unique values: 23-48 cores)</summary>

```
1776095484 23
1776095489 23
1776095494 23
1776095499 27
1776095504 27
1776095509 27
1776095514 27
1776095519 27
1776095525 27
1776095530 48
1776095535 48
1776095540 48
1776095545 48
1776095550 48
1776095555 48
1776095560 48
1776095565 48
1776095570 48
1776095575 48
1776095580 48
```
</details>

---

