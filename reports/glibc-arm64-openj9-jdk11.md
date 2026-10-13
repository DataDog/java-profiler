---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-13 05:53:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1791884892 41
1791884897 41
1791884902 41
1791884907 41
1791884912 41
1791884917 41
1791884922 41
1791884927 41
1791884932 41
1791884937 41
1791884942 41
1791884947 46
1791884952 46
1791884957 48
1791884962 48
1791884967 48
1791884972 48
1791884977 48
1791884982 48
1791884987 48
```
</details>

---

