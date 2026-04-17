---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-17 11:46:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (6 unique values: 64-73 cores)</summary>

```
1776440574 70
1776440579 70
1776440584 70
1776440589 72
1776440594 72
1776440599 72
1776440604 72
1776440609 68
1776440614 68
1776440619 68
1776440624 68
1776440629 68
1776440634 68
1776440639 68
1776440644 73
1776440649 73
1776440654 64
1776440659 64
1776440664 66
1776440669 66
```
</details>

---

