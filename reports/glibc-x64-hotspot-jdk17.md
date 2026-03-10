---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-10 13:36:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 10 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (6 unique values: 39-84 cores)</summary>

```
1773163857 39
1773163862 39
1773163867 39
1773163872 39
1773163877 39
1773163882 39
1773163887 41
1773163892 41
1773163897 41
1773163902 46
1773163907 46
1773163912 46
1773163917 46
1773163922 46
1773163927 46
1773163932 46
1773163937 46
1773163942 49
1773163947 49
1773163952 49
```
</details>

---

