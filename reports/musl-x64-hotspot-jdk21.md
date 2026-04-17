---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-17 07:39:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 999 |
| Sample Rate | 16.65/sec |
| Health Score | 1041% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (5 unique values: 32-50 cores)</summary>

```
1776425750 32
1776425755 37
1776425760 37
1776425765 37
1776425770 50
1776425775 50
1776425780 50
1776425785 50
1776425790 50
1776425795 50
1776425800 50
1776425805 50
1776425810 50
1776425815 50
1776425820 50
1776425825 50
1776425830 48
1776425835 48
1776425840 48
1776425845 48
```
</details>

---

