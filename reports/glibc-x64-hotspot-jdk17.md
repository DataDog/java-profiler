---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-20 06:18:38 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
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
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787220897 96
1787220902 96
1787220907 96
1787220912 96
1787220917 96
1787220922 94
1787220927 94
1787220932 94
1787220937 94
1787220942 94
1787220947 94
1787220952 94
1787220957 94
1787220962 94
1787220967 94
1787220972 94
1787220977 94
1787220982 94
1787220987 94
1787220992 94
```
</details>

---

