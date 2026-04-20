---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-19 21:19:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 49-59 cores)</summary>

```
1776647634 59
1776647639 59
1776647644 59
1776647649 59
1776647654 59
1776647659 59
1776647664 59
1776647669 54
1776647674 54
1776647679 54
1776647685 54
1776647690 54
1776647695 54
1776647700 54
1776647705 54
1776647710 54
1776647715 54
1776647720 54
1776647725 54
1776647730 54
```
</details>

---

