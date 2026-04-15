---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-15 11:14:26 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 819 |
| Sample Rate | 13.65/sec |
| Health Score | 853% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (5 unique values: 75-84 cores)</summary>

```
1776265680 75
1776265685 77
1776265690 77
1776265695 77
1776265700 79
1776265705 79
1776265710 79
1776265715 79
1776265720 79
1776265725 84
1776265730 84
1776265735 84
1776265740 84
1776265745 84
1776265750 84
1776265755 84
1776265760 84
1776265765 84
1776265770 84
1776265775 84
```
</details>

---

