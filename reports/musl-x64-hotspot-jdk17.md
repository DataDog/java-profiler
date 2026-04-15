---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-15 11:36:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 886 |
| Sample Rate | 14.77/sec |
| Health Score | 923% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (5 unique values: 63-73 cores)</summary>

```
1776266784 63
1776266789 63
1776266794 63
1776266799 65
1776266804 65
1776266809 65
1776266814 65
1776266819 65
1776266824 65
1776266829 65
1776266834 71
1776266839 71
1776266844 71
1776266849 71
1776266854 71
1776266859 71
1776266864 71
1776266869 71
1776266874 71
1776266879 69
```
</details>

---

