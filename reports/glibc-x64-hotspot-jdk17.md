---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 13:30:50 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (3 unique values: 55-72 cores)</summary>

```
1794334872 70
1794334877 70
1794334882 70
1794334887 72
1794334892 72
1794334897 72
1794334902 72
1794334907 72
1794334912 72
1794334917 55
1794334922 55
1794334927 55
1794334932 55
1794334937 55
1794334942 55
1794334947 55
1794334952 55
1794334957 55
1794334962 55
1794334967 55
```
</details>

---

