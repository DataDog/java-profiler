---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 06:18:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 39 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1787220872 24
1787220877 24
1787220882 24
1787220887 29
1787220892 29
1787220897 29
1787220902 29
1787220907 29
1787220912 29
1787220917 29
1787220922 29
1787220927 29
1787220932 29
1787220937 29
1787220942 29
1787220947 29
1787220952 29
1787220957 29
1787220962 29
1787220967 29
```
</details>

---

