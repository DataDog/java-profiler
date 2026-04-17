---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-17 07:39:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 72-86 cores)</summary>

```
1776425755 72
1776425760 72
1776425765 72
1776425770 72
1776425775 72
1776425780 72
1776425785 72
1776425790 72
1776425795 81
1776425800 81
1776425805 81
1776425810 83
1776425815 83
1776425820 83
1776425825 83
1776425830 83
1776425835 83
1776425840 83
1776425845 83
1776425850 86
```
</details>

---

