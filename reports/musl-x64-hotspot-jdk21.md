---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-15 11:14:28 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (5 unique values: 30-50 cores)</summary>

```
1776265862 50
1776265867 50
1776265872 50
1776265877 30
1776265882 30
1776265887 30
1776265892 30
1776265897 30
1776265902 30
1776265907 35
1776265912 35
1776265917 35
1776265922 35
1776265927 35
1776265932 35
1776265937 39
1776265942 39
1776265947 39
1776265952 39
1776265957 39
```
</details>

---

