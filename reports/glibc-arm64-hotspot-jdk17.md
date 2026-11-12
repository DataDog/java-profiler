---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 12:07:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794502892 43
1794502897 43
1794502902 43
1794502907 43
1794502912 43
1794502917 43
1794502922 43
1794502927 48
1794502932 48
1794502937 48
1794502942 48
1794502947 48
1794502952 48
1794502957 48
1794502962 48
1794502967 48
1794502972 48
1794502977 48
1794502982 48
1794502987 48
```
</details>

---

