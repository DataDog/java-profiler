---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 05:49:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 55-74 cores)</summary>

```
1789983869 74
1789983874 74
1789983879 74
1789983884 74
1789983889 74
1789983894 74
1789983899 74
1789983904 74
1789983909 74
1789983914 74
1789983919 74
1789983924 64
1789983929 64
1789983934 64
1789983939 64
1789983944 64
1789983949 64
1789983954 64
1789983959 64
1789983964 64
```
</details>

---

